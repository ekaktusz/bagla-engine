cmake_minimum_required(VERSION 3.25)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(bagla-engine VERSION 0.1 DESCRIPTION "the simplest sfml extension library")

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/tmxlite)

add_library(bagla-engine
	"include/bagla-engine/states/State.h" 
	"include/bagla-engine/states/StateManager.h"
	"src/states/StateManager.cpp"
	"include/bagla-engine/gui/Widget.h"
	"include/bagla-engine/gui/Button.h" 
	"include/bagla-engine/asset-manager/AssetManager.h" 
	"src/asset-manager/AssetManager.cpp" 
	"src/gui/Button.cpp" 
	"include/bagla-engine/map/Map.h"
	"include/bagla-engine/map/ObjectLayer.h"
	"include/bagla-engine/map/TileLayer.h"
	"src/map/ObjectLayer.cpp"
	"src/map/Map.cpp" 
	"src/map/TileLayer.cpp" 
	"src/map/TileLayerChunk.cpp" 
	"include/bagla-engine/camera/Camera.h" 
	"include/bagla-engine/GameObject.h" "include/bagla-engine/physics/RigidBody.h" "src/physics/RigidBody.cpp" "include/bagla-engine/gui/CheckBox.h" "src/gui/CheckBox.cpp" "include/bagla-engine/gui/Slider.h" "src/gui/Slider.cpp" "include/bagla-engine/gui/FocusLock.h" "include/bagla-engine/MathExtensions.h" "src/gui/FocusLock.cpp")

target_include_directories(bagla-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include/bagla-engine)
target_include_directories(bagla-engine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/vendor/tmxlite/include)


find_package(SFML COMPONENTS system window graphics audio network CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

target_link_libraries(bagla-engine PRIVATE sfml-system sfml-network sfml-graphics sfml-window sfml-audio)
target_link_libraries(bagla-engine PRIVATE spdlog::spdlog spdlog::spdlog_header_only)
target_link_libraries(bagla-engine PRIVATE tmxlite)
target_link_libraries(bagla-engine PRIVATE box2d::box2d)

set_target_properties(bagla-engine PROPERTIES VERSION 0)
set_target_properties(bagla-engine PROPERTIES SOVERSION 1)
