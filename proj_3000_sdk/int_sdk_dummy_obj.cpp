#include "ext_sdk_interface.hpp"

void _int_sdk_dummy_func()
{
}

struct abc
{

};

int main()
{
    std::selectee<int, 8> sl;

    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());
    print("%d\n", sl.get());

    sl.put(3);
    sl.put(7);
    sl.put(4);
    sl.put(2);
    sl.put(6);
    sl.put(0);
    sl.put(1);
    sl.put(5);

    return 0;
}
