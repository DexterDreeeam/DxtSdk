#include "ext_utils_interface.hpp"

using namespace std;

int main()
{
    tick_start();

    map<int, int> mm;
    mm.insert(1, 1);
    mm.insert(make_pair(2,4));
    mm.insert(8LL, -1);

    mm[8] = 10000;
    mm[-800] = 0;
    mm[100000];

    mm.erase(8);
    mm.erase(mm.find(1));

    pair<int, long long> p = make_pair(-1, 0.0);

    print("map size is : %d\n", mm.size());

    for (auto itr = mm.begin(); itr != mm.end(); ++itr)
    {
        print("itr->first : %d, itr->second : %d.\n", itr->first, itr->second);
    }

    tick_elapse_print();

    queue<int> q = { 2,3,4 };
    for (int i = 100; i < 150; ++i)
    {
        q.push(i);
    }

    while (q.size())
    {
        print("%d\n", q.front());
        q.pop();
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