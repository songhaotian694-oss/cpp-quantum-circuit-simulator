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

void test_y_on_zero() {
    quantum::QuantumState state(1);
    quantum::Simulator::apply_gate(state, quantum::make_y(0));

    check(state.amplitude(0) == std::complex<double>(0.0, 0.0),
          "Y|0> 的 |0> 振幅为 0");
    check(state.amplitude(1) == std::complex<double>(0.0, 1.0),
          "Y|0> = i|1>");
}

void test_y_on_one() {
    quantum::QuantumState state(1);
    state.amplitude(0) = std::complex<double>(0.0, 0.0);
    state.amplitude(1) = std::complex<double>(1.0, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_y(0));

    check(state.amplitude(0) == std::complex<double>(0.0, -1.0),
          "Y|1> = -i|0>");
    check(state.amplitude(1) == std::complex<double>(0.0, 0.0),
          "Y|1> 的 |1> 振幅为 0");
}

void test_y_is_self_inverse() {
    quantum::QuantumState state(1);
    quantum::Simulator::apply_gate(state, quantum::make_y(0));
    quantum::Simulator::apply_gate(state, quantum::make_y(0));

    check(state.amplitude(0) == std::complex<double>(1.0, 0.0),
          "Y*Y|0> = |0>");
    check(state.amplitude(1) == std::complex<double>(0.0, 0.0),
          "Y*Y|0> 的 |1> 振幅为 0");
}

void test_y_on_two_qubits() {
    quantum::QuantumState state(2);
    state.amplitude(0) = std::complex<double>(0.1, 0.0);
    state.amplitude(1) = std::complex<double>(0.2, 0.0);
    state.amplitude(2) = std::complex<double>(0.3, 0.0);
    state.amplitude(3) = std::complex<double>(0.4, 0.0);

    quantum::Simulator::apply_gate(state, quantum::make_y(0));

    check(state.amplitude(0) == std::complex<double>(0.0, -0.2),
          "Y(q0) 把 |01> 相位转入 |00>");
    check(state.amplitude(1) == std::complex<double>(0.0, 0.1),
          "Y(q0) 把 |00> 相位转入 |01>");
    check(state.amplitude(2) == std::complex<double>(0.0, -0.4),
          "Y(q0) 把 |11> 相位转入 |10>");
    check(state.amplitude(3) == std::complex<double>(0.0, 0.3),
          "Y(q0) 把 |10> 相位转入 |11>");
}

void test_invalid_target() {
    quantum::QuantumState state(2);
    bool threw = false;
    try {
        quantum::Simulator::apply_gate(state, quantum::make_y(2));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "两比特状态拒绝 q2");
}

}  // namespace

int main() {
    test_y_on_zero();
    test_y_on_one();
    test_y_is_self_inverse();
    test_y_on_two_qubits();
    test_invalid_target();

    if (failures == 0) {
        std::cout << "test_y_gate: Y 门测试全部通过\n";
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " 项测试失败\n";
    return EXIT_FAILURE;
}
