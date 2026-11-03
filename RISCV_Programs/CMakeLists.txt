cmake_minimum_required(VERSION 3.10)

set(CMAKE_SKIP_INSTALL_ALL_DEPENDENCY ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS On)

project(riscv_examples LANGUAGES ASM C CXX)

set(VERILATOR OFF CACHE BOOL "Compile for Verilator")
set(SCALAR_FLOAT OFF CACHE BOOL "Scalar core has FPU")

# set(MEM_ROM_ORIGIN 0x10000000)
# set(MEM_ROM_LENGTH 0x00400000)
# set(MEM_RAM_ORIGIN 0x20000000)
# set(MEM_RAM_LENGTH 0x00100000)

set(MEM_ROM_ORIGIN 0x00100000)
set(MEM_ROM_LENGTH 0x00400000)
set(MEM_RAM_ORIGIN 0x00600000)
set(MEM_RAM_LENGTH 0x00100000)

set(MIN_STACK_SIZE 0x1000)
set(MIN_HEAP_SIZE 0x1000)

configure_file(etiss.ld.in etiss.ld @ONLY)
configure_file(verilator.ld.in verilator.ld @ONLY)
configure_file(memsegs.ini.in memsegs.ini @ONLY)

set(ETISS_LDSCRIPT ${CMAKE_CURRENT_BINARY_DIR}/etiss.ld)
set(VERILATOR_LDSCRIPT ${CMAKE_CURRENT_BINARY_DIR}/verilator.ld)
set(LIBS_DIR "${PROJECT_SOURCE_DIR}/libs")

set(VERILATOR_LDFLAGS "-nostartfiles -T ${VERILATOR_LDSCRIPT}")
if(CMAKE_CXX_COMPILER_ID MATCHES "(C|c?)lang")
	set(ETISS_LDFLAGS "-nostdlib -lc -lsemihost -lgcc -lstdc++ -L${CMAKE_CURRENT_BINARY_DIR}/riscv_crt0 -T ${ETISS_LDSCRIPT}")
else()
	set(ETISS_LDFLAGS "-L${CMAKE_CURRENT_BINARY_DIR}/riscv_crt0 --specs=${CMAKE_CURRENT_SOURCE_DIR}/etiss-semihost.specs -T ${ETISS_LDSCRIPT}")
endif()

if(VERILATOR)
	set(LDFLAGS ${VERILATOR_LDFLAGS})
elseif(ETISS)
	set(LDFLAGS ${ETISS_LDFLAGS})
else()
	set(LDFLAGS "")
endif()

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${LDFLAGS}")
set(ETISS_ELFINI ${CMAKE_CURRENT_SOURCE_DIR}/elffile.ini.in)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

add_subdirectory(riscv_crt0)
add_subdirectory(verilator_bsp)
add_subdirectory(target_code)
