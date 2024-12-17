#include <stdio.h>
#include <time.h>
#include <stdlib.h>

// Program that given number of seconds, prints the time in hours, minutes and seconds (HH:MM:SS format)
// Recall that the number if seconds is given on command line as an argument to the program

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <seconds>\n", argv[0]);
        return 1;
    }
    // int seconds = atoi(argv[1]);
    // int hours = seconds / 3600;
    // int minutes = (seconds % 3600) / 60;
    // int secs = (seconds % 3600) % 60;
    // printf("%02d:%02d:%02d\n", hours, minutes, secs);
    int r1, r2, r3;
    int tmp  = 0;
    tmp = atoi(argv[1]);
    r1 = tmp / 60; //min
    r2 = r1 / 60; //hour
    r3 = tmp % 60; //sec
    printf("%02d:%02d:%02d\n", r2, r1, r3);
    return 0;
}