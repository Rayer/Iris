/**
 * Project Iris
 */


#include <string>
#include "Iris_State.h"
#include "Context.h"
#include "Loopable.h"
#include "MoManager.h"
#include <boost/uuid/uuid_generators.hpp>

/**
 * MoManager implementation
 */
Iris_State Iris::MoManager::update(double delta, Context *context) {
    std::for_each(this->module_list.begin(), this->module_list.end(), [&](Loopable* loopable){ loopable->update(delta, context); });
    return context->isRunning() ? Iris_State::RUNNING : Iris_State::STOP;
}

boost::uuids::uuid Iris::MoManager::register_module(Loopable *module) {
    boost::uuids::random_generator gen;
    boost::uuids::uuid tag = gen();
    module->set_tag(tag);
    module_list.push_back(module);
    return tag;
}

bool Iris::MoManager::remove_module(boost::uuids::uuid id) {
    for (Loopable *loopable : module_list) {
        if (loopable->tag() == id) {
            module_list.remove(loopable);
            return true;
        }
    }
    return false;
}
