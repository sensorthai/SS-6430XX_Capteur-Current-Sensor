//500A/5V
#include <Wire.h>
#include <Adafruit_ADS1X15.h>
 
Adafruit_ADS1115 ads;
//
double sqI,sumI;
double sampleI;
double Irms;
 
double squareRoot(double fg)
{
    double n = fg / 2.0;
    double lstX = 0.0;
    while (n != lstX)
    {
        lstX = n;
        n = (n + fg / n) / 2.0;
    }
    return n;
}
 
double calcIrms(unsigned int Number_of_Samples, float multiplier,double ical)
{
 
    for (unsigned int n = 0; n < Number_of_Samples; n++)
    {
        sampleI = (double)ads.readADC_Differential_0_1();
      //  Serial.println("Volt");
      //  Serial.println(sampleI);
        sqI = sampleI * sampleI;
        sumI += sqI;
    }
    Irms = squareRoot(sumI / Number_of_Samples) * multiplier * ical;
    sumI = 0;
//--------------------------------------------------------------------------------------
 
    return Irms;
}
 
 
 
void setup()
{
    Serial.begin(115200);
    Wire.begin();
    ads.setGain(GAIN_TWOTHIRDS);  // 2/3x gain +/- 6.144V  1 bit = 3mV      0.1875mV (default)
    ads.begin();
    Serial.println();
    Serial.println("current meter");
 
}
 
void loop()
{


      double Irms= calcIrms(64, 0.03125F,64) / 100;//SCT013 500A/5v
      Serial.print(Irms*220.0);        // Apparent power
      Serial.print(" SCT013 500A/5v ");
      Serial.println(Irms);            // Irms

    delay(1000);
}
 
 
 
