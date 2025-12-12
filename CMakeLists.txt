cmake_minimum_required(VERSION 3.20)
project(AQ_DB)

# --------------------
# C++20
# --------------------
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# --------------------
# Homebrew prefix
# --------------------
set(CMAKE_PREFIX_PATH "/opt/homebrew")

# --------------------
# Find Boost headers only
# --------------------
find_package(Boost CONFIG REQUIRED)

# --------------------
# Executable
# --------------------
add_executable(AQ_DB
        src/main.cpp
        src/server/server.cpp
        src/server/connection.cpp
        src/storage/Shard.cpp
        src/storage/KVStore.cpp
)

# --------------------
# Includes
# --------------------
target_include_directories(AQ_DB PRIVATE
        src/server
        src/storage
)

# --------------------
# Disable Boost.System dependency
# --------------------
target_compile_definitions(AQ_DB PRIVATE
        BOOST_ASIO_DISABLE_BOOST_SYSTEM
)

# --------------------
# Link Boost headers
# --------------------
target_link_libraries(AQ_DB PRIVATE
        Boost::boost
)
