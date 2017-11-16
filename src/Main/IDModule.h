/**
 * Project Iris
 */


#ifndef _IDMODULE_H
#define _IDMODULE_H

#include <boost/uuid/uuid.hpp>

namespace Iris {
    class IDModule {
    public:

        /**
         * @param tag
         */
        virtual void set_tag(boost::uuids::uuid tag) = 0;

        virtual boost::uuids::uuid tag() = 0;
    };
}


#endif //_IDMODULE_H