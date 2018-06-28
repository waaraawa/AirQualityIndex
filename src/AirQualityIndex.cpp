/*
	AirQualityIndex.cpp - Library for getting weather related information.
*/

#include <Arduino.h>
#include <math.h>
#include "AirQualityIndex.h"

Weather::Weather(NWS_HIL_DESC_LANGUAGE lang) {
	m_language = lang;
}

float Weather::getCelsius(float fahrenheit) {
	return (fahrenheit - 32) * 0.55555;
}

float Weather::getFahrenheit(float celsius) {
	return celsius * 1.8 + 32;
}

// https://en.wikipedia.org/wiki/Dew_point#Simple_approximation
float Weather::getDewPoint(float temperature, float humidity, bool isFahrenheit) {
	float dp;

	if (!isFahrenheit)
		temperature = getFahrenheit(temperature);

	dp = temperature - (9 / 25 * (100 - humidity));
//    dp = temperature - ((100 - humidity) / 5);

	return isFahrenheit ? dp : getCelsius(dp);
}

// https://gist.github.com/Mausy5043/4179a715d616e6ad8a4eababee7e0281
// reference: http://wahiduddin.net/calc/density_algorithms.htm
float Weather::getDewPoint2(float temperature, float humidity, bool isFahrenheit) {
	if (isFahrenheit)
		temperature = getCelsius(temperature);

	float RATIO = 373.15 / (273.15 + temperature);  // RATIO was originally named A0, possibly confusing in Arduino context
	float SUM = -7.90298 * (RATIO - 1);
	SUM += 5.02808 * log10(RATIO);
	SUM += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
	SUM += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
	SUM += log10(1013.246);
	float VP = pow(10, SUM - 3) * humidity;
	float T = log(VP / 0.61078);   // temp var
//    return (241.88 * T) / (17.558 - T);
	float Dp = (241.88 * T) / (17.558 - T);
	return !isFahrenheit ? Dp : getFahrenheit(Dp);
}

// delta max = 0.6544 wrt dewPoint()
// 5x faster than dewPoint()
// reference: http://en.wikipedia.org/wiki/Dew_point
float Weather::getDewPointFast(float temperature, float humidity, bool isFahrenheit) {
	if (isFahrenheit)
		temperature = getCelsius(temperature);

	float a = 17.271;
	float b = 237.7;
	float temp = (a * temperature) / (b + temperature) + log(humidity * 0.01);
	float Td = (b * temp) / (a - temp);
//    return Td;
	return !isFahrenheit ? Td : getFahrenheit(Td);
}

// https://en.wikipedia.org/wiki/Dew_point#Simple_approximation
float Weather::getHumidity(float temperature, float dewPoint, bool isFahrenheit) {
	float hu;

	if (!isFahrenheit) {
		temperature = getFahrenheit(temperature);
		dewPoint = getFahrenheit(dewPoint);
	}

	hu = 100 - (25 / 9 * (temperature - dewPoint));
//    hu = 100 - (5 * (temperature - dewPoint));

	return isFahrenheit ? hu : getCelsius(hu);
}

// https://github.com/adafruit/DHT-sensor-library/blob/master/DHT.cpp
//boolean isFahrenheit: True == Fahrenheit; False == Celcius
//float Weather::computeHeatIndex(float temperature, float percentHumidity, bool isFahrenheit) {
float Weather::getHeatIndex(float temperature, float humidity, float dewPoint, bool isFahrenheit) {
	// Using both Rothfusz and Steadman's equations
	// http://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml
	float hi;

	if (!isFahrenheit)
		temperature = getFahrenheit(temperature);

	if (-1 == humidity) {
		humidity = getHumidity(temperature, dewPoint, isFahrenheit);
	}

	hi = 0.5 * (temperature + 61.0 + ((temperature - 68.0) * 1.2) + (humidity * 0.094));

	if (hi > 79) {
		hi = -42.379 +
			(2.04901523 * temperature) +
			(10.14333127 * humidity) +
			(-0.22475541 * temperature*humidity) +
			(-0.00683783 * pow(temperature, 2)) +
			(-0.05481717 * pow(humidity, 2)) +
			(0.00122874 * pow(temperature, 2) * humidity) +
			(0.00085282 * temperature*pow(humidity, 2)) +
			(-0.00000199 * pow(temperature, 2) * pow(humidity, 2));

		if((humidity < 13) && (temperature >= 80.0) && (temperature <= 112.0))
			hi -= ((13.0 - humidity) * 0.25) * sqrt((17.0 - abs(temperature - 95.0)) * 0.05882);
		else if((humidity > 85.0) && (temperature >= 80.0) && (temperature <= 87.0))
			hi += ((humidity - 85.0) * 0.1) * ((87.0 - temperature) * 0.2);
	}

	return isFahrenheit ? hi : getCelsius(hi);
}

NWS_HEAT_INDEX_LEVEL Weather::getHeatIndexLevel(float heatIndex) {
	NWS_HEAT_INDEX_LEVEL level = NWS_NORMAL;

	if (79 >= heatIndex) {
		// Normal, less than 80
		level = NWS_NORMAL;
	} else if ((80 <= heatIndex) && (90 > heatIndex)) {
		// Caution, 80 ~ 89
		level = NWS_CAUTION;
	} else if ((90 <= heatIndex) && (106 > heatIndex)) {
		// Extream Caution, 90 ~ 105
		level = NWS_EXT_CAUTION;
	} else if ((106 <= heatIndex) && (130 > heatIndex)) {
		// Danger, 106 ~ 129
		level = NWS_DANGER;
	} else if (130 <= heatIndex) {
		// Extream Danger, over 130
		level = NWS_EXT_DANGER;
	}

	return level;
}

char* Weather::getHeatIndexTag(float heatIndex) {
	NWS_HEAT_INDEX_LEVEL level = NWS_NORMAL;

	if (79 >= heatIndex) {
		// Normal, less than 80
		level = NWS_NORMAL;
	} else if ((80 <= heatIndex) && (90 > heatIndex)) {
		// Caution, 80 ~ 89
		level = NWS_CAUTION;
	} else if ((90 <= heatIndex) && (106 > heatIndex)) {
		// Extream Caution, 90 ~ 105
		level = NWS_EXT_CAUTION;
	} else if ((106 <= heatIndex) && (130 > heatIndex)) {
		// Danger, 106 ~ 129
		level = NWS_DANGER;
	} else if (130 <= heatIndex) {
		// Extream Danger, over 130
		level = NWS_EXT_DANGER;
	}

	return getHeatIndexTag(level);
}

char* Weather::getHeatIndexTag(NWS_HEAT_INDEX_LEVEL level) {
	return m_hilStr[m_language][level].levelTag;
}

char* Weather::getHeatIndexDesc(float heatIndex) {
	NWS_HEAT_INDEX_LEVEL level = NWS_NORMAL;

	if (79 >= heatIndex) {
		// Normal, less than 80
		level = NWS_NORMAL;
	} else if ((80 <= heatIndex) && (90 > heatIndex)) {
		// Caution, 80 ~ 89
		level = NWS_CAUTION;
	} else if ((90 <= heatIndex) && (106 > heatIndex)) {
		// Extream Caution, 90 ~ 105
		level = NWS_EXT_CAUTION;
	} else if ((106 <= heatIndex) && (130 > heatIndex)) {
		// Danger, 106 ~ 129
		level = NWS_DANGER;
	} else if (130 <= heatIndex) {
		// Extream Danger, over 130
		level = NWS_EXT_DANGER;
	}

	return getHeatIndexDesc(level);
}

char* Weather::getHeatIndexDesc(NWS_HEAT_INDEX_LEVEL level) {
	return m_hilStr[m_language][level].levelDesc;
}
