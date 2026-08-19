#include <complex>
#include <cstdlib>
#include <iostream>
#include <stdexcept>
#include <string>

#include "quantum/algorithms/Deutsch.h"
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

void test_x_prepares_deutsch_initial_state() {
    quantum::QuantumState state(quantum::kDeutschQubitCount);
    quantum::Simulator::apply_gate(
        state, quantum::make_x(quantum::kDeutschAuxiliaryQubit));

    check(state.amplitude(0) == std::complex<double>(0.0, 0.0),
          "执行 X(aux) 后 |00> 幅度为 0");
    check(state.amplitude(1) == std::complex<double>(1.0, 0.0),
          "X(q0)|00> = |01>，得到 Deutsch 初态");
}

void test_x_is_self_inverse() {
    quantum::QuantumState state(quantum::kDeutschQubitCount);
    const quantum::Gate x = quantum::make_x(quantum::kDeutschAuxiliaryQubit);
    quantum::Simulator::apply_gate(state, x);
    quantum::Simulator::apply_gate(state, x);

    check(state.amplitude(0) == std::complex<double>(1.0, 0.0),
          "X·X|00> = |00>");
    check(state.amplitude(1) == std::complex<double>(0.0, 0.0),
          "执行两次 X 后 |01> 幅度为 0");
}

void test_x_on_input_qubit() {
    quantum::QuantumState state(quantum::kDeutschQubitCount);
    quantum::Simulator::apply_gate(state, quantum::make_x(quantum::kDeutschInputQubit));

    check(state.amplitude(2) == std::complex<double>(1.0, 0.0),
          "X(q1)|00> = |10>");
}

void test_x_swaps_all_two_qubit_pairs() {
    quantum::QuantumState state(quantum::kDeutschQubitCount);
    state.amplitude(0) = std::complex<double>(0.1, 0.0);
    state.amplitude(1) = std::complex<double>(0.0, 0.2);
    state.amplitude(2) = std::complex<double>(0.3, 0.0);
    state.amplitude(3) = std::complex<double>(0.0, 0.4);

    quantum::Simulator::apply_gate(
        state, quantum::make_x(quantum::kDeutschAuxiliaryQubit));

    check(state.amplitude(0) == std::complex<double>(0.0, 0.2), "X(q0) 交换 |00> 与 |01>");
    check(state.amplitude(1) == std::complex<double>(0.1, 0.0), "X(q0) 完成第一对交换");
    check(state.amplitude(2) == std::complex<double>(0.0, 0.4), "X(q0) 交换 |10> 与 |11>");
    check(state.amplitude(3) == std::complex<double>(0.3, 0.0), "X(q0) 完成第二对交换");
}

void test_invalid_target() {
    quantum::QuantumState state(quantum::kDeutschQubitCount);
    bool threw = false;
    try {
        quantum::Simulator::apply_gate(state, quantum::make_x(2));
    } catch (const std::invalid_argument&) {
        threw = true;
    }
    check(threw, "Deutsch 两比特状态拒绝 q2");
}

}  // namespace

int main() {
    test_x_prepares_deutsch_initial_state();
    test_x_is_self_inverse();
    test_x_on_input_qubit();
    test_x_swaps_all_two_qubit_pairs();
    test_invalid_target();

    if (failures == 0) {
        std::cout << "test_x_gate: 两比特 Deutsch 场景全部测试通过\n";
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " 项测试失败\n";
    return EXIT_FAILURE;
}
