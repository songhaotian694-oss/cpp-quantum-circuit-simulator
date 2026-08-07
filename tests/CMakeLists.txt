add_executable(test_state test_state.cpp)
target_link_libraries(test_state PRIVATE quantum_core)
add_test(NAME test_state COMMAND test_state)