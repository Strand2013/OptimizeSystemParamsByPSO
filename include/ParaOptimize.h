//
// Created by surui1 on 2017/9/8.
//

#include <string>
#include <math.h>
#include "AimFunction.h"
using namespace std;


#ifndef ZBOPERATION_PARAOPTIMIZE_H
#define ZBOPERATION_PARAOPTIMIZE_H

//class map<string, float>{
//    friend map<string,float> operator-(map<string, float> map1, map<string, float> map2);
//    map<string, float> test(map<string, float> a, map<string, float> b);
//};


class Pso{

//    friend const Pso operator-(Pso &a, Pso &b);

public:

    // 限制所有参数 不为零
    // 把加d换成减d
    // 把map换成vector



    Pso(int maxgen, int sizepop)
    {
        this->maxgen = maxgen;
        this->sizepop = sizepop;

    }
    map<string, float> para;

public:
    //test
//    Pso test(map<string, float> &a, map<string, float> &b);
//    void asdd(map<string, float> &a, map<string, float> &b);

    // 粒子群算法
    map<string, float> psoProcess(map<string, float> paraMap);
    // 计算目标函数
    float fitnessFunction(map<string, float> paraMap, vector<float> peopleList);


private:
    Util util;
    AimFunction func;
    int maxgen;    // 迭代次数
    int sizepop;    // 种群规模
    int peopleNums = 10;
    int labelNums = 10000;
    int paraNum = 12;    // 参数个数
    float c1 = 1.4955;   // 速度更新参数1
    float c2 = 1.4955;   // 速度更新参数2
    float popmax = 1.0;  // 单个参数的最大值
    float popmin = -3;   // 单个参数的最小值
    float vmax = 1.0;    // 个体速度的最大值
    float vmin = -1;     // 个体速度的最小值


private:
    // 检查参数
    void detectParaList(map<string, float> &ParaList);

    // 数据运算转换
    vector<float> vectorAddMap(vector<float> vec, map<string,float> paraMap);
    map<string, float> updateParaList(vector<float>vec, float coef, map<string, float>paraList);
    map<string, float> mapaddition(map<string, float> map1, map<string, float> map2);
    map<string, float> mapDeduction(float coef, map<string, float> map1, map<string, float> map2 );
    // 初始化参数
    map<string, float> initializeParameter();
    // 初始化速度
    vector<float> initializeVelocity();
    // 找到最小值
    pair<int, float> findmin(vector<float> fitness);
    // 找到大于某个值的 list
    vector<int> findExceedList(vector<float> inputList, float const flag);
    vector<int> findExceedList(map<string, float> inputList, float const flag);
    // 找打小于某个值的 list
    vector<int> findBackwardList(vector<float> inputList, float const flag);
    vector<int> findBackwardList(map<string, float> inputList, float const flag);
    // 修改速度和单个参数防止越界
    void modifyList(vector<float> &inputList, vector<int> indexList, float const flag);
    void modifyList(map<string, float> &inputList, vector<int> indexList, float const flag);


};
#endif //ZBOPERATION_PARAOPTIMIZE_H
