#include "quantum/gates/SingleQubitGate.h"

#include <cmath>
#include <complex>
#include <cstddef>
#include <stdexcept>
#include <utility>

namespace quantum {
namespace gates {

void apply_x(QuantumState& state, int target) {
    if (target < 0 || target >= state.qubit_count()) {
        throw std::invalid_argument("X gate target is out of range");
    }

    const std::size_t target_mask = std::size_t(1) << target;
    for (std::size_t index = 0; index < state.size(); ++index) {
        // 仅从目标位为 0 的基态开始交换，保证每对概率幅只处理一次。
        if ((index & target_mask) == 0) {
            std::swap(state.amplitude(index), state.amplitude(index | target_mask));
        }
    }
}

void apply_y(QuantumState& state, int target) {
    if (target < 0 || target >= state.qubit_count()) {
        throw std::invalid_argument("Y gate target is out of range");
    }

    const std::size_t target_mask = std::size_t(1) << target;
    const std::complex<double> i(0.0, 1.0);
    for (std::size_t index = 0; index < state.size(); ++index) {
        if ((index & target_mask) == 0) {
            const std::complex<double> a = state.amplitude(index);
            const std::complex<double> b = state.amplitude(index | target_mask);
            state.amplitude(index) = -i * b;
            state.amplitude(index | target_mask) = i * a;
        }
    }
}

void apply_z(QuantumState& state, int target) {
    if (target < 0 || target >= state.qubit_count()) {
        throw std::invalid_argument("Z gate target is out of range");
    }

    const std::size_t target_mask = std::size_t(1) << target;
    const std::complex<double> minus_one(-1.0, 0.0);
    for (std::size_t index = 0; index < state.size(); ++index) {
        if ((index & target_mask) != 0) {
            state.amplitude(index) *= minus_one;
        }
    }
}

void apply_h(QuantumState& state, int target) {
    if (target < 0 || target >= state.qubit_count()) {
        throw std::invalid_argument("H gate target is out of range");
    }

    const std::size_t target_mask = std::size_t(1) << target;
    const double inv_sqrt_two = 1.0 / std::sqrt(2.0);
    for (std::size_t index = 0; index < state.size(); ++index) {
        if ((index & target_mask) == 0) {
            const std::complex<double> a = state.amplitude(index);
            const std::complex<double> b = state.amplitude(index | target_mask);
            state.amplitude(index) = (a + b) * inv_sqrt_two;
            state.amplitude(index | target_mask) = (a - b) * inv_sqrt_two;
        }
    }
}

}  // namespace gates
}  // namespace quantum
