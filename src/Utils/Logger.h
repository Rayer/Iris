//
// Created by Rayer on 24/10/2017.
//

#ifndef IRIS_LOGGER_H
#define IRIS_LOGGER_H

#include <boost/log/trivial.hpp>

namespace Iris {

    class Logger {
    public:
        Logger() {
            BOOST_LOG_TRIVIAL() << "Hello!";
        }
        void fatal(boost::log::formatting_ostream& );
        void error();
        void warning();
        void info();
        void debug();
        void trace();
    };

}


#endif //IRIS_LOGGER_H
