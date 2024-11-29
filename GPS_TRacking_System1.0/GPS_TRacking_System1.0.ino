#include <SoftwareSerial.h>
#include <TinyGPS++.h>

String Latitude;
String Longitude;

TinyGPSPlus gps;

SoftwareSerial gpsSerial(2,3); // RXpin, TXpin(for GPS module)

void setup() {
  Serial.begin(9600);
  gpsSerial.begin(9600);
  // Initialize GSM module
  Serial.println("AT");
}

void loop() {
  // Read GPS data
 while (gpsSerial.available() > 0){
    gps.encode(gpsSerial.read());
    if (gps.location.isUpdated()){
      Latitude=gps.location.lat();
      Longitude=gps.location.lng();
    }
  }
    // Formulate SMS message
    String smsMessage = "Live Location: https://maps.google.com/maps?q="+Latitude+","+Longitude +"";

    // Send SMS through GSM module
    Serial.println("AT+CMGF=1"); // Set SMS mode to text
    delay(1000);
    Serial.println("AT+CMGS=\"+917439928541\"\r"); // Replace with your phone number
    delay(1000);
    Serial.println(smsMessage);
    delay(1000);
    Serial.println((char)26); // End SMS with Ctrl+Z
    delay(2000); // Allow time for SMS to be sent 
}