cmake_minimum_required(VERSION 4.0)
project(AQ_DB)

set(CMAKE_CXX_STANDARD 14)

include_directories(src/storage)

add_executable(AQ_DB
        src/storage/Shard.cpp
        src/storage/Shard.h
        src/storage/KVStore.cpp
        src/storage/KVStore.h
        src/main.cpp
)
