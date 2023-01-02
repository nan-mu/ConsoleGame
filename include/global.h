#pragma once
// 引用库和部分函数

#include <functional>
#include <iostream>
#include <random>
#include <string>
#include <vector>

long randNumber(int length);  // 随机字符串
template <class T>
void bubbleSortRank(const std::vector<T>& _arr, std::vector<int>& res);
template <class T>
void tSwap(T* p1, T* p2);