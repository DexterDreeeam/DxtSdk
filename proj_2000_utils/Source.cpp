#include "ext_utils_interface.hpp"

using namespace std;

int main()
{

    stack<int> stk = { 1,2,3,4,5,6 };

    for (int i : stk)
    {
        print("%d\n", i);
    }

    stk.push(7);
    stk.push(8, 9);

    print("---------------------------\n");

    auto stk2 = stk;

    for (int i : stk)
    {
        print("%d\n", i);
    }

    print("---------------------------\n");

    for (int i : stk2)
    {
        print("%d\n", i);
    }

    vector<int> cands = { 1,5,2,3,3,9,4,7,8,6 };

    tick_start();

    vector<int> vec;

    set<int> ss;

    ss.insert(10000);
    ss.insert(-1);

    ss.clear();

    for (int i = 0; i <= 1000; ++i)
    {
        ss.insert(i);
    }

    for (int i = 2; i < 1000; i += 2)
    {
        auto itr = ss.find(i);
        ss.erase(itr);
    }

    print("---------------------------\n");

    for (auto itr = ss.cbegin(); itr != ss.cend(); ++itr)
    {
        print("%d\n", *itr);
    }

    for (int i = 0; i <= 1000; ++i)
    {
        ss.erase(i);
    }

    tick_elapse_print();

    return 0;

    //for (int i = 0; i < 10000000; ++i)
    //{
    //    int v = random(10000007);
    //    vec.push_back(v);
    //    ss.insert(v);
    //}

    //for (int i : vec)
    //{
    //    ss.erase(i);
    //}

    //int time = tick_elapse();
    //++time;

    //for (int i = 0; i < vec2.size(); ++i)
    //{
    //    print("vec2[%d] is %d\n", i, vec2[i]);
    //}

    ////print("vec2 capacity is %lld\n", vec2.capacity());

    //vec2.clear();

    //vec2.push_back(1000,1000,2000);

    //for (int i = 0; i < vec2.size(); ++i)
    //{
    //    print("vec2[%d] is %d\n", i, vec2[i]);
    //}

    //print("vec2 size %d", vec2.size());

    //print("---------------------------\n");

    //vec2.insert(1,5,3,5,6,100);

    //for (int i = 0; i < vec2.size(); ++i)
    //{
    //    print("vec2[%d] is %d\n", i, vec2[i]);
    //}

    //print("---------------------------\n");

    //vec2.erase(4,2);

    //for (int i = 0; i < vec2.size(); ++i)
    //{
    //    print("vec2[%d] is %d\n", i, vec2[i]);
    //}
    //print("---------------------------\n");
    //for (auto itr = vec2.crbegin(); itr != vec2.crend(); ++itr)
    //{
    //    print("%d\n", *itr);
    //}
    //print("---------------------------\n");
    //for (int &i : vec2)
    //{
    //    print("%d\n", i);
    //}

    return 0;
}