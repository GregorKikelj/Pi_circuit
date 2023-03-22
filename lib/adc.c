#include "adc.h"
#include <wiringPiI2C.h>

void init(I2CConverter* obj) {
  int fd = wiringPiI2CSetup(0x4B);
  obj->fd = fd;
}

int commands[] = {0b10000100, 0b11000100, 0b10010100, 0b11010100,
                  0b10100100, 0b11100100, 0b10110100, 0b11110100};

int read(I2CConverter* obj, int i2c_channel) {
  wiringPiI2CWrite(obj->fd, commands[i2c_channel]);
  int data = wiringPiI2CRead(obj->fd);
  return data;
}