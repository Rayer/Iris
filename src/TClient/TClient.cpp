//
// Created by Rayer on 13/02/2018.
//

#include <string>
#include "TClient.h"
#include "Main/Context.h"
#include "Main/MoManager.h"
#include <iostream>


Iris::TClient::TClient() {
    context = std::make_shared<Context>();
    modules = std::make_shared<MoManager>();
    
}

void Iris::TClient::start() {
    context->setRunning(true);
    while(context->isRunning()) {
        this->print_status();
        std::string next = this->fetch_next_command();
        this->parse_next_command(next);
        modules->update(UPDATE_SPEED, context.get());
    }
}

void Iris::TClient::print_status() {
    std::cout << "This is current status!" << std::endl;
}

std::string Iris::TClient::fetch_next_command() {
    std::string buffer;
    std::cout << "Input command : " << std::endl;
    getline(std::cin, buffer);
    return buffer;
}

void Iris::TClient::parse_next_command(const std::string& cmd) {
    std::cout << "Next command is : " << cmd << std::endl;
}



