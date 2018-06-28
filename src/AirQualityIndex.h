/*
	AirQualityIndex.h - Library for getting weather related information.
*/

#include <String.h>

#ifndef AirQualityIndex_H
#define AirQualityIndex_H

typedef enum _NWS_HIL_DESC_LANGUAGE {
	EN_US = 0,
	KO_KR = 1,
} NWS_HIL_DESC_LANGUAGE, *NWS_HIL_DESC_LANGUAGE_P;
#define HIL_LANGUAGE_COUNT 2

typedef enum _NWS_HEAT_INDEX_LEVEL {
	NWS_NORMAL = 0,
	NWS_CAUTION = 1,
	NWS_EXT_CAUTION = 2,
	NWS_DANGER = 3,
	NWS_EXT_DANGER = 4,
} NWS_HEAT_INDEX_LEVEL, *NWS_HEAT_INDEX_LEVEL_P;
#define HIL_INDEX_LEVEL_COUNT 5

typedef struct _NWS_HIL_ELEMENT {
	char levelTag[16];
	char levelDesc[140];
} NWS_HIL_ELEMENT, *NWS_HIL_ELEMENT_P;

#define NWS_NORMAL_TAG_EN_US "Normal"
#define NWS_NORMAL_TAG_KO_KR "보통"
#define NWS_CAUTION_TAG_EN_US "Caution"
#define NWS_CAUTION_TAG_KO_KR "주의"
#define NWS_EXT_CAUTION_TAG_EN_US "Extream Caution"
#define NWS_EXT_CAUTION_TAG_KO_KR "매우 주의"
#define NWS_DANGER_TAG_EN_US "Danger"
#define NWS_DANGER_TAG_KO_KR "위험"
#define NWS_EXT_DANGER_TAG_EN_US "Extream Danger"
#define NWS_EXT_DANGER_TAG_KO_KR "매우 위험"

#define NWS_NORMAL_DESC_EN_US NWS_NORMAL_TAG_EN_US
#define NWS_NORMAL_DESC_KO_KR NWS_NORMAL_TAG_KO_KR
#define NWS_CAUTION_DESC_EN_US "Fatigue possible with prolonged exposure and/or physical activity."
#define NWS_CAUTION_DESC_KO_KR "장시간 노출이나 육체적인 활동 시 피로해질 수 있음."
#define NWS_EXT_CAUTION_DESC_EN_US "Sunstroke, muscle cramps, and/or heat exhaustion possible with prolonged exposure and/or physical activity."
#define NWS_EXT_CAUTION_DESC_KO_KR "장시간 노출이나 신체 활동 시 일사병, 열경련 혹은 열탈진에 걸릴 수 있음."
#define NWS_DANGER_DESC_EN_US "Sunstroke, muscle cramps, and/or heat exhaustion likely. Heat stroke possible with prolonged exposure and/or physical activity."
#define NWS_DANGER_DESC_KO_KR "일사병, 근육 경련 혹은 열탈진에 걸릴 수 있고, 장시간 노출이나 신체 활동 시 열사병에 걸릴 수 있음."
#define NWS_EXT_DANGER_DESC_EN_US "Heat stroke likely."
#define NWS_EXT_DANGER_DESC_KO_KR "열사병에 걸릴 수 있음."

class Weather {
public:
	Weather(NWS_HIL_DESC_LANGUAGE lang = EN_US);
	float getCelsius(float fahrenheit);
	float getFahrenheit(float celsius);
	float getDewPoint(float temperature, float humidity, bool isFahrenheit = false);
	float getDewPoint2(float temperature, float humidity, bool isFahrenheit = false);
	float getDewPointFast(float temperature, float humidity, bool isFahrenheit = false);
	float getHumidity(float temperature, float dewPoint, bool isFahrenheit = false);
	float getHeatIndex(float temperature, float humidity = -1,
		float dewPoint = -1, bool isFahrenheit = false);

	NWS_HEAT_INDEX_LEVEL getHeatIndexLevel(float heatIndex);
	char *getHeatIndexTag(float heatIndex);
	// char *getHeatIndexTag(NWS_HEAT_INDEX_LEVEL level);
	char *getHeatIndexDesc(float heatIndex);
	char *getHeatIndexDesc(NWS_HEAT_INDEX_LEVEL level);

private:
	#define NWS_HIL_INIT(lvl, lang) {lvl ## _TAG_ ## lang, lvl ## _DESC_ ## lang}
	NWS_HIL_DESC_LANGUAGE m_language;
	NWS_HIL_ELEMENT m_hilStr[HIL_LANGUAGE_COUNT][HIL_INDEX_LEVEL_COUNT] = {
		{NWS_HIL_INIT(NWS_NORMAL, EN_US), NWS_HIL_INIT(NWS_CAUTION, EN_US), NWS_HIL_INIT(NWS_EXT_CAUTION, EN_US), NWS_HIL_INIT(NWS_DANGER, EN_US), NWS_HIL_INIT(NWS_EXT_DANGER, EN_US)},
		{NWS_HIL_INIT(NWS_NORMAL, KO_KR), NWS_HIL_INIT(NWS_CAUTION, KO_KR), NWS_HIL_INIT(NWS_EXT_CAUTION, KO_KR), NWS_HIL_INIT(NWS_DANGER, KO_KR), NWS_HIL_INIT(NWS_EXT_DANGER, KO_KR)},
	};
};

#endif // AirQualityIndex_H
