#include "logger.h"

Log *log_data;

Log::Log()
{
  log_i = 0;
  log_c = 0;
}

void Log::log(char *buff)
{
  char *l = &logs[(log_i%DO_MAX_NUM_LOGS)*DO_MAX_LOG_LEN];
  int i = 0 ;
  while(buff[i] != '\0' && i < DO_MAX_LOG_LEN-1)
  {
    l[i] = buff[i];
    i++;
  }
  l[i] = '\0';
  log_i++;
  log_c++;
  if(log_c > DO_MAX_NUM_LOGS) log_c = DO_MAX_NUM_LOGS;
}

char *Log::logAt(int i)
{
  return logs+(((log_i-log_c+DO_MAX_NUM_LOGS+i)%DO_MAX_NUM_LOGS)*DO_MAX_LOG_LEN);
}

int Log::logLen()
{
  return log_i;
}

