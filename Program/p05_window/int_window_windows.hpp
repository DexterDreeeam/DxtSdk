/* ********* * ********* * ********* * ********* * *********
 *
 * int_window_windows.hpp
 *
 * proj: proj_05_window
 * desc: window internal interface for Windows
 * autr: dexterdreeeam
 * date: 20201108
 * tips: window interface implemented on Windwos
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_WINDOW_WINDOWS_HPP__)
#define __INT_WINDOW_WINDOWS_HPP__

namespace dxt
{

windows_ns::LRESULT CALLBACK __window_windows_cb(
    windows_ns::HWND hWnd,
    windows_ns::UINT msg,
    windows_ns::WPARAM wp,
    windows_ns::LPARAM lp)
{
    //switch (msg)
    //{
    //    ;
    //}

    return 0;
}

class windows_window : public window
{
public:
    windows_window(window_desc &desc) :
        window(desc)
    {
        using namespace windows_ns;

        WNDCLASS wc = {};
        wc.hbrBackground = (HBRUSH)COLOR_WINDOW;
        wc.hCursor = LoadCursor(NULL, IDC_ARROW);
        wc.hInstance = GetModuleHandle(EXECUTE_PROCESS_NAME);
        wc.lpszClassName = desc.name.c_str();
        wc.lpfnWndProc = __window_windows_cb;

        s64 ret;
        ret = RegisterClass(&wc);
        assert(ret);

        m_handle = CreateWindow(
            desc.name.c_str(), desc.name.c_str(),
            WS_OVERLAPPEDWINDOW | WS_VISIBLE,
            0, 0, desc.width, desc.height,
            NULL, NULL, NULL, NULL);

        assert(m_handle);
    }

    ~windows_window()
    {

    }

private:
    windows_ns::HWND m_handle;
};

}

#endif //# __INT_WINDOW_WINDOWS_HPP__ ends
