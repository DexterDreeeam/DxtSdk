#include "p00_sdk/ext_sdk_interface.hpp"
#include "p05_window/ext_window_interface.hpp"

int main()
{
    std::safe_selectee<int, 8, true> sl;
    sl.get();
    sl.put(0);
    std::safe_queue<int, 16, 4> sq;

    dxt::window_desc wd = {};
    wd.name = "123";
    wd.width = 800;
    wd.height = 500;
    wd.cb = nullptr;

    auto *p = new dxt::windows_window(wd);

    return 0;
}
