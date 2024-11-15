cmake_minimum_required(VERSION 3.10)
project(WeatherSubscriptionApp)

set(CMAKE_CXX_STANDARD 17)

# Add the executable
add_executable(WeatherApp
    WeatherServer.cpp
    WeatherClient.cpp
    main.cpp
)
