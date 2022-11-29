// 초음파센서

#include <stdio.h>
#include <pigpio.h>

int main() {
  int trig = 17;
  int echo = 27;
  unsigned int start, end;
  float distance;
  
  gpioInitialise();
  
  gpioSetMode(trig, PI_OUTPUT);
  gpioSetMode(echo, PI_INPUT);
  gpioWrite(trig, 0);                 // trig는 0으로 시작
  gpioDelay(100000);
  
  while(1) {
    gpioWrite(trig, 1);               // trig 신호 입력 시작
    gpioDelay(10);
    gpioWrite(trig, 0);               // 10us 후에 0 입력, echo가 1이 되면 시간 기록
    while(gpioRead(echo) == 0)
      start = gpioTick();             // echo가 0이 되면 시간 기록
    
    distance = (end - start) / 58.0f; // pulse 길이로 거리 계산
    printf("diff: %u, distance (cm) : %f\n", end - start, distance);
    
    gpioWrite(trig, 0);
    gpioDelay(100000);
  }
  
  gpioTerminate();
  
  return 0;
}
