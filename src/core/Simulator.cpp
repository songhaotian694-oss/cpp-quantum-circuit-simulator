#include "quantum/core/Simulator.h"

#include "quantum/gates/SingleQubitGate.h"

#include <stdexcept>

namespace quantum {

void Simulator::apply_gate(QuantumState& state, const Gate& gate) {
    switch (gate.type) {
        case GateType::X:
            if (!gate.controls.empty() || gate.targets.size() != 1) {
                throw std::invalid_argument("X gate must have exactly one target and no control");
            }
            gates::apply_x(state, gate.targets[0]);
            return;
        case GateType::Z:
            if (!gate.controls.empty() || gate.targets.size() != 1) {
                throw std::invalid_argument("Z gate must have exactly one target and no control");
            }
            gates::apply_z(state, gate.targets[0]);
            return;
        case GateType::H:
            if (!gate.controls.empty() || gate.targets.size() != 1) {
                throw std::invalid_argument("H gate must have exactly one target and no control");
            }
            gates::apply_h(state, gate.targets[0]);
            return;
        case GateType::CNOT:
            throw std::logic_error("CNOT gate execution is not implemented yet");
    }
    throw std::logic_error("unknown gate type");
}

}  // namespace quantum
