/* ********* * ********* * ********* * ********* * *********
 *
 * ext_xos_custom.hpp
 *
 * proj: proj_1000_xos
 * desc: external user custom settings
 * autr: dexterdreeeam
 * date: 20200827
 * tips: define macro 'I_AM_WINDOWS' or 'I_AM_LINUX'
 *       in this file for cross platform
 *       define macro trace level 'DEBUG_FULL', 'DEBUG_HALF', 'DEBUG_NONE'
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__EXT_XOS_CUSTOM_HPP__)
#define __EXT_XOS_CUSTOM_HPP__

// ===========================
#define I_AM_WINDOWS
//#define I_AM_LINUX
// ===========================


// ===========================
#define DEBUG_FULL  //# all logs and all checkers enabled
//#define DEBUG_CRIT  //# critical logs and all checkers enabled
//#define DEBUG_HALF  //# no log and all checkers enabled
//#define DEBUG_NONE  //# no log and no checker enabled
// ===========================


#define LOG_FOLDER "C:\\DXT_LOG\\"


#endif //# __EXT_XOS_CUSTOM_HPP__ ends
