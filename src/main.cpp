#include <Arduino.h>
#include <DHT.h>
#include <Wire.h>
#include <SeeedOLED.h>
#include <SFE_BMP180.h>

#define DHTPIN 2 //temp sensor
#define DHTTYPE DHT22
DHT dht(DHTPIN, DHTTYPE);

SFE_BMP180 pressure;
double baseline = 1013.25; // baseline pressure

double getPressure();
void drawData();
void drawGraph();

void setup()
{
    Serial.begin(9600);
    Serial.println("DHTxx test!");

    Wire.begin();
    SeeedOled.init();

    SeeedOled.clearDisplay();
    SeeedOled.setNormalDisplay();
    SeeedOled.setPageMode();

    SeeedOled.setTextXY(0,0);
    SeeedOled.putString("Weatherino");
    SeeedOled.setTextXY(7,0);
    SeeedOled.putString("blablabla");

    SeeedOled.setTextXY(2,0);
    SeeedOled.putString("T:");
    SeeedOled.setTextXY(2,11);
    SeeedOled.putString("C");

    SeeedOled.setTextXY(3,0);
    SeeedOled.putString("H:");
    SeeedOled.setTextXY(3,11);
    SeeedOled.putString("%");

    SeeedOled.setTextXY(4,0);
    SeeedOled.putString("P:");
    SeeedOled.setTextXY(4,11);
    SeeedOled.putString("mbar");

    SeeedOled.setTextXY(5,0);
    SeeedOled.putString("A:");
    SeeedOled.setTextXY(5,11);
    SeeedOled.putString("m");

    dht.begin();
    pressure.begin();
}

void loop()
{
    drawData();
    //drawGraph();
}

void drawData()
{
    float h = dht.readHumidity();
    float t = dht.readTemperature();
    double P = getPressure();
    double a = pressure.altitude(P,baseline);

    SeeedOled.setTextXY(2,4);
    SeeedOled.putFloat(t);
    SeeedOled.setTextXY(3,4);
    SeeedOled.putFloat(h);
    SeeedOled.setTextXY(4,4);
    SeeedOled.putFloat(P);
    SeeedOled.setTextXY(5,4);
    SeeedOled.putFloat(a);
    delay(2000);
}

void drawGraph()
{
    SeeedOled.clearDisplay();
    SeeedOled.putPixel(1, 1, true);
    delay(1000);
}


double getPressure()
{
    char status;
    double T,P;

    status = pressure.startTemperature();
    if (status != 0)
    {
        delay(status);
        status = pressure.getTemperature(T);
        if (status != 0)
        {
            status = pressure.startPressure(3);
            if (status != 0)
            {
                delay(status);
                status = pressure.getPressure(P,T);
                return P;
            }
        }
    }
}
