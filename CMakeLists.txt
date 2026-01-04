cmake_minimum_required(VERSION 3.15)
project(low-latency-market-data-feed CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -march=native -Wall -Wextra -pthread")

include_directories(include)

add_executable(feed_handler
    src/main.cpp
    src/feed_parser.cpp
    src/market_event.cpp
)

target_link_libraries(feed_handler pthread)
