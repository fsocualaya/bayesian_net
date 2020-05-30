cmake_minimum_required(VERSION 3.15)
project(bayesian_network)

set(CMAKE_CXX_STANDARD 14)

set(CMAKE_CXX_FLAGS -fpermissive)

add_executable(bayesian_network main.cpp
        not_pandas.cpp
        variable.cpp
        bayesian_net.cpp
        )