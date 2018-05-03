# AirQualityIndex
Calculate air quality index and related things.

float celsiusToFahrenheit(float celsius);  
float fahrenheitToCelsius(float fahrenheit);

getDewPoint function NOAA  
reference (1): http://wahiduddin.net/calc/density_algorithms.htm  
reference (2): http://www.colorado.edu/geography/weather_station/Geog_site/about.htm  
double getDewPoint(bool fahrenheit, double temperature, double humidity);

getHeatIndex function NOAA  
reference: http://www.nws.noaa.gov/os/heat/heat_index.shtml  
reference: http://www.wpc.ncep.noaa.gov/html/heatindex.shtml  
reference: http://www.wpc.ncep.noaa.gov/html/heatindex_equation.shtml  
reference: https://en.wikipedia.org/wiki/Heat_index  
80 ~ 89: Caution  
90 ~ 105: Extreme Caution  
105 ~ 130: Danger  
130 ~ : Extreme Danger  

int16_t getHeatIndex(bool fahrenheit, float temperature, float humidity);

effect_of_heat_index getEffectOfHeatIndex(bool fahrenheit, float temperature);
