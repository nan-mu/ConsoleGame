#pragma once
// 引用库和部分函数

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

long randNumber(int length);  // 随机字符串
void bubbleSortRank(const std::vector<int>& _arr, std::vector<int>& res);
template <class T>
void tSwap(T* p1, T* p2);
