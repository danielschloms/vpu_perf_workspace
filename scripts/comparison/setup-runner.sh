#!/usr/bin/env bash
###############################################################################
# v3-setup.sh
# ===========
# Idempotent setup of the RAM-backed filesystem (tmpfs) that v3-run.py writes
# its instruction traces into, so hundreds of GB of traces never touch the SSD.
#
# Usage:
#   ./v3-setup.sh                       # create+mount+register (default /mnt/traces_ram, 64G)
#   ./v3-setup.sh --size 32G            # a different size
#   ./v3-setup.sh --mount /dev/shm/v3   # a different mount point
#   ./v3-setup.sh --unmount             # unmount and remove the fstab entry
#
# Environment overrides: TRACE_MOUNT, TRACE_SIZE
###############################################################################

set -euo pipefail

SCRIPT_DIR="$(cd -- "$(dirname -- "${BASH_SOURCE[0]}")" &> /dev/null && pwd)"

# Defaults must match v3-run.py.
MOUNT_POINT="${TRACE_MOUNT:-/mnt/traces_ram}"
SIZE="${TRACE_SIZE:-64G}"
UNMOUNT=0

usage() {
    cat <<EOF
Usage: $0 [options]

Options:
  --mount <path>   mount point (env: TRACE_MOUNT, default /mnt/traces_ram)
  --size  <size>   tmpfs size, e.g. 32G (env: TRACE_SIZE, default 64G)
  --unmount        unmount and remove the /etc/fstab line
  -h, --help       show this help
EOF
}

while [[ $# -gt 0 ]]; do
  case "$1" in
    --mount)
      MOUNT_POINT="${2:?--mount requires a path}"
      shift 2
      ;;
    --size)
      SIZE="${2:?--size requires a size like 32G}"
      shift 2
      ;;
    --unmount)
      UNMOUNT=1
      shift
      ;;
    -h|--help)
      usage
      exit 0
      ;;
    *)
      echo "Unknown option: $1" >&2
      usage >&2
      exit 1
      ;;
  esac
done

# Require root; re-exec via sudo if needed.
if [[ "${EUID}" -ne 0 ]]; then
  echo "[setup] elevation required; re-running via sudo..."
  exec sudo -E "$0" "$@"
fi

FSTAB_OPTS="defaults,size=${SIZE}"

is_mounted_tmpfs() {
    findmnt -rn -o FSTYPE --target "${MOUNT_POINT}" 2>/dev/null | grep -qx "tmpfs"
}

fstab_has_entry() {
    # Literal compare on the mount-point field, no regex surprises.
    awk -v mp="${MOUNT_POINT}" 'NF >= 1 && $1 == mp' /etc/fstab | grep -q .
}

add_fstab_entry() {
    if ! fstab_has_entry; then
        echo "${MOUNT_POINT} tmpfs ${FSTAB_OPTS} 0 0" >> /etc/fstab
        echo "[setup] added to /etc/fstab: ${MOUNT_POINT} tmpfs ${FSTAB_OPTS} 0 0"
    else
        echo "[setup] /etc/fstab entry already present"
    fi
}

if [[ "${UNMOUNT}" -eq 1 ]]; then
    echo "[setup] unmounting ${MOUNT_POINT}..."
    if is_mounted_tmpfs; then
        umount "${MOUNT_POINT}"
        echo "[setup] unmounted"
    else
        echo "[setup] not currently mounted as tmpfs; nothing to unmount"
    fi
    # Remove the fstab line (literal mount-point match).
    if fstab_has_entry; then
        awk -v mp="${MOUNT_POINT}" 'NF >= 1 && $1 != mp' /etc/fstab > /tmp/fstab.tmp
        if [ -s /tmp/fstab.tmp ] && mv /tmp/fstab.tmp /etc/fstab; then
            echo "[setup] removed /etc/fstab entry"
        else
            rm -f /tmp/fstab.tmp
            echo "[setup] could not rewrite /etc/fstab (left unchanged)" >&2
        fi
    else
        echo "[setup] no /etc/fstab entry to remove"
    fi
    exit 0
fi

mkdir -p "${MOUNT_POINT}"

if is_mounted_tmpfs; then
    echo "[setup] ${MOUNT_POINT} is already mounted as tmpfs"
    add_fstab_entry
    echo "[setup] done"
    exit 0
fi

echo "[setup] mounting tmpfs ${SIZE} at ${MOUNT_POINT}..."
mount -t tmpfs -o "${FSTAB_OPTS}" tmpfs "${MOUNT_POINT}"

if is_mounted_tmpfs; then
    echo "[setup] mounted: ${MOUNT_POINT} (size=${SIZE})"
    add_fstab_entry
    echo "[setup] done"
else
    echo "[setup] FAILED to mount ${MOUNT_POINT}" >&2
    exit 1
fi
