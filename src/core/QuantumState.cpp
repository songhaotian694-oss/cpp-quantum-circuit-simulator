#include "quantum/core/QuantumState.h"

#include <cmath>
#include <stdexcept>

namespace quantum {

QuantumState::QuantumState(int qubit_count) : qubit_count_(qubit_count) {
    if (qubit_count < 1) {
        throw std::invalid_argument("qubit_count must be >= 1");
    }
    amplitudes_.assign(std::size_t(1) << qubit_count, std::complex<double>(0.0, 0.0));
    amplitudes_[0] = std::complex<double>(1.0, 0.0);  // 初始为 |00...0>
}

const std::complex<double>& QuantumState::amplitude(std::size_t index) const {
    return amplitudes_.at(index);
}

std::complex<double>& QuantumState::amplitude(std::size_t index) {
    return amplitudes_.at(index);
}

void QuantumState::normalize() {
    double sum = 0.0;
    for (const auto& a : amplitudes_) {
        sum += std::norm(a);
    }
    if (sum <= 0.0) {
        throw std::runtime_error("cannot normalize a zero state");
    }
    const double scale = 1.0 / std::sqrt(sum);
    for (auto& a : amplitudes_) {
        a *= scale;
    }
}

}  // namespace quantum