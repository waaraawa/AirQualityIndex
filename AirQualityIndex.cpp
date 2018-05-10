#include <Arduino.h>
#include "AirQualityIndex.h"

float celsiusToFahrenheit(
    float celsius)
{
    return (celsius * 9.0 / 5.0) + 32;
}

float fahrenheitToCelsius(
    float fahrenheit)
{
    return (fahrenheit - 32) * (5.0 / 9.0);
}

// getDewPoint function NOAA
// reference (1): http://wahiduddin.net/calc/density_algorithms.htm
// reference (2): http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double getDewPoint(
    bool fahrenheit,
    double temperature,
    double humidity)
{
    double celsius;

    if (fahrenheit) {
        celsius = fahrenheitToCelsius(temperature);
    } else {
        celsius = temperature;
    }
    // (1) Saturation Vapor Pressure = ESGG(T)
    double RATIO = 373.15 / (273.15 + celsius);
    double RHS = -7.90298 * (RATIO - 1);
    RHS += 5.02808 * log10(RATIO);
    RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1);
    RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1);
    RHS += log10(1013.246);

    // factor -3 is to adjust units - Vapor Pressure SVP * humidity
    double VP = pow(10, RHS - 3) * humidity;

    // (2) DEWPOINT = F(Vapor Pressure)
    double T = log(VP/0.61078);   // temp var

    return (241.88 * T) / (17.558 - T);
}

// getHeatIndex function NOAA
// reference: http://www.nws.noaa.gov/os/heat/heat_index.shtml
// reference: http://www.wpc.ncep.noaa.gov/html/heatindex.shtml
// reference: http://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
// reference: https://en.wikipedia.org/wiki/Heat_index
// 80 ~ 89: Caution
// 90 ~ 105: Extreme Caution
// 105 ~ 130: Danger
// 130 ~ : Extreme Danger
int16_t getHeatIndex(
    bool fahrenheitIn,
    float temperature,
    float humidity,
    bool fahrenheitOut)
{
    float f;
	float rh = humidity;
	float adj = 0;

    int16_t hi = 0;

    if (fahrenheitIn) {
        f = temperature;
    } else {
        f = celsiusToFahrenheit(temperature);
    }

	if(80 < f) {
		hi = -42.379 + 2.04901523*f + 10.14333127*rh - .22475541*f*rh -
	 			.00683783*f*f - .05481717*rh*rh + .00122874*f*f*rh +
				.00085282*f*rh*rh - .00000199*f*f*rh*rh;

		if ((13 > rh) && ((80 <= f) && (112 >= f)))
			adj = -(((13-rh)/4)*sqrt((17-abs(f-95.))/17));

		if ((85 < rh) && ((80 <= f) && (87 >= f)))
			adj = ((rh-85)/10) * ((87-f)/5);
	} else {
		hi = 0.5 * (f + 61.0 + ((f-68.0)*1.2) + (rh*0.094));
	}

    if (fahrenheitOut) {
        return hi + adj;
    } else {
        return fahrenheitToCelsius(hi + adj);
    }
}

effect_of_heat_index getEffectOfHeatIndex(
    bool fahrenheit,
    float temperature)
{
    effect_of_heat_index ret;
    float f;

    if (fahrenheit) {
        f = temperature;
    } else {
        f = celsiusToFahrenheit(temperature);
    }

    if (80 > f) {
        ret = EOHI_NORMAL;
    } else if ((80 <= f) && (90 >= f)) {
        ret = EOHI_CAUTION;
    } else if ((91 < f) && (105 >= f)) {
        ret = EOHI_EXTREME_CAUTION;
    } else if ((105 < f) && (130 >= f)) {
        ret = EOHI_DANGER;
    } else {
        ret = EOHI_EXTREME_DANGER;
    }

    return ret;
}
