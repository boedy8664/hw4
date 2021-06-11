#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);
Thread t;
char data[13];
int i = 0;

void Data() {
    int x1, y1, x2, y2;
    int del;
    car.stop();
    while(1){
        if(data[0]=='S') {
            x1 = 100*(int(data[1])-48) + 10*(int(data[2])-48) + int(data[3])-48;
            y1 = 100*(int(data[4])-48) + 10*(int(data[5])-48) + int(data[6])-48;
            x2 = 100*(int(data[7])-48) + 10*(int(data[8])-48) + int(data[9])-48;
            y2 = 100*(int(data[10])-48) + 10*(int(data[11])-48) + int(data[12])-48;
            printf("x1:%d,y1: %d,x2: %d,y2 %d",x1,y1,x2,y2);
            del=x2-x1;
            if (del<0) {
                del = -del;
                car.line(20,20+del/2,1,1);
               // car.goStraight(100);
                ThisThread::sleep_for(100ms);
            }
            else {
               // del = -del;
                car.line(20+del/4,20,1,1);
               // car.goStraight(-100);
                ThisThread::sleep_for(100ms);
            }
        }
        if(data[0] == 'N') car.stop();
	    ThisThread::sleep_for(120ms);  

    }
}

int main(){
   uart.set_baud(9600);
   t.start(Data);
   while(1){
      if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            if (i != 12) {
                data[i] = recv[0];
                i++;
               // printf(" %c ", data[i]);
            }
            else {
                data[i] = recv[0];
                i = 0;
               // printf(" %c ", data[i]);
            }
            //pc.write(recv, sizeof(recv));
            
            
      }
   }
}