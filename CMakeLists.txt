cmake_minimum_required(VERSION 3.16)
project(AudioMoon)

set(CMAKE_CXX_STANDARD 17)

add_subdirectory(libs)
add_library( AudioMoon STATIC src/data/AudioFile.h src/data/AudioObject.h src/data/PlayerObject.h src/audio/AudioPlayer.cpp src/audio/AudioPlayer.h)

target_link_libraries( AudioMoon PUBLIC OpenAL )
target_include_directories( AudioMoon PUBLIC src )

add_subdirectory( examples )
