cmake_minimum_required(VERSION 4.0)
project(
  Libero_Demo
  VERSION 0.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if(WIN32)
    message(WARNING "Windows is not yet supported. (WIP)")
endif(WIN32)

set(gcc_errors "-Wall -Wextra -Wpedantic")
set(gcc_warninGS "-Wno-error=unused-variable -Wno-error=unused-parameter \
    -Wno-error=unused-function -Wno-error=unused-but-set-variable")
set(gcc_sanitizers "-fsanitize=address,undefined")

set(gcc_flags_debug "-O0 -ggdb3 ${gcc_errors} ${gcc_warnings} ${gcc_sanitizers}")
set(gcc_link_flags_debug "${GCC_SANITIZERS}")

set(gcc_flags_release "-O3 -flto ${gcc_errors} ${gcc_warnings}")
set(gcc_link_flags_release "-flto")
# Profiling Config
#set(gcc_flags_release "-O2 -g ${gcc_errors} ${gcc_warnings}")
#set(gcc_link_flags_release "")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${gcc_flags_debug}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${gcc_link_flags_debug} ")

set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} ${gcc_flags_release}")
set(CMAKE_EXE_LINKER_FLAGS_RELEASE "${CMAKE_EXE_LINKER_FLAGS_RELEASE} ${gcc_link_flags_release} ")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)

add_subdirectory(Libero)

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE src Libero)
