#include <complex>
#include <cstdlib>
#include <iostream>

#include "quantum/core/QuantumState.h"

namespace {

int failures = 0;

void check(bool condition, const char* message) {
    if (!condition) {
        std::cerr << "FAIL: " << message << '\n';
        ++failures;
    }
}

}  // namespace

int main() {
    quantum::QuantumState state(2);

    check(state.qubit_count() == 2, "2 个量子比特");
    check(state.size() == 4, "状态向量长度为 4");
    check(state.amplitude(0) == std::complex<double>(1.0, 0.0), "初始态为 |00>");
    check(std::norm(state.amplitude(1)) == 0.0, "|01> 概率幅为 0");

    state.amplitude(0) = std::complex<double>(3.0, 0.0);
    state.amplitude(1) = std::complex<double>(4.0, 0.0);
    state.normalize();
    check(std::abs(std::norm(state.amplitude(0)) + std::norm(state.amplitude(1)) - 1.0) < 1e-12,
          "归一化后概率和为 1");

    if (failures == 0) {
        std::cout << "全部测试通过" << '\n';
        return EXIT_SUCCESS;
    }
    std::cerr << failures << " 项测试失败" << '\n';
    return EXIT_FAILURE;
}