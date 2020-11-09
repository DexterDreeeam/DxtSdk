/* ********* * ********* * ********* * ********* * *********
 *
 * int_window.hpp
 *
 * proj: proj_05_window
 * desc: window component definitions
 * autr: dexterdreeeam
 * date: 20201108
 * tips:
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_WINDOW_HPP__)
#define __INT_WINDOW_HPP__

namespace dxt
{

class window;

enum class window_event_type : s64
{
    reserved = -1,

    window_close,
    window_resize,

    mouse_press,
    mouse_release,
    mouse_repeat,
    mouse_move,
    mouse_scroll,

    key_press,
    key_release,
    key_repeat,

    number //# reserved for counting
};

static const char *window_event_type_cstr[(u64)window_event_type::number] =
{
    "window_close",
    "window_resize",

    "mouse_press",
    "mouse_release",
    "mouse_repeat",
    "mouse_move",
    "mouse_scroll",

    "key_press",
    "key_release",
    "key_repeat"
};

class window_event
{
public:
    window_event(window *w) : m_wnd(w) {}
    virtual ~window_event() {}
    virtual window_event_type Type() const { return window_event_type::reserved; }

    window *GetWindow() { return m_wnd; }

protected:
    window *m_wnd;
};

class window_close : public window_event
{
public:
    window_close(window *w) : window_event(w) {}
    ~window_close() override {}
    window_event_type Type() const override { return window_event_type::window_close; }
};

class window_resize : public window_event
{
public:
    window_resize(window *w) : window_event(w) {}
    ~window_resize() override {}
    window_event_type Type() const override { return window_event_type::window_resize; }
};

class mouse_press : public window_event
{
public:
    mouse_press(window *w) : window_event(w) {}
    ~mouse_press() override {}
    window_event_type Type() const override { return window_event_type::mouse_press; }
};

class mouse_release : public window_event
{
public:
    mouse_release(window *w) : window_event(w) {}
    ~mouse_release() override {}
    window_event_type Type() const override { return window_event_type::mouse_release; }
};

class mouse_repeat : public window_event
{
public:
    mouse_repeat(window *w) : window_event(w) {}
    ~mouse_repeat() override {}
    window_event_type Type() const override { return window_event_type::mouse_repeat; }
};

class mouse_move : public window_event
{
public:
    mouse_move(window *w) : window_event(w) {}
    ~mouse_move() override {}
    window_event_type Type() const override { return window_event_type::mouse_move; }
};

class mouse_scroll : public window_event
{
public:
    mouse_scroll(window *w) : window_event(w) {}
    ~mouse_scroll() override {}
    window_event_type Type() const override { return window_event_type::mouse_scroll; }
};

class key_press : public window_event
{
public:
    key_press(window *w) : window_event(w) {}
    ~key_press() override {}
    window_event_type Type() const override { return window_event_type::key_press; }
};

class key_release : public window_event
{
public:
    key_release(window *w) : window_event(w) {}
    ~key_release() override {}
    window_event_type Type() const override { return window_event_type::key_release; }
};

class key_repeat : public window_event
{
public:
    key_repeat(window *w) : window_event(w) {}
    ~key_repeat() override {}
    window_event_type Type() const override { return window_event_type::key_repeat; }
};

typedef void WindowEventCbFunc(const window_event &evnt);

struct window_desc
{
    std::string name;
    s64 width;
    s64 height;
    WindowEventCbFunc *cb;
};

class window
{
public:
    window(window_desc &desc) :
        m_desc(desc)
    {}

    virtual ~window() {}

    window_desc *GetWindowDesc() { return &m_desc; }

protected:
    window_desc m_desc;
};

}

#endif //# __INT_WINDOW_HPP__ ends
