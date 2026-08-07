cmake_minimum_required(VERSION 3.16)

project(quantum_simulator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_CLI  "Build command-line demo program" ON)
option(BUILD_TESTS "Build automated tests" ON)
option(BUILD_GUI  "Build Qt GUI application" OFF)

# Core library: quantum simulation core (no Qt dependency).
add_library(quantum_core STATIC
    src/core/QuantumState.cpp
    # Add modules here as they are implemented:
    # src/core/QuantumGate.cpp
    # src/core/QuantumCircuit.cpp
    # src/core/Simulator.cpp
    # src/core/Measurement.cpp
    # src/gates/SingleQubitGate.cpp
    # src/gates/TwoQubitGate.cpp
    # src/gates/RotationGate.cpp
    # src/optimizer/GateCancel.cpp
    # src/optimizer/GateMerge.cpp
    # src/optimizer/Optimizer.cpp
    # src/io/CsvExporter.cpp
    # src/algorithms/DeutschJozsa.cpp
    # src/algorithms/BernsteinVazirani.cpp
)

target_include_directories(quantum_core PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

if(BUILD_CLI)
    add_subdirectory(app/cli)
endif()

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()

if(BUILD_GUI)
    add_subdirectory(app/gui)
endif()