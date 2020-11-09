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

class windows_window : public window
{
public:
    windows_window(window_desc &desc) :
        window(desc),
        m_module(NULL),
        m_handle(nullptr),
        m_window_class(),
        m_execute(nullptr),
        m_execute_thrd_id(0),
        m_execute_exit_complete(nullptr)
    {
        using namespace windows_ns;
        AUTO_TRACE;

        if (!g_global_window_map_lock)
        {
            g_global_window_map_lock = lock_create();
        }
        assert(g_global_window_map_lock);

        m_execute = thrd_create(ExecuteCb, this);
        assert(m_execute);
    }

    ~windows_window() override
    {
        using namespace windows_ns;
        AUTO_TRACE;
        s64 ret;

        m_execute_exit_complete = evnt_create();
        while (m_execute_thrd_id == 0)
        {
            tick_sleep(10);
        }
        ret = PostThreadMessage(m_execute_thrd_id, WM_DESTROY, 0, 0);
        assert(ret);
        evnt_wait(m_execute_exit_complete);

        lock_wait_get(g_global_window_map_lock);
        assert(g_global_window_map.count((s64)m_handle));
        g_global_window_map.erase(g_global_window_map.find((s64)m_handle));
        lock_put(g_global_window_map_lock);
    }

private:
    void Execute()
    {
        using namespace windows_ns;
        AUTO_TRACE;
        s64 ret;

        m_module = GetModuleHandle(NULL);
        assert(m_module);

        m_window_class.style = 0;
        m_window_class.lpfnWndProc = windows_window::MessageCb;
        m_window_class.cbClsExtra;
        m_window_class.cbWndExtra;
        m_window_class.hInstance = m_module;
        m_window_class.hIcon = LoadIcon(NULL,IDI_APPLICATION);
        m_window_class.hCursor = LoadCursor(NULL, IDC_ARROW);
        m_window_class.hbrBackground = (HBRUSH)COLOR_WINDOW;
        m_window_class.lpszMenuName = window::GetWindowDesc()->name.c_str();
        m_window_class.lpszClassName = window::GetWindowDesc()->name.c_str();

        ret = RegisterClass(&m_window_class);
        assert(ret);

        m_handle = CreateWindow(
            window::GetWindowDesc()->name.c_str(),
            window::GetWindowDesc()->name.c_str(),
            WS_VISIBLE | WS_CAPTION | WS_MAXIMIZE,
            0, 0,
            window::GetWindowDesc()->width, window::GetWindowDesc()->height,
            NULL, NULL, m_module, NULL);
        assert(m_handle);

        lock_wait_get(g_global_window_map_lock);
        g_global_window_map[(s64)m_handle] = this;
        lock_put(g_global_window_map_lock);

        ret = ShowWindow(m_handle, SW_SHOW);
        assert(ret);

        m_execute_thrd_id = thrd_myid();

        MSG msg = {};
        while (GetMessage(&msg, NULL, 0, 0))
        {
            TranslateMessage(&msg);
            if (msg.message == WM_DESTROY)
            {
                log("%s Receive window destroy event, exit execute loop", __FUNCTION__);
                break;
            }
            DispatchMessage(&msg);
        }

        ret = DestroyWindow(m_handle);
        assert(ret);
        ret = UnregisterClass(m_window_class.lpszClassName, m_module);
        assert(ret);
        evnt_set(m_execute_exit_complete);
    }

    static void ExecuteCb(void *p)
    {
        using namespace windows_ns;
        AUTO_TRACE;

        windows_window *wnd = (windows_window*)p;
        wnd->Execute();
    }

    static windows_ns::LRESULT CALLBACK MessageCb(
        windows_ns::HWND hWnd,
        windows_ns::UINT msg,
        windows_ns::WPARAM wp,
        windows_ns::LPARAM lp)
    {
        using namespace windows_ns;

        window *wnd = nullptr;
        lock_wait_get(g_global_window_map_lock);
        wnd = g_global_window_map[(s64)hWnd];
        lock_put(g_global_window_map_lock);

        if (!wnd || wnd->GetWindowDesc()->cb == nullptr)
        {
            goto undone;
        }

        switch (msg)
        {
        case WM_CLOSE:
            break;

        case WM_LBUTTONDOWN:
        case WM_RBUTTONDOWN:
            wnd->GetWindowDesc()->cb(mouse_press(wnd));
            break;

        case WM_LBUTTONUP:
        case WM_RBUTTONUP:
            wnd->GetWindowDesc()->cb(mouse_release(wnd));
            break;

        case WM_MOUSEMOVE:
            wnd->GetWindowDesc()->cb(mouse_move(wnd));
            break;

        case WM_HSCROLL:
        case WM_VSCROLL:
            wnd->GetWindowDesc()->cb(mouse_scroll(wnd));
            break;

        case WM_KEYDOWN:
            wnd->GetWindowDesc()->cb(key_press(wnd));
            break;

        case WM_KEYUP:
            wnd->GetWindowDesc()->cb(key_release(wnd));
            break;

        default:
            goto undone;
        }

    done:
        return 0;

    undone:
        return DefWindowProc(hWnd, msg, wp, lp);
    }

private:
    static std::map<s64, window*> g_global_window_map;
    static lock                   g_global_window_map_lock;

    windows_ns::HMODULE           m_module;
    windows_ns::HWND              m_handle;
    windows_ns::WNDCLASS          m_window_class;
    thrd                          m_execute;
    volatile u64                  m_execute_thrd_id;
    evnt                          m_execute_exit_complete;
};

_SELECTANY_ std::map<s64, window*> windows_window::g_global_window_map;
_SELECTANY_ lock windows_window::g_global_window_map_lock = nullptr;

}

#endif //# __INT_WINDOW_WINDOWS_HPP__ ends
