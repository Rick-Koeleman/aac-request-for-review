// lis3mdl.h

#include <stdio.h>
#include <stdint.h>
#include "i2c.h"

// Device ID
#define DEVICE_ID          0x3D

// Device can be configured with one of two addresses based on SDO/SA1 pin
#define I2C_ADDRESS_1      0x1C
#define I2C_ADDRESS_2      0x1E

// Register definitions for LIS3MDL
#define WHO_AM_I           0x0F
#define CTRL_REG1          0x20
#define CTRL_REG2          0x21
#define CTRL_REG3          0x22
#define CTRL_REG4          0x23
#define CTRL_REG5          0x24
#define STATUS_REG         0x27
#define OUT_X_L            0x28
#define OUT_X_H            0x29
#define OUT_Y_L            0x2A
#define OUT_Y_H            0x2B
#define OUT_Z_L            0x2C
#define OUT_Z_H            0x2D
#define TEMP_OUT_L         0x2E
#define TEMP_OUT_H         0x2F
#define INT_CFG            0x30
#define INT_SRC            0x31
#define INT_THS_L          0x32
#define INT_THS_H          0x33

// base address for reading axis data, where N is the axis to read
#define AXIS_OUT(N)        OUT_X_L + N

typedef struct
{
    uint8_t ctrl_reg1;
    uint8_t ctrl_reg2;
    uint8_t ctrl_reg3;
    uint8_t ctrl_reg4;
    uint8_t ctrl_reg5;
    uint8_t int_cfg;
    uint8_t int_ths_l;
    uint8_t int_ths_h;
} config_t;

typedef struct
{
    config_t config;
    uint8_t device_address;
} handle_t;

typedef enum
{
    ODR_0_625 = 0x00,   //0.625Hz
    ODR_1_25 = 0x04,    //1.25Hz
    ODR_2_5 = 0x08,     //2.5Hz
    ODR_5 = 0x0C,       //5Hz
    ODR_10 = 0x10,      //10Hz
    ODR_20 = 0x14,      //20Hz
    ODR_40 = 0x18,      //40Hz
    ODR_80 = 0x1C       //80Hz
} output_data_rate_config_t;

typedef enum
{
    INT_ENABLE = 0x01,
    INT_DISABLE = 0x00
} interrupt_enable_t;

typedef enum
{
    X_AXIS = 0,
    Y_AXIS = 2,
    Z_AXIS = 4
} axis_t;

status_t init(handle_t* h, uint8_t addr, config_t conf);
status_t setup(handle_t* h);
status_t get_fullscale_config(handle_t* h, uint8_t* fs_config);
status_t get_output_data_rate(handle_t* h, uint8_t* odr);
status_t set_output_data_rate(handle_t* h, output_data_rate_config_t rate);
status_t set_itr_pin(handle_t* h, interrupt_enable_t intr);
status_t get_axis_data(handle_t* h, axis_t axis, uint16_t* data);
