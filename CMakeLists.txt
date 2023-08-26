cmake_minimum_required(VERSION 3.13)
project(AllayBE)
set(CMAKE_CXX_STANDARD 14)

file(GLOB SOURCE
	src/*.cpp
	src/nbt/*.cpp
	src/nbt/list/*.cpp
	src/misc/*.cpp
	src/player/*.cpp
	src/console/*.cpp
	src/managers/*.cpp
	src/network/raknet/*.cpp
	src/network/minecraft/packets/*.cpp
	src/network/minecraft/handlers/*.cpp
)

set(SOURCE_FILES ${SOURCE})

if (CMAKE_BUILD_TYPE MATCHES Debug)
	if (UNIX AND NOT WIN32)
		set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
		set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=address -fno-omit-frame-pointer")
  	endif()
endif()

add_executable(AllayBE ${SOURCE_FILES})

add_subdirectory(RakNet)
add_subdirectory(zlib)

include_directories(RakNet/Source)
include_directories(zlib)
include_directories(include)

target_link_libraries(AllayBE PRIVATE
	RakNetLibStatic
	zlib
)
