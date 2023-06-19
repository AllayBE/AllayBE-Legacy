cmake_minimum_required(VERSION 3.13)
project(AllayBE)
set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE
	src/*.cpp
	src/misc/*.cpp
	src/player/*.cpp
	src/console/*.cpp
	src/network/raknet/*.cpp
	src/network/minecraft/packets/*.cpp
)

set(SOURCE_FILES ${SOURCE})

add_executable(AllayBE ${SOURCE_FILES})

add_subdirectory(RakNet)

include_directories(RakNet/Source)
include_directories(include)

target_link_libraries(AllayBE PRIVATE RakNetLibStatic)