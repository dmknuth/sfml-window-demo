cmake_minimum_required(VERSION 3.28)
project(GameDemoProject LANGUAGES CXX)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.0.1
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM)
FetchContent_MakeAvailable(SFML)

# ------------------- nlohmann/json (header-only) -------------------
FetchContent_Declare(
    json
    GIT_REPOSITORY https://github.com/nlohmann/json.git
    GIT_TAG v3.11.3          # latest stable
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)
FetchContent_MakeAvailable(json)

# ZeroMQ (system version via Homebrew)
find_package(PkgConfig REQUIRED)
pkg_check_modules(ZMQ REQUIRED libzmq)

add_executable(
    GameDemo
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Shapes.cpp
    src/FpsCounter.cpp
    src/Broadcaster.cpp
)
target_compile_features(GameDemo PRIVATE cxx_std_20)
target_include_directories(GameDemo PRIVATE ${ZMQ_INCLUDE_DIRS})
target_link_directories(GameDemo PRIVATE ${ZMQ_LIBRARY_DIRS})
target_link_libraries(GameDemo PRIVATE SFML::Graphics ${ZMQ_LIBRARIES})
target_link_libraries(GameDemo PRIVATE nlohmann_json::nlohmann_json)
