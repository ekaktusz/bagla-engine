cmake_minimum_required(VERSION 3.25)

set(CMAKE_TOOLCHAIN_FILE "${CMAKE_CURRENT_SOURCE_DIR}/vendor/vcpkg/scripts/buildsystems/vcpkg.cmake"
  CACHE STRING "Vcpkg toolchain file")

project(bagla-engine VERSION 0.1 DESCRIPTION "the simplest sfml extension library")

# Add subdirectories
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/tmxlite)

# Define source files
set(SOURCES
    src/states/StateManager.cpp
    src/asset-manager/AssetManager.cpp
    src/gui/Button.cpp
    src/gui/CheckBox.cpp
    src/gui/Slider.cpp
    src/gui/FocusLock.cpp
    src/map/ObjectLayer.cpp
    src/map/Map.cpp
    src/map/TileLayer.cpp
    src/map/TileLayerChunk.cpp
    src/physics/RigidBody.cpp
    src/physics/ContactListener.cpp
    src/physics/PhysicsWorld.cpp
    src/physics/DebugDraw.cpp
    src/camera/Camera.cpp
    src/animation/Animation.cpp
    src/animation/AnimationContainer.cpp
    src/graphics/RoundedRectangleShape.cpp
    src/states/StateTransition.cpp
    src/graphics/ParallaxLayer.cpp
    src/graphics/ParallaxBackground.cpp
)

# Define header files
set(HEADERS
    include/bagla-engine/states/State.h
    include/bagla-engine/states/StateManager.h
    include/bagla-engine/gui/Widget.h
    include/bagla-engine/gui/Button.h
    include/bagla-engine/asset-manager/AssetManager.h
    include/bagla-engine/map/Map.h
    include/bagla-engine/map/ObjectLayer.h
    include/bagla-engine/map/TileLayer.h
    include/bagla-engine/camera/Camera.h
    include/bagla-engine/GameObject.h
    include/bagla-engine/EventHandler.h
    include/bagla-engine/physics/RigidBody.h
    include/bagla-engine/gui/CheckBox.h
    include/bagla-engine/gui/Slider.h
    include/bagla-engine/gui/FocusLock.h
    include/bagla-engine/MathExtensions.h
    include/bagla-engine/physics/ContactListener.h
    include/bagla-engine/physics/PhysicsWorld.h
    include/bagla-engine/physics/DebugDraw.h
    include/bagla-engine/animation/Animation.h
    include/bagla-engine/animation/AnimationContainer.h
    include/bagla-engine/graphics/RoundedRectangleShape.h
    include/bagla-engine/states/StateTransition.h
    include/bagla-engine/graphics/ParallaxBackground.h
    include/bagla-engine/graphics/ParallaxLayer.h
)

# Create library
add_library(bagla-engine ${SOURCES} ${HEADERS} "include/bagla-engine/IEventHandler.h")

# Set include directories
target_include_directories(bagla-engine PUBLIC 
    ${CMAKE_CURRENT_SOURCE_DIR}/include/bagla-engine
    ${CMAKE_CURRENT_SOURCE_DIR}/vendor/tmxlite/include
)

# Find and link required packages
find_package(SFML COMPONENTS system window graphics audio network CONFIG REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)

target_link_libraries(bagla-engine PRIVATE 
    sfml-system sfml-network sfml-graphics sfml-window sfml-audio
    spdlog::spdlog spdlog::spdlog_header_only
    tmxlite
    box2d::box2d
)

# Set library properties
set_target_properties(bagla-engine PROPERTIES 
    VERSION 0
    SOVERSION 1
)