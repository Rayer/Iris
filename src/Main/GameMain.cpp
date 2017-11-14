/**
 * Project Iris
 */


#include "GameMain.h"
#include "Context.h"
#include "MoMLayer.h"
#include <chrono>
#include <iostream>

using namespace Iris;

/**
 * GameMain implementation
 */


/**
 * @param context
 * @return void
 */
using namespace Iris;

void GameMain::loop(Context *context) {
    typedef std::chrono::high_resolution_clock time;
    typedef std::chrono::milliseconds ms;

    //initialize
    auto timer = time::now();

    while (context->isRunning()) {

        double delta = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(
                time::now() - timer).count();
        mom_layer->update(delta, context);
        timer = time::now();
    }

}