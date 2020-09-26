/* ********* * ********* * ********* * ********* * *********
 *
 * ext_sdk_custom.hpp
 *
 * proj: proj_3000_sdk
 * desc: external user custom settings
 * autr: dexterdreeeam
 * date: 20200827
 * tips: define macro 'I_AM_WINDOWS' or 'I_AM_LINUX'
 *       in this file for cross platform
 *       define macro trace level 'DEBUG_FULL', 'DEBUG_CRIT', 'DEBUG_HALF', 'DEBUG_NONE'
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__EXT_SDK_CUSTOM_HPP__)
#define __EXT_SDK_CUSTOM_HPP__

// ===========================
#define I_AM_WINDOWS
//#define I_AM_LINUX
// ===========================


/*
 *  Debug Level
 *    - DEBUG_FULL
 *        function call timer
 *
 *    - DEBUG_CRIT
 *        function call stack
 *        normal log
 *        error log
 *
 *    - DEBUG_HALF
 *        inside checker
 *        input checker
 *
 *    - DEBUG_NONE
 */

// ===========================
#define DEBUG_FULL  //# all logs and all checkers enabled
//#define DEBUG_CRIT  //# critical logs and all checkers enabled
//#define DEBUG_HALF  //# no log and all checkers enabled
//#define DEBUG_NONE  //# no log and no checker enabled
// ===========================


#define BASE_LOG_FOLDER "C:/dxtSDK/"


#endif //# __EXT_SDK_CUSTOM_HPP__ ends
