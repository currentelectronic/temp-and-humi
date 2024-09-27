#include <LiquidCrystal.h> // includes the LiquidCrystal Library
#include <dht.h>
#define dataPin 8

LiquidCrystal lcd(11, 10, 5, 4, 3, 2); // Creates an LCD object. Parameters: (rs, enable, d4, d5, d6, d7)
dht DHT;

int sensorPin = A0;
int adc = 0;
int ma = 0, ma_prv = 0;
float relay = 0;
unsigned long Time_Stamp;
bool LCD_Ready;

void setup() 
{
  pinMode(9, OUTPUT);

	lcd.begin(16,2); // Initializes the interface to the LCD screen, and specifies the dimensions (width and height) of the display
}

void loop() 
{
	int readData = DHT.read22(dataPin);
	float t = DHT.temperature;
	float h = DHT.humidity;

  unsigned char LCD_BUFF[16];
	 // Sets the location at which subsequent text written to the LCD will be displayed
	 // Prints string "Temp." on the LCD

	//Print temperature value in Celcius and Fahrenheit every alternate cycle
    adc = analogRead(sensorPin);
    ma = map(adc, 0, 1023, 0, 100);

    if(ma != ma_prv){
      ma_prv = ma;
      int (ma);
      Time_Stamp = millis();   
      lcd.clear();
    }
    else if((millis() - Time_Stamp) < 3000){
      lcd.setCursor(0, 0);
      lcd.print("Optimal Humidity");

      lcd.setCursor(0, 1);
      lcd.setCursor(6, 1);
      lcd.print(ma);

      LCD_Ready = 0;
    }
    else if(LCD_Ready){
      lcd.setCursor(0,0);  lcd.print("Temp: ");
      lcd.setCursor(15,0); lcd.print("C");

      lcd.setCursor(0,1); lcd.print("Humi: ");
      lcd.setCursor(15,1); lcd.print("%");

      lcd.setCursor(6,0);
		  lcd.print(t); // Prints the temperature value from the sensor
		  lcd.setCursor(6,1);
	    lcd.print(h);
    }
    else if(!LCD_Ready) {lcd.clear(); LCD_Ready = 1;}

    relay = (ma - h);

    if(relay >= 3 )
    {
      digitalWrite(9, LOW);
    }
    else if(relay <= -3)
    {
      digitalWrite(9, HIGH);
    }

}