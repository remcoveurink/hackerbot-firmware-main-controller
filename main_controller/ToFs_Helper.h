/*********************************************************************************
Hackerbot Industries, LLC
Created By: Ian Bernstein
Created:    February 2025
Updated:    April 1, 2025

This file contains configuration and helper functions for the time of flight sensors that are on
most Hackerbot models so that the robot can avoid obstacles taller than the 
built in bump and LiDAR sensors can "see"

Special thanks to the following for their code contributions to this codebase:
Ian Bernstein - https://github.com/arobodude
Randy Beiter - https://github.com/rbeiter
*********************************************************************************/

#ifndef TOFS_HELPER_H
#define TOFS_HELPER_H

#ifdef __cplusplus
extern "C" {
#endif

#include <vl53l7cx_class.h>

#define TOFS_DEFAULT_I2C_ADDRESS  0x29     // Time of flight sensor unconfigured default address
#define TOF_LEFT_I2C_ADDRESS      0x2A     // Time of flight sensor (left) configured address
#define TOF_RIGHT_I2C_ADDRESS     0x2B     // Time of flight sensor (right) configured address

extern bool json_mode;

enum tof_state_t {
  TOF_STATE_NOTCONNECTED = 0,
  TOF_STATE_DEFAULTI2CADDRESS = 1,
  TOF_STATE_INITIALIZED = 2,
  TOF_STATE_I2CADDRESSASSIGNED = 3,
  TOF_STATE_READY = 4
};

extern tof_state_t tof_left_state;
extern tof_state_t tof_right_state;

void tofs_setup();

bool check_left_sensor();
bool check_right_sensor();

typedef struct {
    /* Measured distance in mm */
#ifndef VL53L7CX_DISABLE_DISTANCE_MM
  int16_t distance_mm[(VL53L7CX_RESOLUTION_8X8
                       *VL53L7CX_NB_TARGET_PER_ZONE)];
#endif
    /* Status indicating the measurement validity (5 & 9 means ranging OK)*/
#ifndef VL53L7CX_DISABLE_TARGET_STATUS
  uint8_t target_status[(VL53L7CX_RESOLUTION_8X8
                         *VL53L7CX_NB_TARGET_PER_ZONE)];
#endif
} VL53L7CX_Measurement;

bool left_sensor_ready();
bool right_sensor_ready();

VL53L7CX_Measurement* get_left_sensor_measurement();
VL53L7CX_Measurement* get_right_sensor_measurement();

#ifdef __cplusplus
}
#endif

#endif // TOFS_HELPER_H
