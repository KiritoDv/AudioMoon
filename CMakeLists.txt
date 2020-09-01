cmake_minimum_required(VERSION 3.16)
project(audio_lib)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)
add_library( audio_lib STATIC src/data/AudioFile.h src/data/AudioObject.h src/data/PlayerObject.h src/audio/AudioPlayer.cpp src/audio/AudioPlayer.h)

target_link_libraries( audio_lib PUBLIC OpenAL )
target_include_directories( audio_lib PUBLIC src )

add_subdirectory( examples )