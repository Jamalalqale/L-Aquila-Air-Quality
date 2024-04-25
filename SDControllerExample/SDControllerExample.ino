#include <SPI.h>
#include <SD.h>

class DataFileController {
public:
  void setSDControlller() {
    if (!SD.begin(4)) {
      Serial.println("initialization SD failed!");
      while (1);
    }
    Serial.println("initialization SD done.");
  }

  File OpenFile(const char* fileName) {
    setSDControlller();
    File myFile = SD.open(fileName, FILE_WRITE);
    if (!myFile) {
      Serial.print(F("SD Card: error on opening file arduino.txt"));
    }
    return myFile;
  }

  void CloseFile(File myFile) {
    myFile.close();
  }

  void ReadFile(File myFile) {
 myFile = SD.open("MQReads.txt", FILE_READ);
  if (myFile) {
    while (myFile.available()) {
      char ch = myFile.read(); // read characters one by one from Micro SD Card
      Serial.print(ch); // print the character to Serial Monitor
    }
    myFile.close();
  } else {
    Serial.print(F("SD Card: error on opening file arduino.txt"));
  }
  }

  void StoreReads(const char* str, File myFile) {
    String receivedString = str;
    myFile.println(receivedString);
  }
};

File myFile;
DataFileController m_dataFileController;

void setup() {
  Serial.begin(9600);
  m_dataFileController.setSDControlller();
  myFile = m_dataFileController.OpenFile("MQReads.txt");
  const char* myString = "Hello, Arduino!";
  m_dataFileController.StoreReads(myString, myFile);
  m_dataFileController.CloseFile(myFile);
  m_dataFileController.ReadFile(myFile);
}

void loop() {
  // Your loop code here
}
