#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>

#include "bmp280.h"

void delay_ms(uint32_t period_ms)
{
    usleep(period_ms*1000);
}

int8_t i2c_reg_write(uint8_t reg_addr, uint8_t *reg_data, uint16_t length, void *user_ptr)
{

    uint8_t *buf;
    int fd = *(int*)user_ptr;

    buf = (uint8_t*)malloc(length+1);
    buf[0] = reg_addr;
    memcpy(buf+1, reg_data, length);
    if (write(fd, buf, length + 1) < length)
    {
        free (buf);
        return BMP280_E_COMM_FAIL;
    }

    free (buf);

    return BMP280_OK;
}

int8_t i2c_reg_read(uint8_t reg_addr, uint8_t *reg_data, uint16_t length, void *user_ptr)
{
    int fd = *(int*)user_ptr;
    write(fd, &reg_addr, 1);
    read(fd, reg_data, length);

    return BMP280_OK;
}

