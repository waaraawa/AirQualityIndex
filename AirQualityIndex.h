#ifndef __AirQualityIndex_H__
#define __AirQualityIndex_H__

double getDewPoint(double celsius, double humidity);
int16_t getHeatIndex(float celsius, float humidity);

#endif // __AirQualityIndex_H__
