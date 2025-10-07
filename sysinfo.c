#include <stdio.h>


int get_uptime(char os[]){ //NOTE: Assuming the user must be on a macintosh 
    const osType = os;
    switch (osType){
    case 'MAC':
        return get_uptime_mac();
        break;
    default:
        break;
    }
    return 0;
}

int get_uptime_mac(){

}