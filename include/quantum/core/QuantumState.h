#pragma once

#include <complex>
#include <cstddef>
#include <vector>

namespace quantum {

// 量子态：以状态向量表示，长度 2^n。
class QuantumState {
public:
    explicit QuantumState(int qubit_count);

    int qubit_count() const { return qubit_count_; }
    std::size_t size() const { return amplitudes_.size(); }

    const std::complex<double>& amplitude(std::size_t index) const;
    std::complex<double>& amplitude(std::size_t index);

    // 归一化：所有概率幅模平方之和为 1。
    void normalize();

private:
    int qubit_count_;
    std::vector<std::complex<double>> amplitudes_;
};

}  // namespace quantum