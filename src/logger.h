#ifndef DO_LOGGER_H
#define DO_LOGGER_H

#include "defines.h"
#include <stdio.h>

#define DO_LOG_STORE 1
#define DO_MAX_LOG_LEN 256
#define DO_MAX_NUM_LOGS 256

#if DO_PLATFORM == DO_PLATFORM_ANDROID

  #include <android/log.h>
  #define do_log(t, ...) ({__android_log_print(ANDROID_LOG_INFO, "DO", t, ##__VA_ARGS__);})

#elif DO_PLATFORM == DO_PLATFORM_MAC

  #if DO_LOG_STORE
    #define do_log(t, ...) ({ printf(t, ##__VA_ARGS__); printf("\n"); fflush(stdout); char buff[DO_MAX_LOG_LEN]; sprintf(buff, t, ##__VA_ARGS__); log_data->log(buff); })
  #else
    #define do_log(t, ...) ({ printf(t, ##__VA_ARGS__); printf("\n"); fflush(stdout); })
  #endif

#endif

class Log;
extern Log *log_data;
class Log
{
  private:
    int log_i;
    int log_c;
    char logs[DO_MAX_NUM_LOGS*DO_MAX_LOG_LEN];
  public:
    Log();
    void log(char *buff);
    char *logAt(int i);
    int logLen();
};

#endif

