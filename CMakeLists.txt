cmake_minimum_required(VERSION 3.25)

project(bagla-engine VERSION 0.1 DESCRIPTION "the simplest sfml extension library")

add_library(bagla-engine
	"include/bagla-engine/states/State.h" 
	"include/bagla-engine/states/StateManager.h"
	"src/states/StateManager.cpp"
	"include/bagla-engine/gui/Widget.h"
	"include/bagla-engine/gui/Button.h" 
	"include/bagla-engine/asset-manager/AssetManager.h" 
	"src/asset-manager/AssetManager.cpp" 
	"src/gui/Button.cpp")

target_include_directories(bagla-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/bagla-engine)

find_package(SFML COMPONENTS system window graphics audio network CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)

target_link_libraries(bagla-engine PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
target_link_libraries(bagla-engine PRIVATE spdlog::spdlog spdlog::spdlog_header_only)

set_target_properties(bagla-engine PROPERTIES VERSION 0)
set_target_properties(bagla-engine PROPERTIES SOVERSION 1)
