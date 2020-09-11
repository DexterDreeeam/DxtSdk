#include "ext_utils_interface.hpp"

using namespace std;

int main()
{

    list<int> l2;
    {
        list<int> l1 = { 100, 1000 };
        l1.push_front(1,2,3,4,5,6,7);

        //while (l1.size())
        //{
        //    print("%d\n", l1.front());
        //    l1.pop_front();
        //}

        print("///////////////////");

        l2 = right_value_type(l1);

        print("///////////////////\n");
        while (l1.size())
        {
            print("%d\n", l1.front());
            l1.pop_front();
        }

    }
    print("///////////////////\n");
    while (l2.size())
    {
        print("%d\n", l2.front());
        l2.pop_front();
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