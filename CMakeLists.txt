cmake_minimum_required(VERSION 4.0)
project(
  Libero_Demo
  VERSION 0.0.0
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)

if(WIN32)
    message(WARNING "Windows is not yet supported. (WIP)")
endif(WIN32)

set(GCC_ERRORS "-Wall -Wextra -Wpedantic")
set(GCC_WARNINGS "-Wno-error=unused-variable -Wno-error=unused-parameter \
    -Wno-error=unused-function -Wno-error=unused-but-set-variable")
set(GCC_SANITIZERS "-fsanitize=address,undefined")

set(GCC_FLAGS_DEBUG "-O0 -ggdb3 ${GCC_ERRORS} ${GCC_WARNINGS} ${GCC_SANITIZERS}")
set(GCC_LINK_FLAGS_DEBUG "${GCC_SANITIZERS}")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} ${GCC_FLAGS_DEBUG}")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} ${GCC_LINK_FLAGS_DEBUG} ")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink
    ${CMAKE_BINARY_DIR}/compile_commands.json ${CMAKE_CURRENT_SOURCE_DIR}/compile_commands.json)

add_subdirectory(Libero)
target_compile_definitions(Libero INTERFACE ECS_COMPONENTS_CUSTOM)
target_compile_definitions(Libero INTERFACE ECS_COMPONENTS_CUSTOM_PATH_TYPES="${CMAKE_CURRENT_SOURCE_DIR}/src/EcsComponentsCustomTypes.txt")
target_compile_definitions(Libero INTERFACE ECS_COMPONENTS_CUSTOM_PATH_IMPL="${CMAKE_CURRENT_SOURCE_DIR}/src/EcsComponentsCustomImpl.hxx")

add_subdirectory(src)

add_executable(${PROJECT_NAME} main.cpp)
target_link_libraries(${PROJECT_NAME} PRIVATE src Libero)
