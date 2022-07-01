// https://www.programmingboss.com/2021/04/esp32-arduino-serial-communication-with-code.html

#include <SoftwareSerial.h>
#include <ArduinoJson.h>

const int baudMain = 115200;
const int baudSub = 9600;

const bool flagDevelopment = false;

bool flagReady = false;
bool isReadyScanner = false;

int countNoScanner = 0;

#define PIN_RX_SIM 10
#define PIN_TX_SIM 11
#define PIN_RX_SCN 12
#define PIN_TX_SCN 13

SoftwareSerial serialSim800L(PIN_RX_SIM, PIN_TX_SIM); // RX, TX
SoftwareSerial serialScanner(PIN_RX_SCN, PIN_TX_SCN); // RX, TX

String apn = "internet";                 // APN
String apn_u = "";                       // APN-Username
String apn_p = "";                       // APN-Password
String url = "http://url.com/index.php"; // URL for HTTP-POST-REQUEST
String data1;                            // String for the first Paramter (e.g. Sensor1)
String data2;                            // String for the second Paramter (e.g. Sensor2)

void setup()
{
  Serial.begin(baudSub);
  Serial1.begin(baudSub); // IN: SEND SCANNED DATA TO ESP32
  // Serial2.begin(baud);
  serialSim800L.begin(baudSub);
  serialScanner.begin(baudSub); // OUT:  SEND SCANNED DATA TO ESP32

  Serial.println("System starts...");
}

void loop()
{
  if (flagReady == false)
  {
    flagReady = true;
    serialSim800L.println("Mingxi");
    Serial.println("Ready!");
  }

  data1 = "123";
  data2 = "ABC";
  // gsm_sendhttp(); // Start the GSM-Modul and start the transmisson
  // delay(1000);    // Wait one minute

  // if (serialScanner.available()) // Check if there is Incoming Data in the Serial Buffer.
  // {
  //   while (serialScanner.available()) // Keep reading Byte by Byte from the Buffer till the Buffer is empty
  //   {
  //     char input = serialScanner.read(); // Read 1 Byte of data and store it in a character variable
  //     serialScanner.print(input); // Print the Byte
  //     delay(5); // A small delay
  //   }
  //   serialScanner.println();
  // }

  // if (Serial.available()) // Check if there is Incoming Data in the Serial Buffer.
  // {
  //   String input = Serial.readString(); // Read 1 Byte of data and store it in a character variable
  //   Serial.println(input);                // Print the Byte
  //   Serial1.println(input);
  //   // delay(5); // A small delay
  //   delay(1000);
  // }

  if (serialSim800L.available())
  {
    Serial.write(serialSim800L.read());
  }

  if (Serial.available())
  {
    serialSim800L.write(Serial.read());
  }

  // if (Serial2.available())
  // {
  //   Serial.write(Serial2.read());
  // }

  // if (Serial.available())
  // {
  //   Serial2.write(Serial.read());
  // }

  bool flag = serialScanner.available();
  bool displayInfo = false;

  String info = "CONNECTION - NETWORK <-> MAIN: ";
  String message = "";

  if (flag) // Check if there is Incoming Data in the Serial Buffer.
  {
    displayInfo = true;
    info += "OK";
    message = "The Scanner is activated!";
    String input = serialScanner.readString(); // Read 1 Byte of data and store it in a character variable
    
    if (flagDevelopment) {
      Serial.println(input);
    }

    Serial1.println(input);
  }
  else
  {
    Serial1.println();
    delay(1000);
  }

  // HANDEL HTTP RESPONSE
  if (Serial1.available())
  {
    String response = Serial1.readString();  
    execute(response);
  }

  if (flag != isReadyScanner)
  {
    if (flag)
    {
      isReadyScanner = flag;
      Serial.println(info);
      Serial.println(message);
    }
  }
  // else
  // {
  //   if (flag == false) {
  //     info += "ERROR";
  //     message = "Please check the connection between boards!";
  //     delay(1000);
  //   }

  //   isReadyScanner = flag;
  //   Serial.println(info);
  //   Serial.println(message);
  // }

} // END - loop()

void gsm_sendhttp()
{
  Serial.println("Start GSM!");
  serialSim800L.println("AT");
  runsl(); // Print GSM Status an the Serial Output;
  // delay(4000);
  // serialSim800L.println("AT+SAPBR=3,1,Contype,GPRS");
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+SAPBR=3,1,APN," + apn);
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+SAPBR=3,1,USER," + apn_u); // Comment out, if you need username
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+SAPBR=3,1,PWD," + apn_p); // Comment out, if you need password
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+SAPBR =1,1");
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+SAPBR=2,1");
  // runsl();
  // delay(2000);
  // serialSim800L.println("AT+HTTPINIT");
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+HTTPPARA=CID,1");
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+HTTPPARA=URL," + url);
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+HTTPPARA=CONTENT,application/x-www-form-urlencoded");
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+HTTPDATA=192,10000");
  // runsl();
  // delay(100);
  // serialSim800L.println("params=" + data1 + "~" + data2);
  // runsl();
  // delay(10000);
  // serialSim800L.println("AT+HTTPACTION=1");
  // runsl();
  // delay(5000);
  // serialSim800L.println("AT+HTTPREAD");
  // runsl();
  // delay(100);
  // serialSim800L.println("AT+HTTPTERM");
  // runsl();
}

// Print GSM Status
void runsl()
{
  while (serialSim800L.available())
  {
    Serial.write(serialSim800L.read());
  }
}
