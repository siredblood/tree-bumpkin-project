#include "compile_time.hpp"


/// This string stores the time and date that the executable was compiled.
const char * aboutVersionString = "1.9.1";
const char * aboutCompileTimeString = __DATE__ " at " __TIME__;
