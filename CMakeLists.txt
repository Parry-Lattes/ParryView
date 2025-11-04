cmake_minimum_required(VERSION 4.0)
set(CMAKE_CXX_STANDARD 20)
set(JSON_BuildTests OFF CACHE INTERNAL "")

project(ParryView)

add_subdirectory(vendor/webview EXCLUDE_FROM_ALL)
add_subdirectory(vendor/nlohmann_json EXCLUDE_FROM_ALL)

add_executable(ParryView main.cpp)
target_compile_features(ParryView PRIVATE cxx_std_20)
target_link_libraries(ParryView PRIVATE webview::core nlohmann_json::nlohmann_json)