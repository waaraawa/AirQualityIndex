#include <Arduino.h>

// getDewPoint function NOAA
// reference (1): http://wahiduddin.net/calc/density_algorithms.htm
// reference (2): http://www.colorado.edu/geography/weather_station/Geog_site/about.htm
//
double getDewPoint(double celsius, double humidity)
{
    // (1) Saturation Vapor Pressure = ESGG(T)
    double RATIO = 373.15 / (273.15 + celsius);
    double RHS = -7.90298 * (RATIO - 1);
    RHS += 5.02808 * log10(RATIO);
    RHS += -1.3816e-7 * (pow(10, (11.344 * (1 - 1/RATIO ))) - 1) ;
    RHS += 8.1328e-3 * (pow(10, (-3.49149 * (RATIO - 1))) - 1) ;
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
// 80 ~ 90: Caution
// 91 ~ 102: Extream Caution
// 103 ~ 124: Danger
// 125 ~ : Extream Danger
int16_t getHeatIndex(float celsius, float humidity)
{
    float f = (celsius * 9 / 5) + 32;
	float rh = humidity;
	float adj = 0;

    int16_t hi = 0;

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

    Serial.print("c: ");
    Serial.print(celsius);
    Serial.print("f: ");
    Serial.print(f);
    Serial.print(", hi: ");
    Serial.print(hi);
    Serial.print(", adj: ");
    Serial.println(adj);
    return hi + adj;
}
