#include <cmath>
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

void check_close(double actual, double expected, const std::string& message) {
    check(std::abs(actual - expected) < 1e-12, message);
}

void test_h_on_zero() {
    quantum::QuantumState state(1);
    quantum::Simulator::apply_gate(state, quantum::make_h(0));

    const double inv = 1.0 / std::sqrt(2.0);
    check_close(state.amplitude(0).real(), inv, "H|0> 的 |0> 振幅为 1/sqrt(2)");
    check_close(state.amplitude(0).imag(), 0.0, "H|0> 的 |0> 振幅无虚部");
    check_close(state.amplitude(1).real(), inv, "H|0> 的 |1> 振幅为 1/sqrt(2)");
    check_close(state.amplitude(1).imag(), 0.0, "H|0> 的 |1> 振幅无虚部");
}

void test_h_on_one() {
    quantum::QuantumState state(1);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_h(0));

    const double inv = 1.0 / std::sqrt(2.0);
    check_close(state.amplitude(0).real(), inv, "H|1> 的 |0> 振幅为 1/sqrt(2)");
    check_close(state.amplitude(1).real(), -inv, "H|1> 的 |1> 振幅为 -1/sqrt(2)");
}

void test_h_is_self_inverse() {
    quantum::QuantumState state(1);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_h(0));
    quantum::Simulator::apply_gate(state, quantum::make_h(0));

    check_close(state.amplitude(0).real(), 0.0, "H*H|1> 的 |0> 振幅为 0");
    check_close(state.amplitude(1).real(), 1.0, "H*H|1> 的 |1> 振幅为 1");
}

void test_h_on_two_qubits() {
    quantum::QuantumState state(2);
    quantum::Simulator::apply_gate(state, quantum::make_h(0));

    const double inv = 1.0 / std::sqrt(2.0);
    check_close(state.amplitude(0).real(), inv, "H(q0)|00> 的 |00> 振幅为 1/sqrt(2)");
    check_close(state.amplitude(1).real(), inv, "H(q0)|00> 的 |01> 振幅为 1/sqrt(2)");
    check_close(state.amplitude(2).real(), 0.0, "H(q0)|00> 的 |10> 振幅为 0");
    check_close(state.amplitude(3).real(), 0.0, "H(q0)|00> 的 |11> 振幅为 0");
}

void test_invalid_target() {
    quantum::QuantumState state(2);
    bool threw = false;
    try {
        quantum::Simulator::apply_gate(state, quantum::make_h(2));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "两比特状态拒绝 q2");
}

}  // namespace

int main() {
    test_h_on_zero();
    test_h_on_one();
    test_h_is_self_inverse();
    test_h_on_two_qubits();
    test_invalid_target();

    if (failures == 0) {
        std::cout << "test_h_gate: H 门测试全部通过\n";
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " 项测试失败\n";
    return EXIT_FAILURE;
}
