#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"


Ticker servo_ticker;
PwmOut pin5(D5), pin6(D6);
BufferedSerial xbee(D1, D0);
void reverse(Arguments *in, Reply *out);
BBCar car(pin5, pin6, servo_ticker);
RPCFunction rpcreverse(&reverse, "reverse");
int main() {
   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   RPC::call(buf, outbuf);
   }
}

void reverse(Arguments *in, Reply *out) {
    double d1 = in->getArg<double>();
    double d2 = in->getArg<double>();
    const char *direc = in->getArg<const char*>();
    
    double td1 = (d1-8)/10*750;
    double td2 = d2/10*750;
    double Td1 = (d1-4)/10*750;
    double Td2 = (d2+4)/10*750;

    if(strcmp(direc, "east") == 0) {
       car.goStraight(-100);
       ThisThread::sleep_for(Td2);
       car.stop();
       ThisThread::sleep_for(1s);
       car.turn(-100, 0.1);
       ThisThread::sleep_for(2400ms);
       car.stop();
       ThisThread::sleep_for(1s);
       car.goStraight(-100);
       ThisThread::sleep_for(Td1);
       car.stop();
       return;
    }

    else if(strcmp(direc, "west") == 0) {
       car.goStraight(-100);
       ThisThread::sleep_for(td2);
       car.stop();
       ThisThread::sleep_for(1s);
       car.turn(-100,-0.3);
       ThisThread::sleep_for(2500ms);
       car.stop();
       ThisThread::sleep_for(1s);
       car.goStraight(-100);
       ThisThread::sleep_for(td1);
       car.stop();
       return;
    }


}