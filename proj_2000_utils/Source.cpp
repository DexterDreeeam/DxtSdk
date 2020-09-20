#include "ext_utils_interface.hpp"

using namespace std;

int main()
{
    tick_start();

    vector<string> vs;
    vs.push_back("ok");
    vs.push_back("bu ok");

    for (auto &s : vs)
    {
        print("%s\n", s.c_str());
    }

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

    string s = "134abccccc";
    string s2 = "890a" + s;

    s2 += "  123";

    if ("134abccccc" == s)
    {
        print("ojbk\n");
    }

    for (auto itr = s2.cbegin(); itr != s2.cend(); ++itr)
    {
        print("%c\n", *itr);
    }

    print("%s\n", s2.c_str());

    tick_elapse_print();

    print("========================================\n");

    unordered_map<int, int> mymap;

    for (int i = 0; i < 1000; ++i)
    {
        if (i == 16)
        {
            ++i;
            --i;
        }
        mymap[i] = i + 100;
    }

    for (int i = 0; i < 1000; ++i)
    {
        if (i % 10 == 2)
        {
            mymap.erase(mymap.find(i));
        }
    }

    for (auto itr = mymap.begin(); itr != mymap.end(); ++itr)
    {
        print("%d : %d\n", itr->first, itr->second);
    }
    print("========================================\n");

    unordered_set<int> myset;
    for (int i = 0; i < 2000; ++i)
    {
        myset.insert(i);
    }

    for (int i = 10; i < 2000; i += 10)
    {
        myset.erase(myset.find(i));
    }

    for (int i : myset)
    {
        print("%d\n", i);
    }

    print("========================================\n");
    return 0;
}