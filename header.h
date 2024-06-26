#ifndef HEADER_H
#define HEADER_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <signal.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <time.h>
#include <string.h>

// Constants and shared memory key
#define SHM_KEY 1234
#define SHM_SIZE 1024
#define SWITCH_THRESHOLD 3
#define NUM_OF_WORKERS_FOR_EACH_LINE 1

// Struct for pill containers
typedef struct {
    int is_sealed;
    int has_normal_color;
    int has_correct_label;
    int expiry_date_printed;
    int expiry_date_correct;
    int count;
} Pill_Container;

typedef struct {
    int level;
    int has_normal_color;
    int is_sealed;
    int has_correct_label;
    int expiry_date_printed;
    int expiry_date_correct;
    int is_valid;
} Liquid_medicine;

// Struct for shared arguments
typedef struct {
    int NUM_OF_PRODUCTION_LINES;
    int MAX_LIQUID_BOTTLES_PER_LINE;
    int MAX_PILL_CONTAINERS_PER_LINE;
    int BOTTLES_PER_PACKAGE;
    int SIMULATION_DURATION;
    int MIN_LIQUID_LEVEL;
    int MAX_LIQUID_LEVEL;
    int COLOR_MAX_THRESHOLD;
    int COLOR_MIN_THRESHOLD;
    int SEALED_MAX_THRESHOLD;
    int SEALED_MIN_THRESHOLD;
    int LABEL_MAX_THRESHOLD;
    int LABEL_MIN_THRESHOLD;
    int EXPIRY_MAX_THRESHOLD;
    int EXPIRY_MIN_THRESHOLD;
    int MIN_DELAY;
    int MAX_DELAY;
    int MIN_DELAY_FOR_INSPECTORS;
    int MAX_DELAY_FOR_INSPECTORS;
    int PACKAGING_DELAY_MIN;
    int PACKAGING_DELAY_MAX;
    int produced_liquid_medicine[100];
    int bottles_packaged[100];
    int produced_pills[100];
    int pills_packaged[100];
    int production_speed[100];
    int production_line_pid[100];
    time_t starting_time[100];
    int NUM_OF_WORKERS[100];
    Pill_Container pills[100][1000]; // Changed to match production lines and containers
    int produced_index[100][1000];
    int inspected_index[100][1000];
} Shared_Argument;

extern Shared_Argument *shared_args;
extern pthread_mutex_t mutex;
extern int simulation_running;
extern int line_index_pills;
extern int production_line;

// Function declarations
void signal_handler(int sig);
void* production_function(void *args);
void* inspectors_function(void *args);
void* packagers_function(void *args);
void* manager_function(void *args);
int check_validity1(Pill_Container *pill);

#endif // HEADER_H

