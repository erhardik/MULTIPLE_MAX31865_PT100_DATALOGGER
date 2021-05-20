#include <Adafruit_MAX31865.h>
#include "SPI.h"

// use hardware SPI, just pass in the CS pin
Adafruit_MAX31865 max_1 = Adafruit_MAX31865(10); // for first PT100 module
Adafruit_MAX31865 max_2 = Adafruit_MAX31865(9);  // for second PT100 module
Adafruit_MAX31865 max_3 = Adafruit_MAX31865(8);  // for third PT100 module
Adafruit_MAX31865 max_4 = Adafruit_MAX31865(7);  // for fourth PT100 module

// Use software SPI: CS, DI, DO, CLK
Adafruit_MAX31865 thermo = Adafruit_MAX31865(10, 11, 12, 13); // for single module use this otherwise delete this lines

// The value of the Rref resistor. Use 430.0 for PT100 & Use 4300 for PT1000! 
#define RREF 430.0       

// The 'nominal' 0-degrees-C resistance of the sensor
// 100.0 for PT100, 1000.0 for PT1000
#define RNOMINAL  100.0

void setup() {
  Serial.begin(115200);      // select same in serial monitor
  Serial.println("4 Channel Datalogger Start");  // inital messsage
  Serial.println("Find more at https://github.com/erhardik/iot");  // inital messsage
  SPI.begin();
  max_1.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  max_2.begin(MAX31865_3WIRE); // set to 2WIRE or 4WIRE as necessary
  max_3.begin(MAX31865_3WIRE);  // set to 2WIRE or 4WIRE as necessary
  max_4.begin(MAX31865_3WIRE); // set to 2WIRE or 4WIRE as necessary
}

void loop() {
  uint16_t rtd1 = max_1.readRTD();
  uint16_t rtd2 = max_2.readRTD();
  uint16_t rtd3 = max_3.readRTD();
  uint16_t rtd4 = max_4.readRTD();
  Serial.print("RTD value1: "); Serial.println(rtd1);
  Serial.print("RTD value2: "); Serial.println(rtd2);
  Serial.print("RTD value3: "); Serial.println(rtd3);
  Serial.print("RTD value4: "); Serial.println(rtd4);
  
  float ratio1 = rtd1;
  float ratio2 = rtd2;
  float ratio3 = rtd3;
  float ratio4 = rtd4;
  
  ratio1 /= 32768;
  ratio2 /= 32768;
  ratio3 /= 32768;
  ratio4 /= 32768;
  
  Serial.print("Resistance1 = "); Serial.println(RREF*ratio1,8);
    Serial.print("Resistance2 = "); Serial.println(RREF*ratio2,8);
  Serial.print("Resistance3 = "); Serial.println(RREF*ratio3,8);
    Serial.print("Resistance4 = "); Serial.println(RREF*ratio4,8);

  Serial.print("Temperature1 = "); Serial.println(max_1.temperature(RNOMINAL, RREF));
    Serial.print("Temperature2 = "); Serial.println(max_2.temperature(RNOMINAL, RREF));
  Serial.print("Temperature3 = "); Serial.println(max_3.temperature(RNOMINAL, RREF));
    Serial.print("Temperature4 = "); Serial.println(max_4.temperature(RNOMINAL, RREF));

  // Check and print any faults
  uint8_t fault1 = max_1.readFault();
  uint8_t fault2 = max_2.readFault();
  uint8_t fault3 = max_3.readFault();
  uint8_t fault4 = max_4.readFault();

  if (fault1) {
    Serial.print("Fault 0x"); Serial.println(fault1, HEX);
    if (fault1 & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault1 & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault1 & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault1 & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault1 & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault1 & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    max_1.clearFault();
  } 

  if (fault2) {
    Serial.print("Fault 0x"); Serial.println(fault2, HEX);
    if (fault2 & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault2 & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault2 & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault2 & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault2 & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault2 & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    max_2.clearFault();
  }

  if (fault3) {
    Serial.print("Fault 0x"); Serial.println(fault3, HEX);
    if (fault3 & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault3 & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault3 & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault3 & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault3 & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault3 & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    max_3.clearFault();
  }

  if (fault4) {
    Serial.print("Fault 0x"); Serial.println(fault4, HEX);
    if (fault4 & MAX31865_FAULT_HIGHTHRESH) {
      Serial.println("RTD High Threshold"); 
    }
    if (fault4 & MAX31865_FAULT_LOWTHRESH) {
      Serial.println("RTD Low Threshold"); 
    }
    if (fault4 & MAX31865_FAULT_REFINLOW) {
      Serial.println("REFIN- > 0.85 x Bias"); 
    }
    if (fault4 & MAX31865_FAULT_REFINHIGH) {
      Serial.println("REFIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault4 & MAX31865_FAULT_RTDINLOW) {
      Serial.println("RTDIN- < 0.85 x Bias - FORCE- open"); 
    }
    if (fault4 & MAX31865_FAULT_OVUV) {
      Serial.println("Under/Over voltage"); 
    }
    max_4.clearFault();
  }
  Serial.println();  // create one blank line before new logging
  delay(5000);      // set as per your data logging need, 5000 = at every 5 sec data will be pulled
}
