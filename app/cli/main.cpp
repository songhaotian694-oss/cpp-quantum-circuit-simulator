#include <iostream>

#include "quantum/core/QuantumState.h"

int main() {
    quantum::QuantumState state(2);

    std::cout << "量子比特数: " << state.qubit_count() << '\n';
    std::cout << "状态向量长度: " << state.size() << '\n';
    std::cout << "|00> 概率幅: " << state.amplitude(0).real()
              << " + " << state.amplitude(0).imag() << "i\n";

    return 0;
}