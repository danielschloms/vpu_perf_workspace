# Benchmark / program suites under programs/src/.
#
# Each directory is an independent suite. The hardware-configuration / simulator
# paths are provided by the parent programs/CMakeLists.txt and inherited by the
# subdirs. The embench-iot suite owns its harness runtime under
# embench-iot/runtime (the embench-iot sources themselves are a submodule that
# is left untouched).

# --- embench-iot -----------------------------------------------------------
add_subdirectory(embench-iot)

# --- MLPerfTiny (WIP; opt-in) ----------------------------------------------
# Enabled with -DEMBENCH_MLPERFTINY=ON. Its CMakeLists currently targets the old
# framework build and must be adapted before it can be built by default.
if(EMBENCH_MLPERFTINY)
    add_subdirectory(tiny)
endif()
