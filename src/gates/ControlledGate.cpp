#include "quantum/gates/ControlledGate.h"

#include <cstddef>
#include <stdexcept>
#include <utility>

namespace quantum {
namespace gates {

void apply_cnot(QuantumState& state, int control, int target) {
    if (control < 0 || control >= state.qubit_count() ||
        target < 0 || target >= state.qubit_count()) {
        throw std::invalid_argument("CNOT control or target is out of range");
    }
    if (control == target) {
        throw std::invalid_argument("CNOT control and target must differ");
    }

    const std::size_t control_mask = std::size_t(1) << control;
    const std::size_t target_mask = std::size_t(1) << target;
    for (std::size_t index = 0; index < state.size(); ++index) {
        if (((index & control_mask) != 0) && ((index & target_mask) == 0)) {
            std::swap(state.amplitude(index), state.amplitude(index | target_mask));
        }
    }
}

}  // namespace gates
}  // namespace quantum
