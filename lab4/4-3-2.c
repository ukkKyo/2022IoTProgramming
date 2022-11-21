// PWM LED 밝기 조절

#include <stdio.h>
#include <pigpio.h>

int main()
{
  int led = 12;
  int step = 10000;
  int delay = 10000;
  int freq = 10000;
  int duty = 0;
  
  gpioInitialise();
  
  while(1) {
    duty += step; // duty cycle 증가 또는 감소, step의 +,- 값에 따라 달라짐.
    if(duty >= 1000000 || duty <= 0) { //duty cycle이 100%나 0%면 역방향 전환
      step = -step;
    }
    gpioHardwarePWM(led, freq, duty);
    
    gpioDelay(delay); // delay만큼 정지
  }
  
  gpioTerminate();
  
  return 0;
}
