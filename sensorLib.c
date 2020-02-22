#include <stdlib.h>
#include <unistd.h>
#include "sensorlib.h"

#define TEMP_MAX 50
#define VOLUME_MAX 1

static float x;

float get_temp(void) {
    sleep(1);
    return (float)rand()/(float)(RAND_MAX/TEMP_MAX);
}

float get_volume(void) {
    sleep(1);
    return x += (float)rand()/(float)(RAND_MAX/VOLUME_MAX);
}

void init_sensor(void) {
    x = 0;
}

void set_hot_tap(int value) {

}

void set_cold_tap(int value) {
    
}
