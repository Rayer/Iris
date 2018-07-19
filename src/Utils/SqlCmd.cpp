#include "SqlCmd.h"


SqlQuery::SqlQuery(const std::string &table) {
    m_tablename = table;
}

SqlQuery::~SqlQuery(void) {
}

SqlQuery &SqlQuery::addQuery(const std::string &query) {
    m_queryItemList.push_back(query);
    return *this;
}

std::string SqlQuery::generate() {
    std::stringstream buffer;
    buffer << "SELECT ";
    for (std::list<std::string>::iterator iter = m_queryItemList.begin(); iter != m_queryItemList.end(); ++iter) {
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

SqlUpdate::~SqlUpdate() {
    //Nothing to do?
}

SqlUpdate &SqlUpdate::setValue(const std::string &key, const std::string &value) {
    m_kvPair = std::make_pair(key, value);
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
    buffer << "UPDATE " << m_tablename << " SET " << m_kvPair.first << "='" << m_kvPair.second << "' WHERE "
           << m_whereString;
    buffer << ";";
    return buffer.str();
}


where_clause::And where_clause::Exp::operator&(const Exp &exp) const {
    return And(*this, exp);
}


where_clause::Eq::Eq(const std::string &var, const std::string &val)
        : m_var(var), m_val(val) {};

//This implementation requires C++11 which is not yet supported by current build toolchain
where_clause::Eq::Eq(const std::string &var, const int val)
        : m_var(var), m_val(std::to_string((long long) val)) {};

where_clause::Eq::Eq(const std::string &var, const double val)
        : m_var(var), m_val(std::to_string((long double) val)) {};

/*
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
 */

std::string where_clause::Eq::str() const {
    if (strcmp(m_val.c_str(), "  ") == 0 || m_val.empty()) {
        return m_var + "is null";
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
