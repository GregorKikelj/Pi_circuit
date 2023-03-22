#ifndef I2C_CONVERTER_H
#define I2C_CONVERTER_H

typedef struct I2CConverterStruct {
  int fd;
} I2CConverter;

void init(I2CConverter* obj);
int read(I2CConverter* obj, int i2c_channel);

#endif