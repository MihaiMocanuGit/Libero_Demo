add_subdirectory(EcsDefs)
add_library(src STATIC UnitFactory.hpp UnitFactory.cpp)
target_link_libraries(src PUBLIC EcsDef)
set_target_properties(src PROPERTIES LINKER_LANGUAGE CXX)
