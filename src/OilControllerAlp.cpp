/// @file OilControllerAlp.cpp
#include "JsonDeserializeAlp.h"
#include "OilObject.h"
#include "OilControllerAlp.h"

OilControllerAlp::OilControllerAlp(OilObject oilValue, JsonDeserializeAlp jsonDeserialize) : _oilValue(oilValue), _jsonDeserialize(jsonDeserialize)
{
    pinMode(_oilValue.getPin(), OUTPUT);
    analogWrite(_oilValue.getPin(), _oilValue.getCurrentStateOil());
}

void OilControllerAlp::update(const String &json)
{
    bool shouldSendSignalToPin = canSendSignalToPin(json);

    if (shouldSendSignalToPin)
    {
        updateOilState(json);
    }
    else
    {
        resetPinState();
    }
}

void OilControllerAlp::resetPinState()
{
    analogWrite(_oilValue.getPin(), _oilValue.getDefaultInitialValue());
    _oilValue.setCurrentStateOil(_oilValue.getDefaultInitialValue());
}

bool OilControllerAlp::canSendSignalToPin(const String &json)
{
    bool electricOn = _jsonDeserialize.getBoolValue(json, "electricOn");
    bool engineOn = _jsonDeserialize.getBoolValue(json, "engineOn");

    return electricOn || engineOn;
}

void OilControllerAlp::updateOilState(const String &json)
{
    float currentOil = _jsonDeserialize.getFloatValue(json, _oilValue.getJsonKey());
    

    if (currentOil > 0)
    {
        int pwm = map(currentOil, _oilValue.getOilCapacity(), _oilValue.getOilMinCapacity(), _oilValue.getMinPWM(), _oilValue.getMaxPWM());

        if (_oilValue.getCurrentStateOil() != pwm)
        {
            analogWrite(_oilValue.getPin(), pwm);
            _oilValue.setCurrentStateOil(pwm);
        }
    }
   
}
