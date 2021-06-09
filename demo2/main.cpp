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
    car.stop();
    while(1){
        if(data[0]=='S') {
            x1 = 100*int(data[1]) + 10*int(data[2]) + int(data[3]);
            y1 = 100*int(data[4]) + 10*int(data[5]) + int(data[6]);
            x2 = 100*int(data[7]) + 10*int(data[8]) + int(data[9]);
            y2 = 100*int(data[10]) + 10*int(data[11]) + int(data[12]);
            

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
                printf(" %c ", data[i]);
            }
            else {
                data[i] = recv[0];
                i = 0;
                printf(" %c ", data[i]);
            }
            //pc.write(recv, sizeof(recv));
            
            
      }
   }
}