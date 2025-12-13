#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#ifdef __linux__
#include <sys/sysinfo.h>
#endif
#ifdef __APPLE__
#include <sys/sysctl.h>
#endif

typedef struct {
    int days;
    int hours;
    int minutes;
    int seconds;
} uptime_struct;

uptime_struct get_uptime_mac() {
    int mib[2];
    struct timeval boottime;
    size_t size = sizeof(boottime);
    time_t now, uptime_seconds;

    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;

    if (sysctl(mib, 2, &boottime, &size, NULL, 0) != 0) {
        perror("sysctl");
        return (uptime_struct){0, 0, 0, 0};
    }

    time(&now);
    uptime_seconds = now - boottime.tv_sec;

    uptime_struct uptime;
    uptime.days = uptime_seconds / (24 * 3600);
    uptime_seconds %= (24 * 3600);
    uptime.hours = uptime_seconds / 3600;
    uptime_seconds %= 3600;
    uptime.minutes = uptime_seconds / 60;
    uptime.seconds = uptime_seconds % 60;

    return uptime;
}

uptime_struct get_uptime_linux() {
#ifdef __linux__
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return (uptime_struct){0, 0, 0, 0};
    }
    long uptime_seconds = info.uptime;

    uptime_struct uptime;
    uptime.days = uptime_seconds / (24 * 3600);
    uptime_seconds %= (24 * 3600);
    uptime.hours = uptime_seconds / 3600;
    uptime_seconds %= 3600;
    uptime.minutes = uptime_seconds / 60;
    uptime.seconds = uptime_seconds % 60;

    return uptime;
#else
    return (uptime_struct){0, 0, 0, 0};
#endif
}

// Returns uptime struct based on OS
uptime_struct get_uptime(const char *os) {
    if (strcmp(os, "MAC") == 0) {
        return get_uptime_mac();
    } else if (strcmp(os, "LINUX") == 0) {
        return get_uptime_linux();
    } else {
        fprintf(stderr, "Unsupported OS: %s\n", os);
        return (uptime_struct){0, 0, 0, 0};
    }
}

// Helper function to convert uptime_struct to string
void uptime_to_string(uptime_struct uptime, char *buffer, size_t size) {
    snprintf(buffer, size, "%d days, %d hours, %d minutes, %d seconds",
             uptime.days, uptime.hours, uptime.minutes, uptime.seconds);
}
