//
// Created by surui1 on 2017/9/8.
//

#include "../include/util.h"
#include <iostream>

using namespace std;

float Util::calc_mean(vector<float> resultList)
{
    int len = (int) resultList.size();
    if(len == 0)
    {
        return 0.0;
    }
    float result = 0;
    for (int i = 0; i < len; i++)
    {
        result += resultList[i];
    }
    result = result/len;
    return result;
}

float Util::calc_std(vector<float> resultList)
{
    float stdv;
    int len = (int) resultList.size();
    if (len == 0)
    {
        return 0.0;
    }
    float mean = calc_mean(resultList);
    float tempsum = 0;
    for(int i = 0; i < len; i++)
    {
        tempsum = tempsum + (resultList[i] - mean)*(resultList[i] - mean);
    }
    stdv = (float) sqrt(tempsum/len);
    return stdv;
}

bool Util::oneTest(float probability)
{
    float flag = probability * 10000;
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<unsigned> dis(0, 10000);
    dis(e);
    int one = dis(e);
    return flag >= one;
}

// 生成打标群众
vector<float> Util::generateProbablility(int nums)
{
    int i = 0;
    float prob = 0.0;
    vector<float> probList;
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<unsigned> dis(0, 1000);
    cout<< ">>> generating ..."<<endl;
    while( i < nums )
    {
        dis(e);
        int one = dis(e);
        if(one<=100)
        {
            static uniform_int_distribution<unsigned> dis1(8000, 9000);
            dis1(e);
            prob = (float) (dis1(e) / 10000.0);

        }
        else if(one > 100 && one <= 600)
        {
            static uniform_int_distribution<unsigned> dis2(9001, 9500);
            dis2(e);
            prob = (float) (dis2(e) / 10000.0);
        }
        else if(one > 600 && one <= 5900)
        {
            static uniform_int_distribution<unsigned> dis3(9501, 9900);
            dis3(e);
            prob = (float) (dis3(e) / 10000.0);
        }
        else if(one > 5900 && one <= 10000)
        {
            static uniform_int_distribution<unsigned> dis3(9901, 9999);
            dis3(e);
            prob = (float) (dis3(e) / 10000.0);
        }
        probList.push_back(prob);
        i++;
        if(i%1000 == 0)
        {
            cout<<">>> generate 1000 people ..."<<endl;
        }
    }
    cout<<">>> generate finished"<<endl;
    return probList;
}

float Util::runif()
{
    float result;
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<signed> disV(1, 999);
    disV(e);
    result = (float)(disV(e) / 1000.0);
    return result;
}