#pragma once

#include "quantum/core/QuantumState.h"

namespace quantum {
namespace gates {

// 在 target 指定的量子比特上执行 Pauli-X 门。
void apply_x(QuantumState& state, int target);

}  // namespace gates
}  // namespace quantum
