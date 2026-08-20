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

void test_z_keeps_zero() {
    quantum::QuantumState state(1);
    quantum::Simulator::apply_gate(state, quantum::make_z(0));

    check(state.amplitude(0) == std::complex<double>(1.0, 0.0),
          "Z|0> = |0>");
}

void test_z_flips_one_phase() {
    quantum::QuantumState state(1);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_z(0));

    check(state.amplitude(1) == std::complex<double>(-1.0, 0.0),
          "Z|1> = -|1>");
}

void test_z_is_self_inverse() {
    quantum::QuantumState state(1);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_z(0));
    quantum::Simulator::apply_gate(state, quantum::make_z(0));

    check(state.amplitude(0) == std::complex<double>(0.0, 0.0),
          "Z*Z|1> 不改变振幅");
    check(state.amplitude(1) == std::complex<double>(1.0, 0.0),
          "Z*Z|1> = |1>");
}

void test_z_flips_phase_on_target_one() {
    quantum::QuantumState state(2);
    state.amplitude(0) = std::complex<double>(0.1, 0.0);
    state.amplitude(1) = std::complex<double>(0.2, 0.0);
    state.amplitude(2) = std::complex<double>(0.3, 0.0);
    state.amplitude(3) = std::complex<double>(0.4, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_z(0));

    check(state.amplitude(0) == std::complex<double>(0.1, 0.0), "Z(q0) 不改变 |00>");
    check(state.amplitude(1) == std::complex<double>(-0.2, 0.0), "Z(q0) 翻转 |01> 相位");
    check(state.amplitude(2) == std::complex<double>(0.3, 0.0), "Z(q0) 不改变 |10>");
    check(state.amplitude(3) == std::complex<double>(-0.4, 0.0), "Z(q0) 翻转 |11> 相位");
}

void test_z_on_second_qubit() {
    quantum::QuantumState state(2);
    state.amplitude(0) = std::complex<double>(0.1, 0.0);
    state.amplitude(1) = std::complex<double>(0.2, 0.0);
    state.amplitude(2) = std::complex<double>(0.3, 0.0);
    state.amplitude(3) = std::complex<double>(0.4, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_z(1));

    check(state.amplitude(0) == std::complex<double>(0.1, 0.0), "Z(q1) 不改变 |00>");
    check(state.amplitude(1) == std::complex<double>(0.2, 0.0), "Z(q1) 不改变 |01>");
    check(state.amplitude(2) == std::complex<double>(-0.3, 0.0), "Z(q1) 翻转 |10> 相位");
    check(state.amplitude(3) == std::complex<double>(-0.4, 0.0), "Z(q1) 翻转 |11> 相位");
}

void test_invalid_target() {
    quantum::QuantumState state(2);
    bool threw = false;
    try {
        quantum::Simulator::apply_gate(state, quantum::make_z(2));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "两比特状态拒绝 q2");
}

}  // namespace

int main() {
    test_z_keeps_zero();
    test_z_flips_one_phase();
    test_z_is_self_inverse();
    test_z_flips_phase_on_target_one();
    test_z_on_second_qubit();
    test_invalid_target();

    if (failures == 0) {
        std::cout << "test_z_gate: Z 门测试全部通过\n";
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " 项测试失败\n";
    return EXIT_FAILURE;
}
