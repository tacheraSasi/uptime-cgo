#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/sysctl.h>
#include <sys/time.h>
#include <time.h>
#ifdef __linux__
#include <sys/sysinfo.h>
#endif
#include "sysinfo.h"

typedef struct {
  int days;
  int hours;
  int minutes;
  int seconds;
} uptime_struct;

char *get_uptime(char os[]) {
  if (strcmp(os, "MAC") == 0) {
    return get_uptime_mac();
  } else if (strcmp(os, "LINUX") == 0) {
    return get_uptime_linux();
  } else {
    printf("Unsupported OS: %s\n", os);
    return NULL;
  }
}

uptime_struct get_uptime_mac() {
  int mib[2];
  struct timeval boottime;
  uptime_struct uptime_body;
  size_t size = sizeof(boottime);
  time_t now;
  time_t uptime;

  mib[0] = CTL_KERN;
  mib[1] = KERN_BOOTTIME;

  if (sysctl(mib, 2, &boottime, &size, NULL, 0) != 0) {
    perror("sysctl");
    return NULL;
  }

  time(&now);
  uptime = now - boottime.tv_sec;

  int days = uptime / (24 * 3600);
  uptime %= (24 * 3600);
  int hours = uptime / 3600;
  uptime %= 3600;
  int minutes = uptime / 60;
  int seconds = uptime % 60;

  char *result = malloc(256);
  if (result == NULL) {
    return NULL;
  }
  char daysString[64];
  if (days == 1) {
    sprintf(daysString, "1 day");
  } else {
    sprintf(daysString, "%d days", days);
  }

  char hoursString[64];
  if (hours == 1) {
    sprintf(hoursString, "1 hour");
  } else {
    sprintf(hoursString, "%d hours", hours);
  }
  char minutesString[64];
  if (minutes == 1) {
    sprintf(minutesString, "1 minute");
  } else {
    sprintf(minutesString, "%d minutes", minutes);
  }
  char secondsString[64];
  if (seconds == 1) {
    sprintf(secondsString, "1 second");
  } else {
    sprintf(secondsString, "%d seconds", seconds);
  }
  char *uptime_str = malloc(256);
  uptime_body.hours = hours;
  uptime_body.minutes = minutes;
  uptime_body.seconds = seconds;
  return uptime_body;
}

uptime_struct get_uptime_linux() {
  uptime_struct uptime_body;
#ifdef __linux__
  struct sysinfo info;
  if (sysinfo(&info) != 0) {
    perror("sysinfo");
    return NULL;
  }
  long uptime = info.uptime;
  int days = uptime / (24 * 3600);
  uptime %= (24 * 3600);
  int hours = uptime / 3600;
  uptime %= 3600;
  int minutes = uptime / 60;
  int seconds = uptime % 60;

  char *result = malloc(256);
  if (result == NULL) {
    return NULL;
  }
  sprintf(result, "%d days, %d hours, %d minutes, %d seconds\n", days, hours,
          minutes, seconds);
  uptime_body.days = days;
  uptime_body.hours = hours;
  uptime_body.minutes = minutes;
  uptime_body.seconds = seconds;
  return uptime_body;
#else
  return uptime_body;
#endif
}
