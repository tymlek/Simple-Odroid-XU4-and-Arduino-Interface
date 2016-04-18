#define RX_SIZE 3
#define TX_SIZE 3

byte rx_buff[RX_SIZE];
byte tx_buff[TX_SIZE];
int counter;
int val;

void setup() {
  Serial.begin(9600);
}

void loop() {
  if (Serial.available() > 0) {  
    Serial.readBytes((char*)rx_buff,RX_SIZE);
    
    switch (rx_buff[0]) {
      // Digital Input
      case 0x01: {
        pinMode(rx_buff[1],INPUT);
        delay(50);
       
        Serial.write(digitalRead(rx_buff[1]));
        break;
      }
      
      // Digital Output
      case 0x02: {
        pinMode(rx_buff[1],OUTPUT);
        delay(50);
              
        digitalWrite(rx_buff[1],rx_buff[2]);
        break;
      }
      
      // Analog Input
      case 0x03: {
        val = 0;
        val = analogRead(rx_buff[1]);
        delay(50);
        tx_buff[0] = (byte)val;
        tx_buff[1] = byte(val >> 8);
        
        Serial.write(tx_buff,TX_SIZE);
        break;
      }
      
      // Analog Output - p3, p5, p6, p10, p11
      case 0x04: {
        pinMode(rx_buff[1],OUTPUT);
        delay(50);
        
        analogWrite(rx_buff[1],rx_buff[2]);
        break;
      }
      
      // Write register
      case 0x05: {
        (*((byte*)rx_buff[1])) = rx_buff[2];
        break;
      }
      
      // Read register
      case 0x06: {
        tx_buff[0] = (*((byte*)rx_buff[1]));
        delay(50);
        Serial.write(tx_buff,TX_SIZE);
        break;
      }
    }
  }
}
