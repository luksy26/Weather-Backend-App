cmake_minimum_required(VERSION 3.10)
project(WeatherSubscriptionApp)

set(CMAKE_CXX_STANDARD 17)

# Define a common library for shared code
add_library(WeatherLib
    WeatherServer.cpp
    WeatherClient.cpp
)

target_include_directories(WeatherLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

# Demo executable
add_executable(demo main.cpp)
target_link_libraries(demo WeatherLib)

# Latency testing executable
add_executable(test_latency test_latency.cpp)
target_link_libraries(test_latency WeatherLib)

# Throughput testing executable
add_executable(test_throughput test_throughput.cpp)
target_link_libraries(test_throughput WeatherLib)

# Resource usage testing executable
add_executable(test_resource_usage test_resource_usage.cpp)
target_link_libraries(test_resource_usage WeatherLib)
