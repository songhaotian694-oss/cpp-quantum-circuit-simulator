# cpp-quantum-circuit-simulator

基于 C++ 的轻量级量子线路仿真与可追踪优化平台。
在普通电脑上模拟 1—10 个量子比特的小规模量子线路，实现基础线路优化与优化过程追踪。

## 目录结构

```
include/quantum/  公开头文件（.h）
src/              实现文件（.cpp）
app/cli/          命令行程序入口
app/gui/          Qt 界面程序入口（待开发）
tests/            自动化测试
examples/         使用示例
benchmark/        实验数据
docs/             设计文档与记录
third_party/      第三方依赖说明
```

## 构建

```bash
cmake -S . -B build
cmake --build build
```

## 测试

```bash
ctest --test-dir build --output-on-failure
```