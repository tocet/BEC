#define BAUDRATE 115200
#include <SFE_BMP180.h>
#include <Wire.h>

#define ALTITUDE 37.0 // altitude of Bydgoszcz, in meters

SFE_BMP180 bmp180;
char status;
double temp,pressure,p0,a;

void setup() {
  Serial.begin(BAUDRATE);
  Serial.println("Sensor init");
  if (bmp180.begin())
    Serial.println("BMP180 init success");
   else {
    Serial.println("BMP180 init failure");
    while(1); }
}

void loop() {
/*
1. You must first get a temperature measurement to perform a pressure reading.
2. Start a temperature measurement:
 If request is successful, the number of ms to wait is returned.
 If request is unsuccessful, 0 is returned.
*/  
  status = bmp180.startTemperature();
  if (status != 0) {
   delay(status);

//3. Function returns 1 if successful, 0 if failure
 
   status = bmp180.getTemperature(temp);
   if (status != 0)     {
    Serial.print("Temperature: ");
    Serial.print(temp,2);
    Serial.println(" deg C");
     
//4. Start a pressure measurement:
// The parameter is the oversampling setting, from 0 to 3 (highest res, longest wait).
// If request is successful, the number of ms to wait is returned.
// If request is unsuccessful, 0 is returned.
    status = bmp180.startPressure(3);
     if (status != 0) {
      delay(status);

//5. Retrieve the completed pressure measurement:
// The function requires the previous temperature measurement (T).
// (If temperature is stable, you can do one temperature measurement for a number of pressure measurements.)
// Function returns 1 if successful, 0 if failure.

      status = bmp180.getPressure(pressure,temp);
      if (status != 0) {
       Serial.print("Absolute pressure: ");
       Serial.print(pressure,2);
       Serial.println(" mb");

//6. The pressure sensor returns abolute pressure, which varies with altitude.
// To remove the effects of altitude, use the sealevel function and your current altitude.
// This number is commonly used in weather reports.
// Parameters: P = absolute pressure in mb, ALTITUDE = current altitude in m.
// Result: p0 = sea-level compensated pressure in mb

       p0 = bmp180.sealevel(pressure,ALTITUDE); 
       Serial.print("Sea-level pressure: ");
       Serial.print(p0,2);
       Serial.println(" mb");

//7. If you want to determine your altitude from the pressure reading,

       a = bmp180.altitude(pressure,p0);
       Serial.print("Computed altitude: ");
       Serial.print(a,0);
       Serial.println(" meters");
        }
        else Serial.println("error retrieving pressure measurement\n");
      }
      else Serial.println("error starting pressure measurement\n");
    }
    else Serial.println("error retrieving temperature measurement\n");
  }
  else Serial.println("error starting temperature measurement\n");
  delay(5000);  
}
