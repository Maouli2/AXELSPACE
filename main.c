#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <unistd.h>
#include "mcuLib.h"
#include "sensorLib.h"

#define MAX_TEMP 50
#define MIN_TEMP 15
#define MAX_VOLUME 60
#define MIN_VOLUME 1
#define MIN_TIME 900

int main(void)
{
    init_sensor();
    float volume;
    float temp;
    float user_temp;
    float user_volume;
    time_t start_time;

    while(1) {
        // for simplicity no input check is performed
        printf("Please enter the temperature: \n");
        scanf("%f", &user_temp);  
        printf("Please add the volume: \n");    
        scanf("%f", &user_volume);

        if (user_temp > MAX_TEMP || user_temp < MIN_TEMP) {
            printf("Temperature should be within [%d - %d] range\n",
            MIN_TEMP, MAX_TEMP);
            continue;
        }

        if (user_volume > MAX_VOLUME || user_volume < MIN_VOLUME) {
            printf("Volume should be within [%d - %d] range\n",
                MIN_VOLUME, MAX_VOLUME);
            continue;
        }
        break;
    }
 
    // in real-life MCU timer will be used
    start_time = get_current_time();
    
    printf("start_time: %ld\n", start_time);

    //set watchdog
 
    while ((volume = get_volume()) <= user_volume) {
        sleep(1);
        printf("volume: %f\n", volume);

        //update watchdog
 
        printf("current time: %ld\n", get_current_time());

        if (start_time + MIN_TIME < get_current_time()) {
            printf("Expected time exceeded\n");
            break;
        } 
 
        temp = get_temp();

        printf("temp: %f\n", temp);

        if ((temp >= (user_temp - 1)) && (temp <= (user_temp + 1))) {
            set_hot_tap(true);
            set_cold_tap(true);
            printf("true true\n");
        }
        else if (temp < user_temp) {
            set_hot_tap(true);
            set_cold_tap(false);
            printf("true false\n");
        }
        else {
            set_hot_tap(false);
            set_cold_tap(true);
            printf("false true\n");
        }
    }
    
    set_hot_tap(false);
    set_cold_tap(false);
 
    return 0;
}
