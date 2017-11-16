/**
 * Project Iris
 */


#ifndef _MOMANAGER_H
#define _MOMANAGER_H

#include <list>
#include <boost/uuid/uuid.hpp>
#include "MoMLayer.h"
#include "Loopable.h"

namespace Iris {
    class MoManager : public MoMLayer {
    private:
        std::list<Loopable *> module_list;
    public:
        Iris_State update(double delta, Context *context) override;

        boost::uuids::uuid register_module(Loopable *module) override;

        bool remove_module(boost::uuids::uuid id) override;
    };
}


#endif //_MOMANAGER_H