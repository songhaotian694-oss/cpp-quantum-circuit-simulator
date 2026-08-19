#pragma once

namespace quantum {

// Deutsch 算法固定使用两个量子比特和四个一位布尔函数。
enum class DeutschOracle {
    ConstantZero,  // f(0)=0, f(1)=0
    ConstantOne,   // f(0)=1, f(1)=1
    Identity,      // f(0)=0, f(1)=1，即 f(x)=x
    Negation,      // f(0)=1, f(1)=0，即 f(x)=1-x
};

enum class DeutschFunctionClass {
    Constant,
    Balanced,
};

// Qt 和 CLI 只接收算法结果，不接触线路内部的两个量子比特。
struct DeutschResult {
    DeutschOracle oracle = DeutschOracle::ConstantZero;
    DeutschFunctionClass function_class = DeutschFunctionClass::Constant;
    double input_zero_probability = 0.0;
    double input_one_probability = 0.0;
};

// 固定算法约定（仅供说明和测试读取）：
//   q1 = 输入比特，初始为 0；q0 = 辅助比特，初始为 1；基态显示为 |01>。
inline constexpr int kDeutschQubitCount = 2;
inline constexpr int kDeutschInputQubit = 1;
inline constexpr int kDeutschAuxiliaryQubit = 0;

// 唯一的算法入口：调用方只选择 Oracle，量子比特数量和初态均由算法内部固定。
DeutschResult run_deutsch(DeutschOracle oracle);

// CLI、Qt 下拉框和测试报告共用的文本转换接口。
const char* deutsch_oracle_name(DeutschOracle oracle);
const char* deutsch_function_class_name(DeutschFunctionClass function_class);
DeutschFunctionClass expected_function_class(DeutschOracle oracle);

}  // namespace quantum
