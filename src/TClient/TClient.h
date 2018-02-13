//
// Created by Rayer on 13/02/2018.
//

#ifndef IRIS_TCLIENT_H
#define IRIS_TCLIENT_H

#include <memory>

namespace Iris {

    class Context;
    class MoMLayer;
    class TClient {
    private:
        static const int UPDATE_SPEED = 500;
        std::shared_ptr<Context> context;
        std::shared_ptr<MoMLayer> modules;

        void print_status();
        std::string fetch_next_command();
        void parse_next_command(const std::string);
    public:
        TClient();
        void start();
    };
}




#endif //IRIS_TCLIENT_H
