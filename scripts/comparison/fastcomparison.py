import pathlib
from util import error, success, red, blue, green

START_LABEL = "address_match_start"
END_LABEL = "address_match_end"


class ParseException(Exception):
    def __init__(self, *args):
        super().__init__(*args)

    def __str__(self):
        return "ParseException"


class CmpResult:
    def __init__(
        self,
        cpi_etiss: float,
        cpi_verilator: float,
        sum_diff: int,
        n_instrs: int,
    ):
        self.cpi_etiss = cpi_etiss
        self.cpi_verilator = cpi_verilator
        self.cpi_error_pct = ((cpi_etiss / cpi_verilator) - 1) * 100
        self.sum_diff = sum_diff
        self.n_instrs = n_instrs

    def printout(self, name: str):
        abs_err = abs(self.cpi_error_pct)
        fun_err = red if abs_err >= 5.0 else blue if abs_err >= 2.5 else green
        err_str = fun_err(f"{self.cpi_error_pct:.4f}")
        adi: float = self.sum_diff / self.n_instrs
        fun_adi: function = red if adi >= 0.25 else blue if adi >= 0.1 else green
        adi_str: str = fun_adi(f"{adi:.4f}")
        success(
            name,
            f"CPI ETISS {self.cpi_etiss:.4f} | CPI RTL {self.cpi_verilator:.4f} | CPI Error {err_str}% | ASD {self.sum_diff} | ADI {adi_str}",
        )


def read_addresses(
    verilator_dump_file: pathlib.Path, etiss_dump_file: pathlib.Path
) -> tuple[dict, bool]:
    """Returns a dictionary with start and end addresses."""
    fname = "CMP: read_addresses"
    verilator_start = 0
    verilator_end = 0
    etiss_start = 0
    etiss_end = 0

    ok = True

    try:
        with open(verilator_dump_file, "r", encoding="utf-8") as verilator_dump:
            for line in verilator_dump:
                if f"<{START_LABEL}>:" in line:
                    verilator_start = int(line.split(" ")[0], 16)
                if f"<{END_LABEL}>:" in line:
                    verilator_end = int(line.split(" ")[0], 16)
    except:
        error(f"(AddressMatcher) Could not find {verilator_dump_file} Verilator dump")
        ok = False

    if verilator_start == 0:
        error(fname, "Error Verilator start")
    if verilator_end == 0:
        error(fname, "Error Verilator end")

    try:
        with open(etiss_dump_file, "r", encoding="utf-8") as etiss_dump:
            for line in etiss_dump:
                if f"<{START_LABEL}>:" in line:
                    etiss_start = int(line.split(" ")[0], 16)
                if f"<{END_LABEL}>:" in line:
                    etiss_end = int(line.split(" ")[0], 16)
    except:
        error(f"(AddressMatcher) Could not find {etiss_dump_file} Verilator dump")
        ok = False

    if etiss_start == 0:
        error(fname, "Error ETISS start")
    if etiss_end == 0:
        error(fname, "Error ETISS end")

    return {
        "e_start": etiss_start,
        "e_end": etiss_end,
        "v_start": verilator_start,
        "v_end": verilator_end,
    }, ok


def parse_etiss_line(line: str):
    split_line = line.split(" ")
    pc = int(split_line[0][2:].lstrip("0"), base=16)
    asm = int(split_line[4], 2)
    instr = split_line[2]
    return pc, asm, instr


def parse_verilator_line(line: str):
    fname = "parse_verilator_line"
    split_line = line.strip().split(",")
    try:
        pc = int(split_line[0], base=16)
        asm = int(split_line[1], base=16)
        delta = int(split_line[3])
        cycles = int(split_line[2])
        return pc, asm, cycles, delta
    except:
        error(fname, "Could not parse line!")
        raise ParseException


def parse_stages(line: str) -> dict[str, int]:
    split_line = line.strip().split(",")
    stages = {}
    for i, stage in enumerate(split_line):
        stages[stage] = i
    return stages


def analyze_traces(
    etiss_timing_path: pathlib.Path,
    etiss_trace_path: pathlib.Path,
    verilator_trace_path: pathlib.Path,
    match_path: pathlib.Path,
    addresses: dict[str, int],
    write_match: bool,
    keep_traces: bool = False,
    print_stages: bool = True,
) -> tuple[CmpResult, bool]:

    with open(etiss_trace_path, "r", encoding="utf-8") as etiss_trace, open(
        verilator_trace_path, "r", encoding="utf-8"
    ) as verilator_trace, open(
        etiss_timing_path, "r", encoding="utf-8"
    ) as etiss_timing, open(
        match_path, "w", encoding="utf-8"
    ) as match_file:

        stage_line = etiss_timing.readline()
        stages = parse_stages(stage_line)
        stages_to_print = stages.keys() if print_stages else []

        # Skip first line (ETISS trace skips first instruction)
        etiss_timing.readline()
        verilator_trace.readline()

        timing_stage_index = stages["EX_stg"]

        sum_diff = 0
        cycles_e_prev = 0
        cycles_e_start = 0
        cycles_v_start = 0

        # Skip to start address ETISS
        start_found_e = False
        start_found_v = False
        while True:
            timing_line = etiss_timing.readline()
            if timing_line[0] == "I":
                continue

            etiss_line = etiss_trace.readline()
            pc_e, _, _ = parse_etiss_line(etiss_line)
            if pc_e == addresses["e_start"]:
                cycles_e_prev = int(timing_line.strip().split(",")[timing_stage_index])
                cycles_e_start = cycles_e_prev
                start_found_e = True
                break

        # Skip to start address Verilator
        while True:
            verilator_line = verilator_trace.readline()
            if not verilator_line:
                error("analyze", "No Verilator start address found")
                return (CmpResult(0, 0, 0, 0), False)
            pc_v, asm, cycles, delta = parse_verilator_line(verilator_line)
            if pc_v == addresses["v_start"]:
                cycles_v_start = cycles
                start_found_v = True
                break

        if not (start_found_e and start_found_v):
            print("Error!")
            return (CmpResult(0, 0, 0, 0), False)

        n_instrs = 0
        running_cycles_v = 0
        nonzero_diffs = 0
        # Analyze
        while True:
            timing_line = etiss_timing.readline()
            if not timing_line:
                break
            if timing_line[0] == "I":
                continue

            etiss_trace_line = etiss_trace.readline()
            verilator_trace_line = verilator_trace.readline()

            pc_e, asm_e, instr = parse_etiss_line(etiss_trace_line)
            try:
                pc_v, asm_v, cycles_v, delta_v = parse_verilator_line(
                    verilator_trace_line
                )
            except:
                print("Ouch")
                raise ParseException

            if pc_e == addresses["e_end"] or pc_v == addresses["v_end"]:
                if pc_e != addresses["e_end"]:
                    print("Did not reach end on ETISS")
                if pc_v != addresses["v_end"]:
                    print("Did not reach end on Verilator")
                break

            running_cycles_v = cycles_v
            n_instrs += 1

            timing_split = timing_line.strip().split(",")
            cycles_e = int(timing_split[timing_stage_index])
            delta_e = cycles_e - cycles_e_prev

            delta_diff = delta_e - delta_v
            if delta_diff != 0:
                nonzero_diffs = nonzero_diffs + 1
            sum_diff = sum_diff + abs(delta_diff)

            cycles_e_prev = cycles_e

            if write_match:
                match_file.write(
                    f"{pc_e:08x} | {instr:10} | {asm_e:08x} | {asm_v:08x} | dE: {delta_e:4} | dV: {delta_v:4} | diff: {delta_diff:4} | "
                )
                stage_str = "".join(
                    [
                        f"{stage}: {timing_split[stages[stage]]} | "
                        for stage in stages_to_print
                    ]
                )
                match_file.write(stage_str + "\n")

        total_cycles_e = cycles_e_prev - cycles_e_start
        total_cycles_v = running_cycles_v - cycles_v_start
        cpi_e = total_cycles_e / n_instrs
        cpi_v = total_cycles_v / n_instrs

    if not keep_traces:
        pass
        # Delete traces
        # verilator_trace_path.unlink()
        # etiss_trace_path.unlink()
        # etiss_timing_path.unlink()

    return (CmpResult(cpi_e, cpi_v, sum_diff, n_instrs), True)


def compare_fast(
    etiss_dump_file: pathlib.Path,
    verilator_dump_file: pathlib.Path,
    etiss_timing_file: pathlib.Path,
    etiss_trace_file: pathlib.Path,
    verilator_trace_file: pathlib.Path,
    match_file: pathlib.Path,
) -> tuple[CmpResult, bool]:

    addresses, ok_addresses = read_addresses(verilator_dump_file, etiss_dump_file)

    if not ok_addresses:
        return (0, 0, 0, 0, 0, False)

    return analyze_traces(
        etiss_timing_file,
        etiss_trace_file,
        verilator_trace_file,
        match_file,
        addresses,
        write_match=True,
        keep_traces=False,
        print_stages=True,
    )
