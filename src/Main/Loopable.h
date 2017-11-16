/**
 * Project Iris
 */


#ifndef _LOOPABLE_H
#define _LOOPABLE_H

#include "IDModule.h"

namespace Iris {
    class Context;

    class Loopable : public IDModule {
    public:

        /**
         * @param delta
         */
        virtual void update(double delta, Context* context) = 0;

        virtual std::string name() = 0;

        virtual ~Loopable() = default;
    };
}


#endif //_LOOPABLE_H