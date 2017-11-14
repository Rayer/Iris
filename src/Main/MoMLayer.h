/**
 * Project Iris
 */


#ifndef _MOMLAYER_H
#define _MOMLAYER_H

#include "Iris_State.h"
#include <string>
#include <boost/uuid/uuid.hpp>


namespace Iris {
    class Context;

    class Loopable;

    class MoMLayer {
    public:

        /**
         * @param delta
         * @param context
         */
        virtual Iris_State update(double delta, Context *context) = 0;

        /**
         * @param module
         */
        virtual boost::uuids::uuid register_module(Loopable *module) = 0;

        /**
         * @param id
         */
        virtual bool remove_module(boost::uuids::uuid id) = 0;

        virtual ~MoMLayer() = default;
    };

}

#endif //_MOMLAYER_H