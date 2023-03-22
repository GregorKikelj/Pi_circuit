#include <math.h>
#include <signal.h>
#include <softPwm.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <wiringPi.h>

void sigintHandler(int sig_num) {
  // signal(SIGINT, sigintHandler);
  for (int i = 0; i < 32; i++) {
    pinMode(i, INPUT);
  }
  printf("exit\n");
  exit(0);
}

#define BUZZER_PIN 0
#define SWITCH_PIN 1

int main(void) {
  signal(SIGINT, sigintHandler);
  wiringPiSetup();
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT);
  // while (1) {
  //   digitalWrite(BUZZER_PIN, HIGH);
  //   delay(1000);
  //   digitalWrite(BUZZER_PIN, LOW);
  //   delay(1000);
  // }
  bool prevSwitchState = false;
  while (1) {
    bool switchState = !digitalRead(SWITCH_PIN);
    if (switchState != prevSwitchState) {
      delay(5);  // debounce
      switchState = !digitalRead(SWITCH_PIN);
    }
    digitalWrite(BUZZER_PIN, switchState);
  }
  return 0;
}
