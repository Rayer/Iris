/**
 * Project Iris
 */


#include "Context.h"

using namespace Iris;
/**
 * Context implementation
 */
bool Context::isRunning() const {
    return running;
}

void Context::setRunning(bool running) {
    Context::running = running;
}
