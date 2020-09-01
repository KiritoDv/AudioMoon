add_executable( aiff_loader aiff_loader.cpp )

target_link_libraries( aiff_loader audio_lib OpenAL )
set_target_properties( aiff_loader PROPERTIES FOLDER "examples" )

message(STATUS "print_all_variables------------------------------------------{")
message(STATUS "${CMAKE_BINARY_DIR} ${PROJECT_SOURCE_DIR}")

add_custom_command(TARGET aiff_loader POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different "${CMAKE_BINARY_DIR}/libs/OpenAL/OpenAL32.dll" $<TARGET_FILE_DIR:aiff_loader>)