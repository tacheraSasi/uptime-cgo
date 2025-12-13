#ifndef SYSINFO_H
#define SYSINFO_H

#include <stdlib.h>

typedef struct {
  int days;
  int hours;
  int minutes;
  int seconds;
} uptime_struct;

uptime_struct get_uptime_struct(const char *os);

char *get_uptime(const char *os);

char *get_uptime_json(const char *os);

void uptime_to_string(uptime_struct uptime, char *buffer, size_t size);

#endif
