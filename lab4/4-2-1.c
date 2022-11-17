#include <stdio.h> 
#include <pigpio.h> 

int main() {

  int pin = 18;
  int switch_pin = 24;

  gpioInitialise();

  gpioSetMode(pin, PI_OUTPUT); 
  gpioWrite(switch_pin, PI_INPUT); 

  while(1) {
    if(gpioRead(switch_pin) == 0) {
      gpioWrite(pin, 1);
      gpioDelay(100000);
      gpioWrite(pin, 0);
    }
  }

  gpioTerminate();

  return 0; 

}
