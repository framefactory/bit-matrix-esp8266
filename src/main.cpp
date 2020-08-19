/**
 * ESP/Arduino Clock Application
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#include "ClockApp.h"

ff::ClockApp app;

void setup()
{
    app.setup();
}

void loop()
{
    app.loop();
}