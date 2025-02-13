// nrf24_client.pde
// -*- mode: C++ -*-
// Example sketch showing how to create a simple messageing client
// with the RH_NRF24 class. RH_NRF24 class does not provide for addressing or
// reliability, so you should only use RH_NRF24 if you do not need the higher
// level messaging abilities.
// It is designed to work with the other example nrf24_server.
// Tested on Uno with Sparkfun NRF25L01 module
// Tested on Anarduino Mini (http://www.anarduino.com/mini/) with RFM73 module
// Tested on Arduino Mega with Sparkfun WRL-00691 NRF25L01 module

#include <SPI.h>
#include <RH_NRF24.h>

// Singleton instance of the radio driver
RH_NRF24 nrf24;

void setup() 
{
  pinMode(4, INPUT);

  //these four are for detecting flipped switches
  pinMode(9, INPUT);
  pinMode(7, INPUT);
  pinMode(6, INPUT);
  pinMode(5, INPUT);
  
  Serial.begin(9600);
  while (!Serial) 
    ; // wait for serial port to connect. Needed for Leonardo only
  if (!nrf24.init())
    Serial.println("init failed");
  // Defaults after init are 2.402 GHz (channel 2), 2Mbps, 0dBm
  if (!nrf24.setChannel(1))
    Serial.println("setChannel failed");
  if (!nrf24.setRF(RH_NRF24::DataRate2Mbps, RH_NRF24::TransmitPower0dBm))
    Serial.println("setRF failed");    
}


void loop()
{



  while ( digitalRead(7) != HIGH ) {
    Serial.println(" key NOT SWITCHED");
    delay(10);
  }

/*
      while ( digitalRead(5) != HIGH || digitalRead(9) != HIGH ) {
    Serial.println(" switch NOT SWITCHED");
    delay(10);
  }

   while ( digitalRead(6) != HIGH || digitalRead(5) != HIGH || digitalRead(9) != HIGH ) {
    Serial.println(" button NOT SWITCHED");
    delay(10);
  }

*/

  //pin 5 is the panic close button
  if( digitalRead(5) == HIGH ) {
    
    //send the signal to send the signal




  Serial.println("Sending hard close signal");
  // Send a message to nrf24_server
  uint8_t data1[] = "Panic Button Close";
  nrf24.send(data1, sizeof(data1));
  
  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  {
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);

    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running? 1");
  }
  delay(400);





    
  }

  else {
  
  Serial.println("Sending to nrf24_server");
  // Send a message to nrf24_server
  uint8_t data[] = "Hello World!";
  nrf24.send(data, sizeof(data));
  
  nrf24.waitPacketSent();
  // Now wait for a reply
  uint8_t buf[RH_NRF24_MAX_MESSAGE_LEN];
  uint8_t len = sizeof(buf);

  if (nrf24.waitAvailableTimeout(500))
  {
    // Should be a reply message for us now   
    if (nrf24.recv(buf, &len))
    {
      Serial.print("got reply: ");
      Serial.println((char*)buf);

    }
    else
    {
      Serial.println("recv failed");
    }
  }
  else
  {
    Serial.println("No reply, is nrf24_server running? 2");
  }
  delay(400);
}
}
