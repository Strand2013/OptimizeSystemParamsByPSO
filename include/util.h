//
// Created by surui1 on 2017/9/8.
//
#include <vector>
#include <math.h>
#include <time.h>
#include <random>
using namespace std;

#ifndef ZBOPERATION_UTIL_H
#define ZBOPERATION_UTIL_H

class Util
{
public:
    float calc_mean(vector<float> resultList);
    float calc_std(vector<float> resultList);

    // 模拟一次打标实验的结果
    bool oneTest(float probability);

    // 用一个概率值来生成单个用户，个体
    vector<float> generateProbablility(int nums);

    // 生成0-1的随机数
    float runif();
};

#endif //ZBOPERATION_UTIL_H
