#include <signal.h>
#include <softPwm.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>
#include <wiringPiI2C.h>

volatile bool exit_flag = false;
void sigintHandler(int sig_num) {
  exit_flag = true;
}
void cleanup() {
  for (int i = 0; i < 32; i++) {
    pinMode(i, INPUT);
  }
  printf("exit\n");
  exit(0);
}

int main(void) {
  signal(SIGINT, sigintHandler);
  wiringPiSetup();

  int single_ended = 0x80;    // bit 7 set for single-ended
  int dac_on_ref_off = 0x04;  // bits 2-3 -- AD on, reference off
  int channel = 0x000;        // bits 4-6 contain the channel number to sample

  int cmd = single_ended | dac_on_ref_off | channel;

  int fd = wiringPiI2CSetup(0x4B);
  printf("fd: %d\n", fd);
  while (!exit_flag) {
    wiringPiI2CWrite(fd, cmd);
    int data = wiringPiI2CRead(fd);
    float voltage = (data / 255.0) * 3.3;
    printf("data: %d, voltage: %.2f\n", data, voltage);
    delay(100);
  }
  cleanup();
  return 0;
}
