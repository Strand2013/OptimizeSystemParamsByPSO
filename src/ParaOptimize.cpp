//
// Created by surui1 on 2017/9/8.
//

#include "../include/ParaOptimize.h"
#include <iostream>
#include <limits.h>

using namespace std;


//Pso const operator-(Pso &a, Pso &b)
//{
//    Pso pso;
//    pso.para["u1"] = a.para["u1"] - b.para["u1"];
//    return pso;
//}

//void Pso::asdd(map<string, float> &a, map<string, float> &b)
//{
////    map<string, float> c;
////    c["u1"] = a["u1"] - b["u1"];
////    c["u2"] = a["u2"] - b["u2"];
////    c["u3"] = a["u3"] - b["u3"];
////    c["u4"] = a["u4"] - b["u4"];
////    c["u5"] = a["u5"] - b["u5"];
////    c["u6"] = a["u6"] - b["u6"];
////    c["d1"] = a["d1"] - b["d1"];
////    c["d2"] = a["d2"] - b["d2"];
////    c["d3"] = a["d3"] - b["d3"];
////    c["d4"] = a["d4"] - b["d4"];
////    c["d5"] = a["d5"] - b["d5"];
////    c["d6"] = a["d6"] - b["d6"];
//
////    return c;
//    map<string, float>::iterator iter1;
//    map<string, float>::iterator iter2;
//    iter2 = b.begin();
//    for(iter1 = a.begin(); iter1 != a.end(); iter1++)
//    {
//        iter1->second = iter1->second - iter2->second;
//        iter2++;
//
//    }
////    return a;
//}


map<string, float> Pso::psoProcess(map<string, float> paraMap)
{
    // 初始化数据（人群）
    cout<<"initialize people ..."<<endl;
    vector<float> peopleList = util.generateProbablility(this->peopleNums);
    vector<map<string, float>> paraList;
    vector<vector<float>> velocityList;
    vector<float> fitnessList;
    // 种群初始化（位置， 速度， 当前适应度）
    for(int i = 0; i < this->sizepop; i++)
    {
        // vector没有给定一个长度，那么如果直接对其某个位置进行插值，则会报错 segmentation fault
        paraList.push_back(this->initializeParameter());
        velocityList.push_back(this->initializeVelocity());
        fitnessList.push_back(this-> fitnessFunction(paraList[i], peopleList));
    }
    // 寻优
    pair<int,float> bestfitness;
    bestfitness = this->findmin(fitnessList); // 当前的最优适应度和解的位置

    map<string, float> gbest;            // 群体最优解
    gbest = paraList[bestfitness.first];

    vector<map<string, float> > pbest;   // 个体历史最优解
    pbest = paraList;

    vector<float> fitnesspbest;          //  个体历史最优值
    fitnesspbest = fitnessList;

    float fitnessgbest;                  //  群体最优值
    fitnessgbest = bestfitness.second;

    // 返回的 loss 值
    vector<float> lossList;
    // 更新参数用
    vector<int> indexList;

    cout<<"finding optimal parameter ..."<<endl;
    for(int i = 0; i < this->maxgen; i++)
    {
        // 更新参数
        for(int j = 0; j < this->sizepop; j++)
        {
            // 需要对运算符进行重载 (map + map) (map - map) (map * 数字) (map = map) (数字 * vector)
            // 更新速度列表
            velocityList[j] = vectorAddMap(velocityList[j], mapaddition(mapDeduction(c1*util.runif(), pbest[j], paraList[j]), mapDeduction(c2*util.runif(), gbest, paraList[j])));
            indexList = findExceedList(velocityList[j], this->vmax);
            modifyList(velocityList[j], indexList, this->vmax);
            indexList = findBackwardList(velocityList[j], this->vmin);
            modifyList(velocityList[j], indexList, this->vmin);
            // 更新参数列表
            paraList[j] = updateParaList(velocityList[j], 0.5, paraList[j]);

            indexList = findExceedList(paraList[j], this->popmax);
            modifyList(paraList[j], indexList, this->popmax);
            indexList = findBackwardList(paraList[j], this->popmin);
            modifyList(paraList[j], indexList, this->popmin);

            detectParaList(paraList[j]);

            // 计算适应度
            fitnessList[j] = fitnessFunction(paraList[j], peopleList);
        }
        // 更新适应度函数的极值
        for(int j = 0; j < this->sizepop; j++)
        {
            // 保证个体存储的是历史出现的最优值
            if(fitnessList[j] < fitnesspbest[j])
            {
                pbest[j] = paraList[j];
                fitnesspbest[j] = fitnessList[j];
            }

            if (fitnessList[j] < fitnessgbest)
            {
                gbest = paraList[j];
                fitnessgbest = fitnessList[j];
            }
        }
        map<string, float>::iterator iter;
        for(iter = gbest.begin(); iter != gbest.end(); iter++)
        {
            float temp = iter->second;
            cout<<iter->first<<" : "<<temp<<endl;
        }
        // 输出参数
        cout<<"\n ~~~ loss : "<<fitnessgbest<<"\n"<<endl;
        lossList.push_back(fitnessgbest);
        if(i % 5 == 0 )
        {
            cout<<"-----------------\n";
            cout<<"--- Iter : "<<i<<" ---"<<endl;
            cout<<"-----------------\n";
        }
    }
    // write lossList (画图)
    // write gbest (参数)
    // print parameter and loss
    cout<<"Optimal Parameter final: "<<endl;
    map<string, float>::iterator iter;
    for(iter = gbest.begin(); iter != gbest.end(); iter++)
    {
        float temp = iter->second;
        cout<<iter->first<<" : "<<temp<<endl;
    }
    cout<<"\n\n";
    cout<<"loss : ";
    for(auto l:lossList)
    {
        cout<<l<<" ";
    }
    return gbest;
}

float Pso::fitnessFunction(map<string, float> paraMap, vector<float> peopleList)
{
    if(peopleList.empty())
    {
        cout<<"[ERROR] fitnessFunction peopleList is Null !"<<endl;
        return 0.0;
    }
    float result;
    float score_mean;
    float score_std;
    float temp;
    vector<float> scoreList;
    int len = (int) peopleList.size();
//    cout<< ">>> wait simulate marking ..."<<endl;
    // 做成多线程
    for(int i = 0; i < len; i++)
    {
        // labelNums是模拟一个人的打标次数
        temp = this->func.totalGrade(peopleList[i], this->labelNums, paraMap);
        scoreList.push_back(temp);
    }
    score_mean = this->util.calc_mean(scoreList);
    score_std = this->util.calc_std(scoreList);

    result = (float) (0.9 * sqrt((score_mean - 35) * (score_mean - 35)) + 0.1 * sqrt((score_std - 15) * (score_std - 15)));

    return result;
}

map<string, float> Pso::initializeParameter()
{
    map<string, float> paraMap;
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<signed> disU(1, 1000000);
    static uniform_int_distribution<signed> disD(-3000000, -1);
    disU(e);
    disD(e);
    // 随机初始化参数
    paraMap["u1"] = (float) (disU(e)/1000000.0);
    paraMap["d1"] = (float) (disD(e)/1000000.0);
    paraMap["u2"] = (float) (disU(e)/1000000.0);
    paraMap["d2"] = (float) (disD(e)/1000000.0);
    paraMap["u3"] = (float) (disU(e)/1000000.0);
    paraMap["d3"] = (float) (disD(e)/1000000.0);
    paraMap["u4"] = (float) (disU(e)/1000000.0);
    paraMap["d4"] = (float) (disD(e)/1000000.0);
    paraMap["u5"] = (float) (disU(e)/1000000.0);
    paraMap["d5"] = (float) (disD(e)/1000000.0);
    paraMap["u6"] = (float) (disU(e)/1000000.0);
    paraMap["d6"] = (float) (disD(e)/1000000.0);

    return paraMap;
}

vector<float> Pso::initializeVelocity()
{
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<signed> disV(-1000000, 1000000);
    disV(e);
    vector<float> vList;
    float v ;
    for(int i = 0; i < this->paraNum; i++ )
    {
        v = (float)(disV(e) / 1000000.0);
        vList.push_back(v);
    }

    return vList;
}

void Pso::detectParaList(map<string, float> &ParaList)
{
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<signed> disP(1, 1000000);
    disP(e);
    if(ParaList["u1"] <= 0)
    {
        ParaList["u1"] = (float)(disP(e) / 1000000.0);
    }
    if(ParaList["u2"] <= 0)
    {
        ParaList["u2"] = (float)(disP(e) / 1000000.0);
    }
    if(ParaList["u3"] <= 0)
    {
        ParaList["u3"] = (float)(disP(e) / 1000000.0);
    }
    if(ParaList["u4"] <= 0)
    {
        ParaList["u4"] = (float)(disP(e) / 1000000.0);
    }
    if(ParaList["u5"] <= 0)
    {
        ParaList["u5"] = (float)(disP(e) / 1000000.0);
    }
    if(ParaList["u6"] <= 0)
    {
        ParaList["u6"] = (float)(disP(e) / 1000000.0);
    }
    if(ParaList["d1"] >= 0)
    {
        ParaList["d1"] = (float)(disP(e) / -1000000.0);
    }
    if(ParaList["d2"] >= 0)
    {
        ParaList["d2"] = (float)(disP(e) / -1000000.0);
    }
    if(ParaList["d3"] >= 0)
    {
        ParaList["d3"] = (float)(disP(e) / -1000000.0);
    }
    if(ParaList["d4"] >= 0)
    {
        ParaList["d4"] = (float)(disP(e) / -1000000.0);
    }
    if(ParaList["d5"] >= 0)
    {
        ParaList["d5"] = (float)(disP(e) / -1000000.0);
    }
    if(ParaList["d6"] >= 0)
    {
        ParaList["d6"] = (float)(disP(e) / -1000000.0);
    }
}

pair<int, float> Pso::findmin(vector<float> fitness)
{
    float min = (float)INT_MAX;
    int index = 0;
    int minIndex = 0;
    for(auto pop:fitness)
    {
        if(min > pop)
        {
            min = pop;
            minIndex = index;
        }
        index += 1;
    }
    return make_pair(minIndex, min);
}

vector<int> Pso::findExceedList(vector<float> inputList, float const flag)
{
    vector<int> outputList;
    int len = (int) inputList.size();
    for (int i = 0; i < len; i++)
    {
        if(inputList[i] > flag)
        {
            outputList.push_back(i);
        }
    }
    return outputList;
}

vector<int> Pso::findExceedList(map<string, float> inputList, float const flag)
{
    vector<int> outputList;
    map<string, float>::iterator iter;
    int index = 0;
    for (iter = inputList.begin(); iter != inputList.end(); iter++)
    {
        if(iter->second > flag)
        {
            outputList.push_back(index);
        }
        index += 1;
    }
    return outputList;
}


vector<int> Pso::findBackwardList(vector<float> inputList, float const flag)
{
    vector<int> outputList;
    int len = (int) inputList.size();
    for (int i = 0; i < len; i++)
    {
        if(inputList[i] < flag)
        {
            outputList.push_back(i);
        }
    }
    return outputList;
}

vector<int> Pso::findBackwardList(map<string, float> inputList, float const flag)
{
    vector<int> outputList;
    map<string, float>::iterator iter;
    int index = 0;
    for (iter = inputList.begin(); iter != inputList.end(); iter++)
    {
        if(iter->second < flag)
        {
            outputList.push_back(index);
        }
        index += 1;
    }
    return outputList;
}

void Pso::modifyList(vector<float> &inputList, vector<int> indexList, float const flag)
{
    if(indexList.empty())
    {
        return;
    }
    for(auto index : indexList)
    {
        inputList[index] = flag;
    }
}


void Pso::modifyList(map<string, float> &inputList, vector<int> indexList, float const flag)
{
    if(indexList.empty())
    {
        return;
    }
    map<string, float>::iterator iter;
    for(iter = inputList.begin(); iter != inputList.end(); iter++)
    {
        iter->second = flag;
    }
}

map<string, float> Pso::updateParaList(vector<float> vec, float coef, map<string, float> paraList)
{
    if(vec.empty())
    {
        cout<<"[Error]:updateParaList"<<endl;
        return paraList;
    }
    map<string, float>::iterator iter;
    iter = paraList.begin();
    for(auto v:vec)
    {
        iter->second = (coef * v + iter->second);
        iter++;
    }
    return paraList;
}

vector<float> Pso::vectorAddMap(vector<float> vec, map<string,float> paraMap)
{
    vector<float> resultVec;
    if(vec.empty())
    {
        cout<<"[Error]:vectorAddMap"<<endl;
        return resultVec;
    }
    float temp;
    map<string, float>::iterator iter;
    iter = paraMap.begin();
    for(auto v:vec)
    {
        temp = v + iter->second;
        resultVec.push_back(temp);
        iter++;
    }
    return resultVec;
}

map<string, float> Pso::mapDeduction(float coef, map<string, float> map1, map<string, float> map2 )
{
    map<string, float>::iterator iter1;
    map<string, float>::iterator iter2;
    iter2 = map2.begin();
    for(iter1 = map1.begin(); iter1 != map1.end(); iter1++)
    {
        iter1->second = coef*(iter1->second - iter2->second);
        iter2++;
    }
    return map1;
}

map<string, float> Pso::mapaddition(map<string, float> map1, map<string, float> map2)
{
    map<string, float>::iterator iter1;
    map<string, float>::iterator iter2;
    iter2 = map2.begin();
    for(iter1 = map1.begin(); iter1 != map1.end(); iter1++)
    {
        iter1->second = iter1->second + iter2->second;
        iter2++;
    }
    return map2;
}


//Pso Pso::test(map<string, float> &a, map<string, float> &b)
//{
//    Pso p1;
//    Pso p2;
//    p1.para = a;
//    p2.para = b;
//    return p1-p2;
//};

//friend map<string,float> map::operator-(map<string, float> map1, map<string, float> map2)
//{
//    map<string, float>::iterator iter1;
//    map<string, float>::iterator iter2;
//    iter2 = map2.begin();
//    for(iter1 = map1.begin(); iter1 != map1.end(); iter1++)
//    {
//        iter1->second = iter1->second - iter2->second;
//        iter2++;
//    }
//    return map1;
//
//}

//map<string, float> test(map<string, float> a, map<string, float> b)
//{
//    map<string, float> c;
//    c = a-b;
//    return c;
//}