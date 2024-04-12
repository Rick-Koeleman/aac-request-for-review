// lis3mdl.c

#include "lis3mdl.h"
#include <stdio.h>

status_t init(handle_t* h, uint8_t addr, config_t config)
{
    status_t stat = STATUS_OK;
    uint8_t dev_id;

    h->device_address = addr;
    h->config = config;

    stat = i2c_read(h->device_address, WHO_AM_I, 1, &dev_id);
    if (dev_id != DEVICE_ID) {
        printf("Incorrect device ID read\n");
        return STATUS_ERROR;
    }

    stat = i2c_write(h->device_address, CTRL_REG1, 1, &(h->config.ctrl_reg1));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, CTRL_REG2, 1, &(h->config.ctrl_reg2));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, CTRL_REG3, 1, &(h->config.ctrl_reg3));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, CTRL_REG4, 1, &(h->config.ctrl_reg4));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, CTRL_REG5, 1, &(h->config.ctrl_reg5));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, INT_CFG, 1, &(h->config.int_cfg));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, INT_THS_L, 1, &(h->config.int_ths_l));
    if (stat) {
        return stat;
    }

    stat = i2c_write(h->device_address, INT_THS_H, 1, &(h->config.int_ths_h));
    if (stat)
    {
        return stat;
    }

    return stat;
}


status_t get_fullscale_config(handle_t* h, uint8_t* fs_config)
{
    uint8_t buf;
    status_t stat = i2c_read(h->device_address, CTRL_REG2, 1, &buf);
    *fs_config = buf & 0x60; // full scale configuration, table 23, page 21 of datasheet

    return stat;
}


status_t get_output_data_rate(handle_t* h, uint8_t* odr)
{
    uint8_t buf;
    status_t stat = i2c_read(h->device_address, CTRL_REG1, 1, &buf);
    *odr = buf & 0x1C;

    return stat;
}


status_t set_output_data_rate(handle_t* h, output_data_rate_config_t rate)
{
    uint8_t buf;
    status_t stat = i2c_read(h->device_address, CTRL_REG1, 1, &buf);
    if (stat == STATUS_ERROR)
    {
        return stat;
    }
    buf |= rate;
    stat = i2c_write(h->device_address, CTRL_REG1, 1, &buf);

    return stat;
}


status_t set_itr_pin(handle_t* h, interrupt_enable_t intr)
{
    uint8_t buf;
    status_t stat = i2c_read(h->device_address, INT_CFG, 1, &buf);
    if (stat == STATUS_ERROR)
    {
        return stat;
    }
    buf |= intr;
    stat = i2c_write(h->device_address, INT_CFG, 1, &buf);

    return stat;
}


status_t get_axis_data(handle_t* h, axis_t axis, uint16_t* data)
{
    uint8_t buf[2];
    status_t stat = i2c_read(h->device_address, AXIS_OUT(axis), 2, buf);
    *data = ((uint16_t)buf[0] << 8) | buf[1];

    return stat;
}
