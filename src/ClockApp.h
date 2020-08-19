/**
 * ESP/Arduino Clock Application
 * Copyright 2020 Frame Factory GmbH, Ralph Wiedemeier
 * License: MIT
 */

#ifndef _ESP_CLOCK_CLOCKAPP_H
#define _ESP_CLOCK_CLOCKAPP_H

#include "app.h"

#include "matrix/MAX7219Universe.h"
#include "matrix/MAX7219Chain.h"
#include "matrix/MAX7219Matrix.h"
#include "matrix/Canvas.h"
#include "effect/Composition.h"
#include "core/Application.h"
#include "core/Environment.h"

F_BEGIN_NAMESPACE

class ClockApp : public Application
{
public:
    ClockApp();

    virtual void setup() override;
    virtual void loop() override;

private:
    static const int CLOCK_PIN = 12;
    static const int LOAD_PIN = 14;
    static const int DATA_PIN = 0;
    static const int DELAY = 1;

    Environment _env;

    MAX7219Universe _universe;
    MAX7219Matrices _matrices;
    Canvas _canvas;
    Composition _comp;
};

F_END_NAMESPACE

#endif // _ESP_CLOCK_CLOCKAPP_H