/* ********* * ********* * ********* * ********* * *********
 *
 * ext_window_interface.hpp
 *
 * proj: proj_05_window
 * desc: external interfaces
 * autr: dexterdreeeam
 * date: 20201108
 * tips: window component interface
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__EXT_WINDOW_INTERFACE_HPP__)
#define __EXT_WINDOW_INTERFACE_HPP__

#include "p00_sdk/ext_sdk_interface.hpp"
#include "int_window.hpp"

#ifdef I_AM_WINDOWS
    #include "int_window_windows.hpp"
#elif I_AM_LINUX
    #include "int_window_linux.hpp"
#endif

#endif //# __EXT_WINDOW_INTERFACE_HPP__ ends
