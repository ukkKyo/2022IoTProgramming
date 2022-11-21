// LED 신호등 
#include <stdio.h> 
#include <pigpio.h> 

int main() {

int GLED = 18; // green LED
int YLED = 23; // yellow LED
int RLED = 25; // red LED

gpioInitialise();

gpioSetMode(GLED, PI_OUTPUT); 
gpioSetMode(YLED, PI_OUTPUT); 
gpioSetMode(RLED, PI_OUTPUT); 

while(1) {
  gpioWrite(GLED, 1); 
  gpioDelay(3000000); 
  gpioWrite(GLED, 0);

  gpioWrite(YLED, 1); 
  gpioDelay(3000000); 
  gpioWrite(YLED, 0);

  gpioWrite(RLED, 1); 
  gpioDelay(3000000); 
  gpioWrite(RLED, 0);
  }

gpioTerminate();
  
return 0; 
  

}
