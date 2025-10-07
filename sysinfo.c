#include <stdio.h>
#include <sys/sysctl.h>
#ifdef __linux__
#include <sys/sysinfo.h>
#endif


int get_uptime(char os[]){
    const osType = os;
    switch (osType){
    case 'MAC':
        return get_uptime_mac();
        break;
    case 'LINUX':
        return get_uptime_linux();
        break;
    default:
        printf("Unsupported OS: %s\n", osType);
        return 0;
        break;
    }
    return 0;
}

int get_uptime_mac(){
    int mib[2];
    struct timeval boottime;
    size_t size = sizeof(boottime);
    time_t now;
    time_t uptime;

    mib[0] = CTL_KERN;
    mib[1] = KERN_BOOTTIME;

    if (sysctl(mib, 2, &boottime, &size, NULL, 0) != 0) {
        perror("sysctl");
        return -1;
    }

    time(&now);
    uptime = now - boottime.tv_sec;

    int days = uptime / (24 * 3600);
    uptime %= (24 * 3600);
    int hours = uptime / 3600;
    uptime %= 3600;
    int minutes = uptime / 60;
    int seconds = uptime % 60;

    return sprintf("%d days, %d hours, %d minutes, %d seconds\n", days, hours, minutes, seconds);
}

int get_uptime_linux(){
    struct sysinfo info;
    if (sysinfo(&info) != 0) {
        perror("sysinfo");
        return -1;
    }
    long uptime = info.uptime;
   int days = uptime / (24 * 3600);
   uptime %= (24 * 3600);
   int hours = uptime / 3600;
   uptime %= 3600;
   int minutes = uptime / 60;
   int seconds = uptime % 60;

    return sprintf("%d days, %d hours, %d minutes, %d seconds\n", days, hours, minutes, seconds);
}