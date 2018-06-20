#include <weather.h>

Weather weather;

void setup()
{
    Serial.begin(9600);

    float celsius = 32.12;
    float humidity = 56.39;
    float fahrenheit;
    float heatIndex;
    float dewPoint;

    Serial.print("celsius: ");
    Serial.println(celsius);
    Serial.print("humidity: ");
    Serial.println(humidity);

    fahrenheit = weather.getFahrenheit(celsius);
    Serial.print("fahrenheit: ");
    Serial.println(fahrenheit);
    Serial.print("f to celsius: ");
    Serial.println(weather.getCelsius(fahrenheit));

    Serial.print("dewPointF: ");
    Serial.println(weather.getDewPoint(fahrenheit, humidity, true));
    Serial.print("dewPointC: ");
    Serial.println(weather.getDewPoint(celsius, humidity));

    Serial.print("dewPoint2F: ");
    Serial.println(weather.getDewPoint2(fahrenheit, humidity, true));
    Serial.print("dewPoint2C: ");
    Serial.println(weather.getDewPoint2(celsius, humidity));

    Serial.print("dewPointFastF: ");
    Serial.println(weather.getDewPointFast(fahrenheit, humidity, true));
    Serial.print("dewPointFastC: ");
    Serial.println(weather.getDewPointFast(celsius, humidity));

    Serial.print("dewPointFastC: ");
    Serial.println(weather.getDewPointFast(celsius, humidity));

    dewPoint = weather.getDewPoint2(celsius, humidity);
    Serial.print("humidity by dew pointF: ");
    Serial.println(weather.getHumidity(fahrenheit, dewPoint, true));
    Serial.print("humidity by dew pointC: ");
    Serial.println(weather.getHumidity(celsius, dewPoint));

    Serial.print("heatIndexF: ");
    Serial.println(weather.getHeatIndex(fahrenheit, humidity, -1, true));
    Serial.print("heatIndexC: ");
    Serial.println(weather.getHeatIndex(celsius, humidity));
    Serial.print("heatIndex by dew pointF: ");
    Serial.println(weather.getHeatIndex(celsius, -1, dewPoint, true));
    Serial.print("heatIndex by dew pointC: ");
    Serial.println(weather.getHeatIndex(celsius, -1, dewPoint));

    Serial.print("Heat Index Test");
    for(size_t i = 0; i < 300; i++) {
        Serial.print("index(");
        Serial.print(i);
        Serial.print(") ");
        Serial.print(weather.getHeatIndexTag(i));
        Serial.print(", ");
        Serial.println(weather.getHeatIndexTag(i));
    }
}

void loop()
{
    delay(1000);
}
