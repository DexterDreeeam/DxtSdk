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
    for (int i = 10; i < 15; ++i)
    {
        q.push(i);
    }

    while (q.size())
    {
        print("%d\n", q.front());
        q.pop();
    }

    tick_elapse_print();

    string s = "134abccccc";
    string s2 = "890a" + s;

    s2 += "  123";

    if ("134abccccc" == s)
    {
        print("ojbk\n");
    }

    for (auto itr = s2.crbegin(); itr != s2.crend(); ++itr)
    {
        print("%c\n", *itr);
    }

    print("%s\n", s2.c_str());

    tick_elapse_print();

    return 0;
}