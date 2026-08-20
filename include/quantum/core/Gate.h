#pragma once

#include <string>
#include <vector>

namespace quantum {

// 当前竖切只需要 X、Y、Z、H、CNOT；后续增加量子门时无需修改 Gate 的数据结构。
enum class GateType {
    X,
    Y,
    Z,
    H,
    CNOT,
};

// 量子门的纯数据表示。核心层不包含任何 Qt 类型。
struct Gate {
    GateType type = GateType::X;
    std::vector<int> controls;
    std::vector<int> targets;

    // 返回该门涉及的全部量子比特，控制位在前、目标位在后。
    std::vector<int> acted_qubits() const;
    // 用于 CLI、测试日志和 Qt 展示，例如 "H(q1)"。
    std::string to_string() const;
};

// 统一使用工厂函数构造合法门，调用方不直接拼装 controls/targets。
Gate make_x(int target);
Gate make_y(int target);
Gate make_z(int target);
Gate make_h(int target);
Gate make_cnot(int control, int target);

}  // namespace quantum
