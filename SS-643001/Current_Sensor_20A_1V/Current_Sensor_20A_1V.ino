//20A/1V
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
    ads.setGain(GAIN_FOUR);       // 4x gain   +/- 1.024V  1 bit = 0.5mV    0.03125mV 20A/1V
    ads.begin();
    Serial.println();
    Serial.println("current meter");
 
}
 
void loop()
{
    double Irms = calcIrms(64, 0.03125F,2.83) / 100;//SCT013 20A/1v
    Serial.print(Irms*220.0);        // Apparent power
    Serial.print(" SCT013 20A/1v ");
    Serial.println(Irms);            // Irms


    delay(1000);
}
 
 
 
