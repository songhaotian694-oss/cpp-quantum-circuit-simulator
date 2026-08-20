#include <complex>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "quantum/core/Gate.h"
#include "quantum/core/QuantumState.h"
#include "quantum/core/Simulator.h"

namespace {

int failures = 0;

void check(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

void check_amplitude(const quantum::QuantumState& state,
                     std::size_t index,
                     std::complex<double> expected,
                     const std::string& message) {
    check(state.amplitude(index) == expected, message);
}

void test_cnot_control_zero_keeps_state() {
    quantum::QuantumState state(2);
    quantum::Simulator::apply_gate(state, quantum::make_cnot(0, 1));

    check_amplitude(state, 0, std::complex<double>(1.0, 0.0), "CNOT(q0->q1)|00> = |00>");
    check_amplitude(state, 1, std::complex<double>(0.0, 0.0), "CNOT(q0->q1)|00> 没有 |01>");
}

void test_cnot_flips_target_when_control_one() {
    quantum::QuantumState state(2);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_cnot(0, 1));

    check_amplitude(state, 1, std::complex<double>(0.0, 0.0), "CNOT(q0->q1)|01> 的 |01> 振幅为 0");
    check_amplitude(state, 3, std::complex<double>(1.0, 0.0), "CNOT(q0->q1)|01> = |11>");
}

void test_cnot_with_control_one() {
    quantum::QuantumState state(2);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(2) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_cnot(1, 0));

    check_amplitude(state, 2, std::complex<double>(0.0, 0.0), "CNOT(q1->q0)|10> 的 |10> 振幅为 0");
    check_amplitude(state, 3, std::complex<double>(1.0, 0.0), "CNOT(q1->q0)|10> = |11>");
}

void test_cnot_swaps_superposition_pairs() {
    quantum::QuantumState state(2);
    state.amplitude(0) = std::complex<double>(0.1, 0.0);
    state.amplitude(1) = std::complex<double>(0.2, 0.0);
    state.amplitude(2) = std::complex<double>(0.3, 0.0);
    state.amplitude(3) = std::complex<double>(0.4, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_cnot(0, 1));

    check_amplitude(state, 0, std::complex<double>(0.1, 0.0), "CNOT 保持 |00>");
    check_amplitude(state, 1, std::complex<double>(0.4, 0.0), "CNOT 把 |11> 振幅交换到 |01>");
    check_amplitude(state, 2, std::complex<double>(0.3, 0.0), "CNOT 保持 |10>");
    check_amplitude(state, 3, std::complex<double>(0.2, 0.0), "CNOT 把 |01> 振幅交换到 |11>");
}

void test_cnot_on_three_qubits() {
    quantum::QuantumState state(3);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_cnot(0, 2));

    check_amplitude(state, 1, std::complex<double>(0.0, 0.0), "3 比特 CNOT 清空原基态");
    check_amplitude(state, 5, std::complex<double>(1.0, 0.0), "3 比特 CNOT 翻转 q2");
}

void test_same_control_and_target() {
    quantum::QuantumState state(2);
    bool threw = false;
    try {
        quantum::Simulator::apply_gate(state, quantum::make_cnot(0, 0));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "CNOT 拒绝 control == target");
}

void test_out_of_range() {
    quantum::QuantumState state(2);
    bool threw = false;
    try {
        quantum::Simulator::apply_gate(state, quantum::make_cnot(2, 0));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "CNOT 拒绝越界控制位");
}

}  // namespace

int main() {
    test_cnot_control_zero_keeps_state();
    test_cnot_flips_target_when_control_one();
    test_cnot_with_control_one();
    test_cnot_swaps_superposition_pairs();
    test_cnot_on_three_qubits();
    test_same_control_and_target();
    test_out_of_range();

    if (failures == 0) {
        std::cout << "test_cnot_gate: CNOT 门测试全部通过\n";
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " 项测试失败\n";
    return EXIT_FAILURE;
}
