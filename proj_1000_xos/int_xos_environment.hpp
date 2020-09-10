/* ********* * ********* * ********* * ********* * *********
 *
 * int_xos_environment.hpp
 *
 * proj: proj_1000_xos
 * desc: platform environment configuration
 * autr: dexterdreeeam
 * date: 20200810
 * tips: \
 *
 ********* * ********* * ********* * ********* * ********* */

#if !defined (__INT_XOS_ENVIRONMENT_HPP__)
#define __INT_XOS_ENVIRONMENT_HPP__

#define DEBUG_LEVEL_CALIBRATION_ALL               95
#define DEBUG_LEVEL_CALIBRATION_LOG_TIMER         95
#define DEBUG_LEVEL_CALIBRATION_LOG_CALLSTACK     85
#define DEBUG_LEVEL_CALIBRATION_LOG_NORM          75
#define DEBUG_LEVEL_CALIBRATION_LOG_ERROR         65
#define DEBUG_LEVEL_CALIBRATION_LOG_NONE          55

#define DEBUG_LEVEL_CALIBRATION_CHECK_ALLPARAM    45
#define DEBUG_LEVEL_CALIBRATION_CHECK_ALLINPUT    35
#define DEBUG_LEVEL_CALIBRATION_CHECK_BASIC       25
#define DEBUG_LEVEL_CALIBRATION_NONE               5

#if defined (DEBUG_FULL)
    #define DEBUG_LEVEL 100
#elif defined (DEBUG_CRIT)
    #define DEBUG_LEVEL 80
#elif defined (DEBUG_HALF)
    #define DEBUG_LEVEL 50
#elif defined (DEBUG_NONE)
    #define DEBUG_LEVEL 0
#else
    #error dxt_error: don't supported DEBUG_LEVEL.
#endif


#if defined (I_AM_WINDOWS) && !defined (I_AM_LINUX)
    #include "int_xos_environment_windows.hpp"
#elif defined (I_AM_LINUX)
    #include "int_xos_environment_linux.hpp"
#else
    #error dxt_error: don't supported platform.
#endif


#include "int_xos_math.hpp"

#endif //# __INT_XOS_ENVIRONMENT_HPP__ ends
