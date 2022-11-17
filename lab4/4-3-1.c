// GPIO 출력 예제 (PWM, Pulse Width Modulation)

#include <stdio.h>
#include <pigpio.h>

int main() {
  int led1 = 12;
  int led2 = 13;
  
  gpioInitialise();
  
  gpioHardwarePWM(led1, 1, 500000); // 주파수 1, duty 50%
  gpioHardwarePWM(led2, 2, 500000); // 주파수 2, duty 50%
  
  gpioTerminate();
  
  return 0;
}
