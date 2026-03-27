add_library(EcsDef STATIC EcsComponents.hpp EcsBoilerplate.hxx)
set_target_properties(EcsDef PROPERTIES LINKER_LANGUAGE CXX)
target_link_libraries(EcsDef PUBLIC Libero)

add_custom_command(OUTPUT EcsBoilerplate.hxx
    COMMENT "Generating the ECS component boilerplate"
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMAND python generate.py ECS.json
    CODEGEN
    DEPENDS EcsComponents.hpp)

