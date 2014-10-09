#include <pebble.h>
#include "gfs.h"

// buffer size in B
#define BUFFER_SIZE 12000

// power-of-two samples at a time
#define NUM_SAMPLES 16

/**
 * Context that holds the current callback and frequency. It is used in the accelerometer
 * callback to calculate the G forces and to push the packed sample buffer to the callback.
 */
static struct {
    // the callback function
    accel_sample_callback callback; 
    // the frequency
    int frequency;
    // the buffer
    char* buffer;
    // the position in the buffer
    int buffer_position;
} gfs_context;

/**
 * Handle the samples arriving.
 */
void gfs_raw_accel_data_handler(AccelRawData *data, uint32_t num_samples, uint64_t timestamp) {
    if (num_samples != NUM_SAMPLES) return /* FAIL */;
    // pack
}

int gfs_start(accel_sample_callback callback, int frequency) {
    if (gfs_context.callback != NULL) return E_GFS_ALREADY_RUNNING;

    gfs_context.callback = callback;
    gfs_context.frequency = frequency;
    gfs_context.buffer = malloc(BUFFER_SIZE);
    gfs_context.buffer_position = 0;

    if (gfs_context.buffer == NULL) return E_GFS_MEM;

    accel_raw_data_service_subscribe(NUM_SAMPLES, gfs_raw_accel_data_handler);

    return 1;
}

int gfs_stop() {
    gfs_context.callback = NULL;
    if (gfs_context.buffer != NULL) free(gfs_context.buffer);
    return 1;
}
