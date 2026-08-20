#pragma once

#include "quantum/core/QuantumState.h"

namespace quantum {
namespace gates {

// 在 control 为 1 时翻转 target 量子比特。
void apply_cnot(QuantumState& state, int control, int target);

}  // namespace gates
}  // namespace quantum
