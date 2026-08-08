# cpp-quantum-circuit-simulator

基于 C++ 的轻量级量子线路仿真与可追踪优化平台。
在普通电脑上模拟 1-10 个量子比特的小规模量子线路，实现基础线路优化与优化过程追踪。

## 目录结构

```
app/cli/main.cpp        命令行程序入口（main 函数）
include/                公开头文件（.h）
src/core/               核心实现文件（.cpp）
tests/                  自动化测试
```

## 构建（直接使用 g++，无需 CMake）

```bash
g++ -std=c++20 -Wall -Wextra -g -static app/cli/main.cpp src/core/QuantumState.cpp -I include -o quantum_simulator.exe
```

在 VS Code 中按 `Ctrl+Shift+B` 即可构建。

## 运行

```bash
./quantum_simulator.exe
```

## 测试

```bash
g++ -std=c++20 -Wall -Wextra -g -static tests/test_state.cpp src/core/QuantumState.cpp -I include -o test_state.exe
./test_state.exe
```

在 VS Code 中可通过"构建测试程序"和"运行测试"任务执行。
