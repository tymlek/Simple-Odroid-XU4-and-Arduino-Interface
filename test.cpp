#include <stdio.h>
#include <string.h>
#include <errno.h>

#include "./ATmel328p.h"

int main ()
{
  const char* path = "/dev/ttyUSB0";
  short speed = 9600;

  if (!serialInit(path,speed)) {
    fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
    return 1;
  }

  digitalOut(Dpin_3,HIGH);

  sleep(2);

  digitalOut(Dpin_3,LOW);

  sleep(2);

  printf("Digital input on pin 4: %d\n",digitalIn(Dpin_4));

  sleep(2);

  analogOut(PWMpin_3,50);
  sleep(2);
  analogOut(PWMpin_3,0);

  sleep(2);

  int val = analogIn(Apin_0);
  printf("Analog input on pin A0: %d\n",val);
  double volts = val * (4.54 / 1024);
  printf("Analog input on pin A0: %f V\n",volts);
  
  sleep(2);
  
  writeReg(0x0a,0x08);
  writeReg(0x2b,0x08);
  sleep(2);
  printf("Register Port D: %d\n",readReg(0x2b));
  sleep(2);
  writeReg(0x2b,0x00);
  sleep(2);
  printf("Register Port D: %d\n",readReg(0x2b));

  serialClose(fd);

  return 0;
}
