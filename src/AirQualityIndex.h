/*
	AirQualityIndex.h - Library for getting weather related information.
*/

#ifndef WEATHER_H
#define WEATHER_H

#include <string>

typedef enum _NWS_HIL_DESC_LANGUAGE {
    NWS_HIL_LANG_EN = 0,
    NWS_HIL_LANG_KO = 1,
} NWS_HIL_DESC_LANGUAGE, *NWS_HIL_DESC_LANGUAGE_P;

#define HIL_LANGUAGE_COUNT 2

class Weather {
public:
    Weather(NWS_HIL_DESC_LANGUAGE lang = NWS_HIL_LANG_EN);
    float getCelsius(float fahrenheit);
    float getFahrenheit(float celsius);
    float getDewPoint(float temperature, float humidity, bool isFahrenheit = false);
    float getDewPoint2(float temperature, float humidity, bool isFahrenheit = false);
    float getDewPointFast(float temperature, float humidity, bool isFahrenheit = false);
    float getHumidity(float temperature, float dewPoint, bool isFahrenheit = false);
    float getHeatIndex(float temperature, float humidity = -1,
        float dewPoint = -1, bool isFahrenheit = false);

    String getHeatIndexTag(float heatIndex);
    String getHeatIndexDesc(float heatIndex);
private:
    typedef enum _NWS_HEAT_INDEX_LEVEL {
        NWS_HIL_NORMAL = 0,
        NWS_HIL_CAUTION = 1,
        NWS_HIL_EXT_CAUTION = 2,
        NWS_HIL_DANGER = 3,
        NWS_HIL_EXT_DANGER = 4,
    } NWS_HEAT_INDEX_LEVEL, *NWS_HEAT_INDEX_LEVEL_P;
    #define HIL_INDEX_LEVEL_COUNT 5

    typedef struct _NWS_HIL_EXPLATION {
        NWS_HEAT_INDEX_LEVEL level;
        struct {
            String levelTag;
            String levelDesc;
        } lang[HIL_LANGUAGE_COUNT];
    } NWS_HIL_EXPLATION, *NWS_HIL_EXPLATION_P;

    #define NWS_TAG_NORMAL_EN "Normal"
    #define NWS_TAG_NORMAL_KO "보통"
    #define NWS_TAG_CAUTION_EN "Caution"
    #define NWS_TAG_CAUTION_KO "주의"
    #define NWS_TAG_EXT_CAUTION_EN "Extream Caution"
    #define NWS_TAG_EXT_CAUTION_KO "매우 주의"
    #define NWS_TAG_DANGER_EN "Danger"
    #define NWS_TAG_DANGER_KO "위험"
    #define NWS_TAG_EXT_DANGER_EN "Extream Danger"
    #define NWS_TAG_EXT_DANGER_KO "매우 위험"

    #define NWS_DESC_NORMAL_EN NWS_TAG_NORMAL_EN
    #define NWS_DESC_NORMAL_KO NWS_TAG_NORMAL_KO
    #define NWS_DESC_CAUTION_EN "Fatigue possible with prolonged exposure and/or physical activity."
    #define NWS_DESC_CAUTION_KO "장시간 노출이나 육체적인 활동 시 피로해질 수 있음."
    #define NWS_DESC_EXT_CAUTION_EN "Sunstroke, muscle cramps, and/or heat exhaustion possible with prolonged exposure and/or physical activity."
    #define NWS_DESC_EXT_CAUTION_KO "장시간 노출이나 신체 활동 시 일사병, 열경련 혹은 열탈진에 걸릴 수 있음."
    #define NWS_DESC_DANGER_EN "Sunstroke, muscle cramps, and/or heat exhaustion likely. Heat stroke possible with prolonged exposure and/or physical activity."
    #define NWS_DESC_DANGER_KO "일사병, 근육 경련 혹은 열탈진에 걸릴 수 있고, 장시간 노출이나 신체 활동 시 열사병에 걸릴 수 있음."
    #define NWS_DESC_EXT_DANGER_EN "Heat stroke likely."
    #define NWS_DESC_EXT_DANGER_KO "열사병에 걸릴 수 있음."

    NWS_HIL_EXPLATION m_hilDesc[HIL_INDEX_LEVEL_COUNT] = {
        {NWS_HIL_NORMAL,
            {{String(NWS_TAG_NORMAL_EN), String(NWS_DESC_NORMAL_EN)},
                {String(NWS_TAG_NORMAL_KO), String(NWS_DESC_NORMAL_KO)}}},
        {NWS_HIL_CAUTION,
            {{String(NWS_TAG_CAUTION_EN), String(NWS_DESC_CAUTION_EN)},
                {String(NWS_TAG_CAUTION_KO), String(NWS_DESC_CAUTION_KO)}}},
        {NWS_HIL_EXT_CAUTION,
            {{String(NWS_TAG_EXT_CAUTION_EN), String(NWS_DESC_EXT_CAUTION_EN)},
                {String(NWS_TAG_EXT_CAUTION_KO), String(NWS_DESC_EXT_CAUTION_KO)}}},
        {NWS_HIL_DANGER,
            {{String(NWS_TAG_DANGER_EN), String(NWS_DESC_DANGER_EN)},
                {String(NWS_TAG_DANGER_KO), String(NWS_DESC_DANGER_KO)}}},
        {NWS_HIL_EXT_DANGER,
            {{String(NWS_TAG_EXT_DANGER_EN), String(NWS_DESC_EXT_DANGER_EN)},
                {String(NWS_TAG_EXT_DANGER_KO), String(NWS_DESC_EXT_DANGER_KO)}}}};
    NWS_HIL_DESC_LANGUAGE m_language;
};

#endif // WEATHER_H
