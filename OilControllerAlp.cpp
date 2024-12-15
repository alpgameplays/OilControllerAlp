/// @file OilControllerAlp.cpp
#include "JsonDeserializeAlp.h"
#include "OilObject.h"
#include "OilControllerAlp.h"

OilControllerAlp::OilControllerAlp(OilObject oilTemp, JsonDeserializeAlp jsonDeserialize) : _oilValue(oilTemp), _jsonDeserialize(jsonDeserialize)
{
    pinMode(_oilValue.getPin(), OUTPUT);
    analogWrite(_oilValue.getPin(), _oilValue.getCurrentStateFuel());
}

void OilControllerAlp::update(const String &json)
{
    bool shouldSendSignalToPin = canSendSignalToPin(json);

    if (shouldSendSignalToPin)
    {
        updateFuelState(json);
    }
    else
    {
        resetPinState();
    }
}

void OilControllerAlp::resetPinState()
{
    analogWrite(_oilValue.getPin(), _oilValue.getDefaultInitialValue());
    _oilValue.setCurrentStateFuel(_oilValue.getDefaultInitialValue());
}

bool OilControllerAlp::canSendSignalToPin(const String &json)
{
    bool electricOn = _jsonDeserialize.getBoolValue(json, "electricOn");
    bool engineOn = _jsonDeserialize.getBoolValue(json, "engineOn");

    return electricOn || engineOn;
}

void OilControllerAlp::updateFuelState(const String &json)
{
    float currentOil = _jsonDeserialize.getFloatValue(json, _oilValue.getJsonKey());
    

    if (currentOil > 0)
    {
        float percentValue = (currentOil / _oilValue.getOilCapacity()) * 100.0;
        int pwm = map(percentValue, 100, 0, _oilValue.getMinPWM(), _oilValue.getMaxPWM());

        if (_oilValue.getCurrentStateFuel() != pwm)
        {
            analogWrite(_oilValue.getPin(), pwm);
            _oilValue.setCurrentStateFuel(pwm);
        }
    }
    else
    {
        resetPinState();
    }
}
