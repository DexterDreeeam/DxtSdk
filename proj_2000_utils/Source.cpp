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