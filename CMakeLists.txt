cmake_minimum_required(VERSION 3.22.3)

set(CMAKE_CXX_STANDARD 20)

project(ParryView)

add_subdirectory(vendor/webview EXCLUDE_FROM_ALL)

set(JSON_BuildTests OFF CACHE INTERNAL "")
add_subdirectory(vendor/nlohmann_json EXCLUDE_FROM_ALL)

if (CMAKE_BUILD_TYPE STREQUAL "Release")
    set(DB_PRODUCTION_MODE ON)
endif ()
add_subdirectory(vendor/embed EXCLUDE_FROM_ALL)

add_executable(ParryView main.cpp)

b_embed(ParryView test.js)
target_compile_features(ParryView PRIVATE cxx_std_20)
target_link_libraries(ParryView PRIVATE webview::core nlohmann_json::nlohmann_json)