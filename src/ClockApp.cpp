/**
 * ESP/Arduino Clock Application
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "ClockApp.h"
#include "effect/examples/Clock22.h"
#include "fonts/Fonts.h"

F_USE_NAMESPACE

ClockApp::ClockApp() :
    _universe(CLOCK_PIN, LOAD_PIN, DELAY),
    _matrices(_universe.createChain(DATA_PIN)->createMatrices(4)),
    _canvas(32, 8),
    _comp(32, 8)
{
    _canvas.addMatrices(_matrices, 0, 0, 8, 0);
    _comp.addEffectLayer(new ff::Clock22());
}

void ClockApp::setup()
{
    Application::setup();
 
    _universe.setBrightness(3);
    _universe.initialize();

    _canvas.drawText("BIT", &ff::Fonts::font04B24, 3, 0, 4);
    _canvas.drawText("MAT", &ff::Fonts::font04B24, 19, -1, 4);
    _canvas.update();
    _universe.writeDisplay();

    if (!_env.read()) {
       return;
    }

    // connect to Wifi
    const char* ssid = _env.getCStr("WIFI_SSID");
    const char* password = _env.getCStr("WIFI_PASSWORD");

    if (!ssid || !password || strlen(ssid) == 0 || strlen(password) == 0) {
        Serial.println("Failed to read SSID/password from .env configuration file.");
    }
    else {
        connectWifi(ssid, password);

        // fetch time
        float offset = _env.getFloat("TIMEZONE_OFFSET");
        float dst = _env.getFloat("TIMEZONE_DST");
        _comp.fetchRealTime(offset, dst);
    }

    //_server.initialize(&_universe);

    _canvas.clear();

}

void ClockApp::loop()
{
    static bool isOn = false;
    //_server.handleClient();

    if (_comp.render()) {
        _canvas.blit(_comp);

        //isOn = !isOn;
        //_canvas.set(0, 0, isOn);

        _canvas.update();
        _universe.writeDisplay();
    }
}
