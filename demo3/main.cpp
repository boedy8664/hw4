#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);
Thread t;
char data[18];
int i = 0;
int sign = 1;
int step = 0;
int confirm = 1;
int done = 1;
void Data() {
    float Tx, Tz, Ry, tx,tz, ry;
 //   int done = 0;
    
    car.stop();
   // ThisThread::sleep_for(50ms);
    while(1) {
        printf("ooo %d\n",done);
        
         //   printf(" hello ");
        if(data[0]=='S') {
        Tx = (int(data[1])-48)*((int(data[2])-48) + 0.1*(int(data[4])-48) + 0.01*(int(data[5])-48));
        Tz = -1*(10*(int(data[7])-48) + (int(data[8])-48) + 0.1*(int(data[10])-48) + 0.01*(int(data[11])-48));
        Ry = 100*(int(data[12])-48) + 10*(int(data[13])-48) + (int(data[14])-48) + 0.1*(int(data[16]-48)) + 0.01*(int(data[17])-48);
        }
       // printf("Tx: %f,Tz: %f,Ry: %f",Tx,Tz,Ry);
        
        if (confirm == 5) {
            tx = Tx;
            tz = Tz;
            ry = Ry;
            printf("%f %f %f", tx,tz,ry);
            break;
        }
        

	    ThisThread::sleep_for(120ms);
        confirm++;
    }
    printf("hello");
}

int main(){
   uart.set_baud(9600);
   t.start(Data);
   while(1){
        if(uart.readable()){
            char recv[1];
            uart.read(recv, sizeof(recv));
            
            if(i!=17) {
                if(i == 1) {
                    if(recv[0] == '-') data[i] = '/';
                    else data[i] = '1';
                     //   printf("%c", data[i]);
                        i++;
                }
                else {
                        data[i] = recv[0];
                      //  printf("%c", data[i]);
                        i++;
                }
            }
            else {
                data[i] = recv[0];
                //    printf("%c", data[i]);
                i = 0;
                   
            }
        }
    }
}