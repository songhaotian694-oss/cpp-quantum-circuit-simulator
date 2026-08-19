#include "quantum/core/Gate.h"

#include <sstream>

namespace quantum {

std::vector<int> Gate::acted_qubits() const {
    std::vector<int> qubits = controls;
    qubits.insert(qubits.end(), targets.begin(), targets.end());
    return qubits;
}

std::string Gate::to_string() const {
    std::ostringstream output;
    switch (type) {
        case GateType::X:
            output << "X(q" << targets.at(0) << ')';
            break;
        case GateType::H:
            output << "H(q" << targets.at(0) << ')';
            break;
        case GateType::CNOT:
            output << "CNOT(q" << controls.at(0) << " -> q" << targets.at(0) << ')';
            break;
    }
    return output.str();
}

Gate make_x(int target) {
    Gate gate;
    gate.type = GateType::X;
    gate.targets = {target};
    return gate;
}

Gate make_h(int target) {
    Gate gate;
    gate.type = GateType::H;
    gate.targets = {target};
    return gate;
}

Gate make_cnot(int control, int target) {
    Gate gate;
    gate.type = GateType::CNOT;
    gate.controls = {control};
    gate.targets = {target};
    return gate;
}

}  // namespace quantum
