#ifndef __AirQualityIndex_H__
#define __AirQualityIndex_H__

typedef enum
{
    EOHI_NORMAL,
    EOHI_CAUTION,
    EOHI_EXTREME_CAUTION,
    EOHI_DANGER,
    EOHI_EXTREME_DANGER,
} effect_of_heat_index;

float celsiusToFahrenheit(
    float celsius);

float fahrenheitToCelsius(
    float fahrenheit);

double getDewPoint(
    bool fahrenheit,
    double temperature,
    double humidity);

int16_t getHeatIndex(
    bool fahrenheitIn,
    float temperature,
    float humidity,
    bool fahrenheitOut);

effect_of_heat_index getEffectOfHeatIndex(
    bool fahrenheit,
    float temperature);

#endif // __AirQualityIndex_H__
