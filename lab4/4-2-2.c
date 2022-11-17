// LED ON or OFF switch  
/* 4-2-1.c에서 스위치를 한 번 누르면 LED가 켜지고, 
   다시 누르면 LED가 꺼지는 On/Off 스위치 제작.
   
   풀업, 풀다운 저항에 주의해서 회로 설계할 것.
   스위치를 눌렀을 때(ON) 스위치가 0의 값(LOW)을 가지면 풀업,
   스위치를 눌렀을 때(ON) 스위치가 1의 값(HIGH)을 가지면 풀다운.
   
   풀업은 저항을 Vcc에 연결하면 되고, 풀다운은 저항을 GND에 연결하면 된다.
   
   해당 실습에서는 풀업저항을 사용. */

#include <stdio.h> 
#include <pigpio.h> 

int main() {

  int LED = 18;
  int switch_pin = 24;
  int flag = 0;   // 버튼을 누를 때마다 LED 출력 값을 변경하기 위한 변수.
  // 버튼이 눌렸을 때 flag=0이면 LED ON, flag = 1
  // 버튼이 눌렸을 때 flag=1이면 LED OFF, flag = 0

  gpioInitialise();

  gpioSetMode(LED, PI_OUTPUT); 
  gpioWrite(switch_pin, PI_INPUT); 

  while(1) {
    if(gpioRead(switch_pin) == 0) { // 버튼이 눌렸는지 체크.
      if(flag == 0) {
         gpioWrite(LED, 1);
         flag = 1;
      } 
       else {
         gpioWrite(LED, 0);
         flag = 0;
      }
    }
    gpioDelay(500000); // 스위치 입력이 짧은 시간 내에 여러 번 들어가는 것 방지
  }
 
  gpioTerminate();

  return 0; 

}
