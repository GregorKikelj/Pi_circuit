#include <signal.h>
#include <softPwm.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include "adc.h"

volatile bool exit_flag = false;
void sigintHandler(int sig_num) {
  exit_flag = true;
}
#define LED_R 0
#define LED_G 2
#define LED_B 3

int rgb[] = {LED_R, LED_G, LED_B};

void cleanup() {
  // for (int i = 0; i < 32; i++) {
  //   pinMode(i, INPUT);
  // }
  printf("exit\n");
  exit(0);
}

int main(void) {
  signal(SIGINT, sigintHandler);
  wiringPiSetup();

  I2CConverter* adc = malloc(sizeof(I2CConverter));
  init(adc);

  softPwmCreate(rgb[0], 0, 255);
  softPwmCreate(rgb[1], 0, 255);
  softPwmCreate(rgb[2], 0, 255);
  while (!exit_flag) {
    for (int channel = 0; channel < 3; channel++) {
      int data = read(adc, channel);
      float voltage = (data / 255.0) * 3.3;
      printf("channel: %d, data: %d, voltage: %.2f\n", channel, data, voltage);

      softPwmWrite(rgb[channel], 255 - data);
    }
    printf("\n");
    delay(300);
  }
  cleanup();
  return 0;
}
