//
// Created by surui1 on 2017/9/8.
//

#include "../include/AimFunction.h"
#include <iostream>
using namespace std;

float AimFunction::totalGrade(float probability, int iteration, map<string, float> paraMap)
{
    float score = 30.0;
    int i = 0;
    bool result;
    while(i < iteration)
    {
        if(score > 0 && score <= 10)
        {
            score = intervalGrade(score, probability, paraMap["u1"], paraMap["d1"]);
        }
        else if(score > 10 && score <= 20)
        {
            score = intervalGrade(score, probability, paraMap["u2"], paraMap["d2"]);
        }
        else if(score > 20 && score <= 30)
        {
            score = intervalGrade(score, probability, paraMap["u3"], paraMap["d3"]);
        }
        else if(score > 30 && score <= 40)
        {
            score = intervalGrade(score, probability, paraMap["u4"], paraMap["d4"]);
        }
        else if(score > 40 && score <= 50)
        {
            score = intervalGrade(score, probability, paraMap["u5"], paraMap["d5"]);
        }
        else{
            score = intervalGrade(score, probability, paraMap["u6"], paraMap["d6"]);
        }
        i++;
    }
    return score;
}

float AimFunction::intervalGrade(float score, float probability, float up, float down)
{
    bool isRight;
    isRight = this->util.oneTest(probability);
    (isRight)? score += up : score += down;
    return score;
}