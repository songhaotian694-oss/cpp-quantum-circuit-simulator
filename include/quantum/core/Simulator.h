#pragma once

#include "quantum/core/Circuit.h"
#include "quantum/core/Gate.h"
#include "quantum/core/QuantumState.h"

namespace quantum {

// 状态向量仿真器。它只负责执行门和线路，不负责算法判断或界面显示。
class Simulator {
public:
    // 从 |00...0> 开始执行整条线路并返回最终状态。
    static QuantumState run(const Circuit& circuit);

    // 在已有状态上执行一个门，供单元测试和算法模块复用。
    static void apply_gate(QuantumState& state, const Gate& gate);
};

}  // namespace quantum
