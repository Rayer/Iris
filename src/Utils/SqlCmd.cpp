#include "SqlCmd.h"
#include <boost/algorithm/string.hpp>


SqlQuery::SqlQuery(const std::string &table) {
    m_tablename = table;
}

SqlQuery &SqlQuery::addQuery(const std::string &query) {
    m_queryItemList.push_back(query);
    return *this;
}

std::string SqlQuery::generate() {
    std::stringstream buffer;
    buffer << "SELECT ";
    for (auto iter = m_queryItemList.begin(); iter != m_queryItemList.end(); ++iter) {
        if (iter != m_queryItemList.begin()) {
            buffer << "," << *iter;
        } else {
            buffer << *iter;
        }
    }

    buffer << " FROM " << m_tablename;
    if (!m_whereString.empty())
        buffer << " WHERE " << m_whereString;

    if (!m_orderString.empty())
        buffer << " " << m_orderString;

    buffer << ";";

    return buffer.str();
}

SqlQuery &SqlQuery::where(const std::string &condition) {
    m_whereString = condition;
    return *this;
}

SqlQuery &SqlQuery::where(const where_clause::Exp &exp) {
    return where(exp.str());
}


SqlUpdate::SqlUpdate(const std::string &tablename) {
    m_tablename = tablename;
}


SqlUpdate &SqlUpdate::setValue(const std::string &key, const std::string &value) {
    m_kvList.emplace_back(key, value);
    return *this;
}

SqlUpdate &SqlUpdate::setValue(const std::string &key, int value) {
    m_kvList.emplace_back(key, std::to_string(value));
    return *this;
}

SqlUpdate &SqlUpdate::setValue(const std::string &key, double value) {
    std::stringstream buf;
    buf << value;
    m_kvList.emplace_back(key, buf.str());
    return *this;
}

SqlUpdate &SqlUpdate::where(const std::string &where_clouse) {
    m_whereString = where_clouse;
    return *this;
}

SqlUpdate &SqlUpdate::where(const where_clause::Exp &exp) {
    return where(exp.str());
}


std::string SqlUpdate::generate() {
    std::stringstream buffer;
    //UPDATE TABLE_NAME SET KEY = VALUE WHERE (WHERE_CLOUSE)
    std::stringstream set_value_buf;

    std::list<std::string> set_result;
//    std::transform(m_kvList.begin(), m_kvList.end(), set_result.begin(), [](const KVPair& kvPair)->std::string {
//        return kvPair.first + "='" + kvPair.second + "'";
//    });

    for (KVPair kv : m_kvList) {
        set_result.push_back(kv.first + "='" + kv.second + "'");
    }

    std::string set_string = boost::join(set_result, ",");

    buffer << "UPDATE " << m_tablename << " SET " << set_string;
    if (!m_whereString.empty()) buffer << " WHERE " << m_whereString;
    buffer << ";";
    return buffer.str();
}


SqlInsert::SqlInsert(const std::string &tablename) : m_tablename(tablename) {
}

SqlInsert &SqlInsert::insertValue(const std::string &key, const std::string &value) {
    m_kvList.emplace_back(key, value);
    return *this;
}

SqlInsert &SqlInsert::insertValue(const std::string &key, int value) {
    m_kvList.emplace_back(key, std::to_string(value));
    return *this;
}

SqlInsert &SqlInsert::insertValue(const std::string &key, double value) {
    std::stringstream buf;
    buf << value;
    m_kvList.emplace_back(key, buf.str());
    return *this;
}

std::string SqlInsert::generate() {
    std::stringstream buf;
    std::list<std::string> columns;
    std::list<std::string> values;

    for (KVPair kv : m_kvList) {
        columns.push_back(kv.first);
        values.push_back(kv.second);
    }

    buf << "INSERT INTO " << m_tablename << " (" << boost::join(columns, ",") << ") VALUES ('"
        << boost::join(values, "','") << "');";
    return buf.str();
}

where_clause::And where_clause::Exp::operator&(const Exp &exp) const {
    return And(*this, exp);
}


where_clause::Eq::Eq(const std::string &var, const std::string &val)
        : m_var(var), m_val(val) {};

/*
//This implementation requires C++11 which is not yet supported by current build toolchain
where_clause::Eq::Eq(const std::string &var, const int val)
        : m_var(var), m_val(std::to_string((long long) val)) {};

where_clause::Eq::Eq(const std::string &var, const double val)
        : m_var(var), m_val(std::to_string((long double) val)) {};
*/

where_clause::Eq::Eq(const std::string& var, const int val)
        : m_var(var){
    std::stringstream buf;
    buf << val;
    m_val = buf.str();
};

where_clause::Eq::Eq(const std::string& var, const double val)
        : m_var(var){
    std::stringstream buf;
    buf << val;
    m_val = buf.str();
};


std::string where_clause::Eq::str() const {

    //trim_copy costs, so m_val.empty() first.
    if (m_val.empty() || boost::trim_copy(m_val).empty()) {
        return m_var + " is null";
    } else {
        return m_var + "='" + m_val + "'";
    }
}

where_clause::Like::Like(const std::string &var, const std::string &val)
        : m_var(var), m_val(val) {};

std::string where_clause::Like::str() const {
    return m_var + " Like '" + m_val + "'";
}

where_clause::And::And(const Exp &lhs, const Exp &rhs) : m_lhs(lhs), m_rhs(rhs) {
}

std::string where_clause::And::str() const {
    std::stringstream output;
    output << m_lhs.str() << " AND " << m_rhs.str();
    return output.str();
}

SqlQuery &SqlQuery::orderBy(const std::string &column, Order order) {
    m_orderString = "ORDER BY " + column + (order == ASCENDING ? "" : " DESC");
    return *this;
}

where_clause::Not::Not(const std::string &var, const std::string &val) : m_var(var), m_val(val) {
}

where_clause::Not::Not(const std::string &var, int val) : m_var(var), m_val(std::to_string(val)) {
}

where_clause::Not::Not(const std::string &var, double val) : m_var(var) {
    std::stringstream buf;
    buf << val;
    m_val = buf.str();
}

std::string where_clause::Not::str() const {
    //trim_copy costs, so m_val.empty() first.
    if (m_val.empty() || boost::trim_copy(m_val).empty()) {
        return m_var + " is not null";
    } else {
        return m_var + "<>'" + m_val + "'";
    }
}


