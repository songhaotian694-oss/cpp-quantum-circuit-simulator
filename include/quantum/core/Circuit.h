#pragma once

#include <cstddef>
#include <vector>

#include "quantum/core/Gate.h"

namespace quantum {

// 固定量子比特数、按执行顺序保存量子门的线路。
class Circuit {
public:
    explicit Circuit(int qubit_count);

    int qubit_count() const { return qubit_count_; }
    std::size_t size() const { return gates_.size(); }
    bool empty() const { return gates_.empty(); }

    const Gate& gate(std::size_t index) const;
    const std::vector<Gate>& gates() const { return gates_; }

    void add_gate(const Gate& gate);
    void clear();

private:
    // 校验门的结构和量子比特下标；非法输入抛 std::invalid_argument。
    void validate_gate(const Gate& gate) const;

    int qubit_count_;
    std::vector<Gate> gates_;
};

}  // namespace quantum
