add_executable( aiff_loader aiff_loader.cpp )

target_link_libraries( aiff_loader AudioMoon OpenAL )
set_target_properties( aiff_loader PROPERTIES FOLDER "examples" )

message(STATUS "print_all_variables------------------------------------------{")
message(STATUS "${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}")
