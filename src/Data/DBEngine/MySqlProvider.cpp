//
// Created by CORP\rayer on 10/31/18.
//

#include "MySqlProvider.h"
#include <mysql++/query.h>

void Iris::MySqlProvider::connect(const std::string &ip, const std::string &user, const std::string &pass,
                                  const std::string &database) {
    conn = new mysqlpp::Connection();
    bool ret = conn->connect(database.c_str(), ip.c_str(), user.c_str(), pass.c_str());
    //bool ret = conn->connect("Iris", "node.rayer.idv.tw", "iris", "iris");

    std::cout << "Database init : " << conn->error() << std::endl;
}

std::shared_ptr<Iris::IQueryResult> Iris::MySqlProvider::query(const std::string &sql) {
    mysqlpp::Query query = conn->query(sql.c_str());
    return std::make_shared<Iris::MySqlQueryResult>(query.store());
}

std::shared_ptr<Iris::IExecuteResult> Iris::MySqlProvider::execute(const std::string &sql) {
    return std::shared_ptr<IExecuteResult>();
}

void Iris::MySqlProvider::cleanup() {
    delete conn;
}

std::string Iris::MySqlQueryResult::get_column(const std::string &column_name) {
    size_t index = (*pos).field_num(column_name.c_str());
    return (*pos).at(index).c_str();
}

unsigned long Iris::MySqlQueryResult::column_count() {
    return (unsigned long)queryResult.num_fields();
}

unsigned long Iris::MySqlQueryResult::row_count() {
    return queryResult.num_rows();
}

bool Iris::MySqlQueryResult::next() {
    pos++;
    if(pos != queryResult.cend()) return true;
    pos--;
    return false;
}

bool Iris::MySqlQueryResult::prev() {
    if(pos == queryResult.cbegin()) return false;
    pos--;
    return true;
}

bool Iris::MySqlQueryResult::go_to_index(int index) {
    if(index > queryResult.size()) return false;
    pos = queryResult.cbegin() + index;
    return true;
}

std::string Iris::MySqlQueryResult::error() {
    return std::string();
}

Iris::MySqlQueryResult::~MySqlQueryResult() {

}

Iris::MySqlQueryResult::MySqlQueryResult(mysqlpp::StoreQueryResult result) : IQueryResult(), queryResult(result) {
    pos = queryResult.begin();
}

