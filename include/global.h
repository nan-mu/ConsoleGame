#pragma once

#include <chrono>
#include <functional>
#include <iomanip>
#include <iostream>
#include <random>
#include <sstream>
#include <string>
#include <vector>

#include "spdlog/sinks/basic_file_sink.h"
#include "spdlog/spdlog.h"

/// @brief 根据长度生成随机数
long randNumber(int length);
/// @brief
/// 冒泡排序，将目标数组的下标存入另一个数组，该数组按照目标数组元素的大小从大到小重排，优点是复杂度为O(n)到O(n^2)
/// @param arr 目标数组
void bubbleSortRank(const std::vector<int>& _arr, std::vector<int>& res);
/// @brief 交换两变量
template <class T>
void tSwap(T* p1, T* p2);
