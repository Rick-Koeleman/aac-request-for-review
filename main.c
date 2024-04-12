#include "lis3mdl.h"
#include <stdio.h>
#include <stdint.h>

int main()
{
    status_t stat = STATUS_OK;
    handle_t lis3mdl_1;
    handle_t lis3mdl_2;

    config_t config_1 = {
        .ctrl_reg1 = 0x10,
        .ctrl_reg2 = 0x00,
        .ctrl_reg3 = 0x03,
        .ctrl_reg4 = 0x00,
        .ctrl_reg5 = 0x00,
        .int_cfg   = 0xE8,
        .int_ths_h = 0x00,
        .int_ths_l = 0x00
    };


    stat = init(&lis3mdl_1, I2C_ADDRESS_1, config_1);
    if (stat == STATUS_ERROR)
    {
        printf("Device (1) initialisation failed\n");
        return 1;
    } else {
        printf("Device (1) initialisation successful\n");
    }


    stat = init(&lis3mdl_2, I2C_ADDRESS_2, config_1);
    if (stat == STATUS_ERROR) {
        printf("Device (2) initialisation failed\n");
        return 1;
    } else {
        printf("Device (2) initialisation successful\n");
    }


    uint8_t fs_config;
    stat = get_fullscale_config(&lis3mdl_1, &fs_config);
    if (stat == STATUS_OK)
    {
        printf("Fullscale config: %d\n", fs_config);
    }
    else
    {
        printf("Error reading fullscale config\n");
    }


    uint8_t output_datarate;
    stat = get_output_data_rate(&lis3mdl_1, &output_datarate);
    if (stat == STATUS_OK)
    {
        printf("Output data rate: %d\n", output_datarate);
    }
    else
    {
        printf("Error reading output data rate");
    }


    stat = set_output_data_rate(&lis3mdl_1, ODR_10);
    if (stat == STATUS_OK)
    {
        printf("Output data rate successfully set\n");
    }
    else
    {
        printf("Error setting the output data rate\n");
    }


    stat = set_itr_pin(&lis3mdl_1, INT_ENABLE);
    if (stat == STATUS_OK)
    {
        printf("Interrupt pin successfully set\n");
    }
    else
    {
        printf("Error setting the interrupt pin\n");
    }


    uint16_t axis_data;
    stat = get_axis_data(&lis3mdl_1, X_AXIS, &axis_data);
    if (stat == STATUS_OK)
    {
        printf("X-Axis data: %02x\n", axis_data);
    }
    else
    {
        printf("Error getting axis data\n");
    }

    return 0;
}
