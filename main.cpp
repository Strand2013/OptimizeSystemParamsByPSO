#include <iostream>
#include <random>
#include<time.h>
#include <map>

#include "include/util.h"
#include "include/ParaOptimize.h"

using namespace std;
int main() {
    Pso pso(50, 20);
    Util util;
    map<string, float> paraMap;

    // 构造随机数
    static default_random_engine e;
    e.seed((unsigned)time(NULL));
    static uniform_int_distribution<signed> disU(0, 1000000);
    static uniform_int_distribution<signed> disD(-1000000, 0);
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

    cout<<"initialize parameter"<<endl;
    cout<<"u1 :"<<paraMap["u1"]<<endl;
    cout<<"u2 :"<<paraMap["u2"]<<endl;
    cout<<"u3 :"<<paraMap["u3"]<<endl;
    cout<<"u4 :"<<paraMap["u4"]<<endl;
    cout<<"u5 :"<<paraMap["u5"]<<endl;
    cout<<"u6 :"<<paraMap["u6"]<<endl;
    cout<<"\n";
    cout<<"d1 :"<<paraMap["d1"]<<endl;
    cout<<"d2 :"<<paraMap["d2"]<<endl;
    cout<<"d3 :"<<paraMap["d3"]<<endl;
    cout<<"d4 :"<<paraMap["d4"]<<endl;
    cout<<"d5 :"<<paraMap["d5"]<<endl;
    cout<<"d6 :"<<paraMap["d6"]<<endl;
    cout<<"\n";
//
//     模拟人群的数量
//    vector<float> peopleList = util.generateProbablility(1000);


//    for(auto prob : peopleList)
//    {
//        cout<<prob<<endl;
//    }

    pso.psoProcess(paraMap);

}