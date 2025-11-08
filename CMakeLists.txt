cmake_minimum_required (VERSION 3.20)

project(
	pvrtc
	VERSION 1.0.0
	LANGUAGES CXX
)

add_library(
		${PROJECT_NAME} STATIC
		Rgba32.h
		Rgba32.cpp
		ColorRGBA.h
		ColorRGBA.cpp
		ColorRGB.cpp
		ColorRGB.h
		Packet.cpp
		Packet.h
		Morton.cpp
		Morton.h
		Common.cpp
		Common.h
		Encode.cpp
		Encode.h
		Decode.cpp
		Decode.h
)

target_include_directories(${PROJECT_NAME} INTERFACE 
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
    $<INSTALL_INTERFACE:include>
)

set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)