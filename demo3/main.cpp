#include"mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

BufferedSerial pc(USBTX,USBRX); //tx,rx
BufferedSerial uart(D1,D0); //tx,rx
Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BBCar car(pin5, pin6, servo_ticker);
DigitalOut led1(LED1);
DigitalInOut ping(D10);
Thread t;
Timer tt;
char data[18];
int i = 0;
int sign = 1;
int step = 0;
int confirm = 1;
int done = 1;
float tx,tz, ry, time1, time2;
void go();

void go() {
    if(ry>=270 && ry <= 360) {
        time1 = (abs(tx)+ry/2)*16;
        car.line(-30, 30, 0.4, 1);
        ThisThread::sleep_for(time1);
    }
    else {
        time1 = (abs(tx)+(360-ry)/2) *12;
        car.line(30, -30, 0.4, 1);
        ThisThread::sleep_for(time1);
    }
    car.stop();
    ThisThread::sleep_for(1s);

    time2 = abs(tx)*850;
    
    car.goStraight(30);
    ThisThread::sleep_for(time2);
    car.stop();
    ThisThread::sleep_for(1s);
    if(ry>=270 && ry <= 360) {
        car.line(30, -30, 0.4, 1);
        ThisThread::sleep_for(time1/1.5);
    }
    else {
        car.line(-30, 30, 0.4, 1);
        ThisThread::sleep_for(time1*1.2);
    }
    car.stop();
    ThisThread::sleep_for(1s);
    car.goStraight(30);
    ThisThread::sleep_for(((abs(tz)-6)*1000));
    car.stop();
    ThisThread::sleep_for(1s);


}


void Data() {
    float Tx, Tz, Ry;
 //   int done = 0;
    float val;
    pc.set_baud(9600);
    car.stop();
   // ThisThread::sleep_for(50ms);
    while(1) {
      //  printf("ooo %d\n",done);
        
         //   printf(" hello ");
        if(data[0]=='S') {
        Tx = (int(data[1])-48)*((int(data[2])-48) + 0.1*(int(data[4])-48) + 0.01*(int(data[5])-48));
        Tz = -1*(10*(int(data[7])-48) + (int(data[8])-48) + 0.1*(int(data[10])-48) + 0.01*(int(data[11])-48));
        Ry = 100*(int(data[12])-48) + 10*(int(data[13])-48) + (int(data[14])-48) + 0.1*(int(data[16]-48)) + 0.01*(int(data[17])-48);
        confirm++;
        }
       // printf("Tx: %f,Tz: %f,Ry: %f",Tx,Tz,Ry);
        if (confirm == 5) {
            tx = Tx;
            tz = Tz;
            ry = Ry;
            go();
           // done = 0;
          //  printf("%f %f %f", tx,tz,ry);
        }
        //printf("%f %f %f", tx,tz,ry);
        ping.output();
        ping = 0; wait_us(200);
        ping = 1; wait_us(5);
        ping = 0; wait_us(5);

        ping.input();
        while(ping.read() == 0);
        tt.start();
        while(ping.read() == 1);
        val = tt.read();
        printf("Ping = %lf\r\n", val*17700.4f);
        tt.stop();
        tt.reset();

       // ThisThread::sleep_for(1s);
	    ThisThread::sleep_for(120ms);
    }
   // printf("hello");
}

int main(){
    uart.set_baud(9600);
    t.start(Data);
  //  parallax_ping  ping1(pin10);
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