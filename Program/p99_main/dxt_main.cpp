#include "p00_sdk/ext_sdk_interface.hpp"
#include "p05_window/ext_window_interface.hpp"

using namespace dxt;

boole should_stop = boole_false;

void __WindowEventCbFunc(const window_event &evnt)
{
    log("receive %s event", window_event_type_cstr[(s64)evnt.Type()]);
    if (evnt.Type() == window_event_type::window_close)
    {
        should_stop = boole_true;
    }
}

int main()
{
    tick_start();
    AUTO_TRACE;

    std::safe_selectee<int, 8, true> sl;
    sl.get();
    sl.put(0);
    std::safe_queue<int, 16, 4> sq;

    dxt::window_desc wd = {};
    wd.name = "DexterDream";
    wd.width = 800;
    wd.height = 500;
    wd.cb = __WindowEventCbFunc;

    auto *p = new dxt::windows_window(wd);

    s64 cnt = 0;

    tick_sleep(2000);

    delete p;

    windows_ns::system("pause");

    return 0;
}
