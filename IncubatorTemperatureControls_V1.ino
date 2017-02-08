#include <math.h>
#include <LiquidCrystal.h>

// initialize the library with the numbers of the interface pins
LiquidCrystal lcd(2, 3, 8, 9, 10, 11);
int sensorPin = 1;      //This is the Arduino Pin that will control Relay #1
int sensorInput;        //The variable we will use to store the sensor input
int solenoidPin = 4;    //This is the output pin on the Arduino we are using
double temp;            //Temperature variable in Degrees Celcius
double tempF;           //Temperature in Farenheit
int i = 0;              //Valve position variable 
int SPKR = 12;          //Buzzer Pin

void setup() {
  pinMode(solenoidPin, OUTPUT);           //Sets the pin as an output
  digitalWrite(solenoidPin, LOW);
  pinMode(SPKR, OUTPUT);                  //Speaker now output
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {

  sensorInput = analogRead(A0);    //read the analog sensor and store it
  temp = (double)sensorInput / 1024;       //find percentage of input reading
  temp = temp * 5;                 //multiply by 5V to get voltage
  temp = temp - 0.5;               //Subtract the offset
  temp = temp * 100;               //Convert to degrees
  temp = temp + 28.52;             //Calibrate: linearize
  tempF = (temp * 9.0) / 5.0 + 32.0;

  if (temp > 30 && i == 1) {
    digitalWrite(SPKR, HIGH);          //Switch Speaker ON
    delay(500);
    digitalWrite(SPKR, LOW);           //Switch Speaker OFF 
    digitalWrite(solenoidPin, LOW);    //Switch Solenoid OFF
    i = i - 1;                         //Inform valve is closed
  }
  if (temp < 29 && i == 0) {
    digitalWrite(SPKR, HIGH);          //Switch Speaker ON
    delay(500);
    digitalWrite(SPKR, LOW);           //Switch Speaker OFF 
    digitalWrite(solenoidPin, HIGH);    //Switch Solenoid ON
    i = i + 1;                          //Inform valve has opened  
  }

  //Serial Monitor Output
  Serial.print("Current Temperature: ");
  Serial.print(temp);
  Serial.print(" C    ");
  Serial.print(tempF);
  Serial.println(" F");


  //LCD Output
  lcd.print("Temp = ");
  lcd.print(temp);
  lcd.println(" C  ");
  lcd.setCursor(0, 1); //new row for Farenheit
  lcd.print("Temp = ");
  lcd.print(tempF);
  lcd.println(" F  ");
  delay(4000);                              //Taking readings every 5 seconds                        
  lcd.clear();
}
