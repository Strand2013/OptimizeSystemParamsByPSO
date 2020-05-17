//
// Created by surui1 on 2017/9/8.
//
#include <vector>
#include <map>
#include "util.h"
using namespace std;

#ifndef ZBOPERATION_AIMFUNCTION_H
#define ZBOPERATION_AIMFUNCTION_H
class AimFunction
{

public:
    float totalGrade(float probability, int iteration, map<string, float> paraMap);
    float intervalGrade(float score, float probability, float up, float down);

private:
    Util util;
};
#endif //ZBOPERATION_AIMFUNCTION_H
