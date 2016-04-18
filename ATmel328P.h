#include <unistd.h>
#include <wiringSerial.h>

#define Dpin_0 0x00
#define Dpin_1 0x01
#define Dpin_2 0x02
#define Dpin_3 0x03
#define Dpin_4 0x04
#define Dpin_5 0x05
#define Dpin_6 0x06
#define Dpin_7 0x07
#define Dpin_8 0x08
#define Dpin_9 0x09
#define Dpin_10 0x0a
#define Dpin_11 0x0b
#define Dpin_12 0x0c
#define Dpin_13 0x0d

#define PWMpin_3 0x03
#define PWMpin_5 0x05
#define PWMpin_6 0x06
#define PWMpin_9 0x09
#define PWMpin_10 0x0a
#define PWMpin_11 0x0b

#define Apin_0 0x00
#define Apin_1 0x01
#define Apin_2 0x02
#define Apin_3 0x03
#define Apin_4 0x04
#define Apin_5 0x05
#define Apin_6 0x06
#define Apin_7 0x07

#define DIGITAL_IN 0x01
#define DIGITAL_OUT 0x02
#define ANALOG_IN 0x03
#define ANALOG_OUT 0x04
#define WRITE_REG 0x05
#define READ_REG 0x06

#define LOW 0x00
#define HIGH 0x01

#define INPUT 0x00
#define OUTPUT 0x01

#define TX_SIZE 3
#define RX_SIZE 3

unsigned char tx_buff[TX_SIZE];
unsigned char rx_buff[RX_SIZE];

int fd ;

void digitalOut(unsigned char pin, unsigned char val) {
  tx_buff[0] = DIGITAL_OUT;
  tx_buff[1] = pin;
  tx_buff[2] = val;

  for (int i = 0; i < TX_SIZE; ++i) {
    serialPutchar(fd,tx_buff[i]);
  }
}

int digitalIn(unsigned char pin) {
  tx_buff[0] = DIGITAL_IN;
  tx_buff[1] = pin;
  tx_buff[2] = 0x00;

  for (int i = 0; i < TX_SIZE; ++i) {
    serialPutchar(fd,tx_buff[i]);
  }

  usleep(50000);
  
  return ((int)serialGetchar(fd));
}

void analogOut(unsigned char pin, unsigned char val) {
  tx_buff[0] = ANALOG_OUT;
  tx_buff[1] = pin;
  tx_buff[2] = val;

  for (int i = 0; i < TX_SIZE; ++i) {
    serialPutchar(fd,tx_buff[i]);
  }
}

int analogIn(unsigned char pin) {
  tx_buff[0] = ANALOG_IN;
  tx_buff[1] = pin;
  tx_buff[2] = 0x00;

  for (int i = 0; i < TX_SIZE; ++i) {
    serialPutchar(fd,tx_buff[i]);
  }

  usleep(50000);

  for (int i = 0; i < RX_SIZE; ++i)
    rx_buff[i] = serialGetchar(fd);

  int result = rx_buff[1];
  result = (result << 8);
  result += rx_buff[0];
  
  return result;
}

void writeReg(unsigned char reg , unsigned char val) {
  tx_buff[0] = WRITE_REG;
  tx_buff[1] = reg;
  tx_buff[2] = val;

  for (int i = 0; i < TX_SIZE; ++i) {
    serialPutchar(fd,tx_buff[i]);
  }
}

unsigned char readReg(unsigned char reg) {
  tx_buff[0] = READ_REG;
  tx_buff[1] = reg;
  tx_buff[2] = 0x00;

  for (int i = 0; i < TX_SIZE; ++i) {
    serialPutchar(fd,tx_buff[i]);
  }

  usleep(50000);
  
  for (int i = 0; i < RX_SIZE; ++i)
    rx_buff[i] = serialGetchar(fd);
  
  return (rx_buff[0]);
}

bool serialInit(const char* path, short speed) {
  if ((fd = serialOpen (path, speed)) < 0)
    return false;
  else {
  	sleep(2);
    return true;
  }
}
