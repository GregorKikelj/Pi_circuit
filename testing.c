#include <signal.h>
#include <softPwm.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

#define ledPinRed 0
#define ledPinGreen 1
#define ledPinBlue 2

void sigintHandler(int sig_num) {
  // signal(SIGINT, sigintHandler);
  pinMode(ledPinRed, INPUT);
  pinMode(ledPinGreen, INPUT);
  pinMode(ledPinBlue, INPUT);
  printf("exit\n");
  exit(0);
}

void setupLedPin(void) {
  softPwmCreate(ledPinRed, 0, 255);    // Creat SoftPWM pin for red
  softPwmCreate(ledPinGreen, 0, 255);  // Creat SoftPWM pin for green
  softPwmCreate(ledPinBlue, 0, 255);   // Creat SoftPWM pin for blue
}

void setLedColor(int r, int g, int b) {
  softPwmWrite(ledPinRed, 255 - r);    // Set the duty cycle
  softPwmWrite(ledPinGreen, 255 - g);  // Set the duty cycle
  softPwmWrite(ledPinBlue, 255 - b);   // Set the duty cycle
}

int main(void) {
  signal(SIGINT, sigintHandler);
  wiringPiSetup();
  setupLedPin();

  int r = 0;
  int g = 255;
  int b = 255;
  setLedColor(r, g, b);
  while (1) {
  }
  return 0;
}
