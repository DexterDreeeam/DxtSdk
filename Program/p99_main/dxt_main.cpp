#include "../p00_sdk/ext_sdk_interface.hpp"

int main()
{
    std::safe_selectee<int, 8, true> sl;
    sl.get();
    sl.put(0);
    std::safe_queue<int, 16, 4> sq;
    return 0;
}
