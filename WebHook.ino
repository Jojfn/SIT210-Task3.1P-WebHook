// This #include statement was automatically added by the Particle IDE.
#include <JsonParserGeneratorRK.h>

// This #include statement was automatically added by the Particle IDE.
#include <Grove_Temperature_And_Humidity_Sensor.h>


const int delay_time = 3000;

#define DHT_SENSOR D3

double hum;
double temp;

DHT dht(DHT_SENSOR);

void setup() {
    pinMode(DHT_SENSOR, INPUT);
}

void loop() {

//Using Grove library to determine temperature celcius and humidity
    temp = dht.getTempCelcius();
    hum = dht.getHumidity();
    TempHumWebhook(temp, hum);
    delay(delay_time);
}


//Creating a buffer for event load of both temperature and humidity
void TempHumWebhook(double temp, double hum){
    //Using JSON value to scope the object of tmperature and humidity
    JsonWriterStatic<256> jw;
    {
        JsonWriterAutoObject obj(&jw);
        jw.insertKeyValue("tempature", temp);
        jw.insertKeyValue("humidity", hum);
    }
    //publish to webhook
    Particle.publish("Argon_DHT", jw.getBuffer(), PRIVATE);
}
