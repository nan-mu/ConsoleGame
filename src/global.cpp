#include "global.h"

std::random_device seed;
std::ranlux48 engine(seed());
std::uniform_int_distribution<> randChar(97, 122);
std::uniform_int_distribution<> randNum(1, 9);

/// @brief 根据长度生成随机数
long randNumber(int length) {
    std::string res = "";
    for (size_t i = 0; i < length; i++) res += std::to_string(randNum(engine));
    return std::stol(res);
}

/// @brief
/// 冒泡排序，将目标数组的下标存入另一个数组，该数组按照目标数组元素的大小从大到小重排，优点是复杂度为O(n)到O(n^2)
/// @param arr 目标数组
void bubbleSortRank(const std::vector<int>& _arr, std::vector<int>& res) {
    int i;
    std::vector<int> arr(_arr);
    for (int ii = 0; ii < arr.size(); ii++) res.push_back(ii);  // 初始化rank
    for (bool j = true; j;) {
        j = false;
        for (i = 1; i < arr.size(); i++) {
            if (arr[i] > arr[i - 1]) {  // 两变量交换并交换排序
                tSwap(&arr[i], &arr[i - 1]);
                tSwap(&res[i], &res[i - 1]);
                j = true;
            }
        }
    }
    std::vector<int>().swap(arr);  // 释放临时数组
}

/// @brief 交换两变量
template <class T>
void tSwap(T* p1, T* p2) {
    T temp = *p1;
    *p1 = *p2;
    *p2 = temp;
}