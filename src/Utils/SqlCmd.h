//
// Created by Rayer Tung on 2018/7/19.
//

#ifndef IRIS_SQLCMD_H
#define IRIS_SQLCMD_H

#pragma once

#include <sstream>
#include <list>
#include <map>

//Forward Declaration
namespace where_clause {
    class Eq;

    class And;

    class Exp;
}

enum Order {
    ASCENDING,
    DESCENDING
};

//Not intent to be used by user. It is abstract class of all SQL Commands.
class SqlCmd {
public:
    /**
    Generate SQL String.
    \return Generated SQL String
    */
    virtual std::string generate() = 0;
    //virtual ADODB::_RecordsetPtr execute(ADODB::_ConnectionPtr ptr) = 0;

    virtual ~SqlCmd() = default;
};

/**
This class provides an easier way to access SQL DB. It is a Builder pattern based class.

```
QueryResult result = SqlQuery("TABLE_NAME").addQuery("COLUMN1").addQuery("COLUMN2").where(Eq("c_system_id", "awsrayer") & Eq("c_client_layout", "1272028")).query(m_OraCnn);
```

\sa QueryResult
*/
class SqlQuery : public SqlCmd {
    std::string m_tablename;
    std::list<std::string> m_queryItemList;
    std::string m_whereString;
    std::string m_orderString;

public:
    /**
    Main builder for Query
    \param table Table Name
    */
    SqlQuery(const std::string &table);

    ~SqlQuery(void) override;

    /**
    Add a query column. It works like SELECT "THIS" from "TABLE NAME"
    \param query Column name added to query list
    \return Builder pattern self reference
    */
    SqlQuery &addQuery(const std::string &query);

    /**
    Where clause. This can consume "text" version of where clause, like "A='01' AND B='02'" as raw stream
    \param condition Where-clause.
    \return Builder pattern self reference
    */
    SqlQuery &where(const std::string &condition);

    /**
    Where clause, but use where_clause utilities.
    For example, .where("A='01' AND B='02'") is equal to .where(Eq("A", "01") & EQ("B", "02"))
    \param exp where_clause utilities classes.
    \return Builder pattern self reference
    \sa where_clause
    */
    SqlQuery &where(const where_clause::Exp &exp);

    /**
     Sorting Order, it can provide ordering by specified column.
     \param column Column should be sorted by.
     \param order ASCENDING(default) and DESCENDING : as literal
     \return Builder pattern self reference
     */
    SqlQuery &orderBy(const std::string &column, Order order = ASCENDING);


    /**
    Generate SQL String.
    \return Generated SQL String
    */
    std::string generate() override;

};

/**
SqlUpdate is another helper for executing "UPDATE" command of SQL, it is a Builder Pattern, too.

<code>

SqlUpdate("TABLE_NAME").setValue("COLUMN1_INT", "123").setValue("COLUMN2_STR", "Hello").execute(m_pOraCnn);

</code>
*/
class SqlUpdate : public SqlCmd {
    std::string m_tablename;
    //std::map<std::string, std::string> m_keyValueMap;
    //TODO: Support multiple set value, if possible. Currently only support single key-value pair
    std::pair<std::string, std::string> m_kvPair;
    std::string m_whereString;

public:
    /**
    Main Builder for Update
    \param tablename Target table name
    */
    SqlUpdate(const std::string &tablename);

    ~SqlUpdate(void) override;

    /**
    Set a value to a column.
    \param key
    \param value Value use to set to the column. Currently only string is supported because all use cases use string as value.
    */
    SqlUpdate &setValue(const std::string &key, const std::string &value);

    /**
    Where clause. This can consume "text" version of where clause, like "A='01' AND B='02'" as raw stream
    \param condition Where-clause.
    \return Builder pattern self reference
    */
    SqlUpdate &where(const std::string &condition);

    /**
    Where clause, but use where_clause utilities.
    For example, .where("A='01' AND B='02'") is equal to .where(Eq("A", "01") & EQ("B", "02"))
    \param exp where_clause utilities classes.
    \return Builder pattern self reference
    \sa where_clause
    */
    SqlUpdate &where(const where_clause::Exp &exp);

    /**
    Generate SQL String.
    \return Generated SQL String
    */
    std::string generate() override;

};

/**
This is a helper class for generating where_clause.

For example, we usually use this to build a `where-clause`
```
std::stringstream where_clause;
where_clause << ORA_A::COLUMN_NAME << "=" << someValue << " AND "
	<< ORA_A::COLUMN_NAME2 << "=" << someValue2 << " AND "
	<< ORA_A::COLUMN_NAME3 << "=" << someValue3;

QueryResult result = SqlQuery(ORA_A::TABLE_NAME)
	.addQuery(ORA_A::COLUMN_OTHER)
	.where(where_clause.str())
	.query(m_pOraCnn);
```

It can be samplify to
```
QueryResult result = SqlQuery(ORA_A::TABLE_NAME)
	.addQuery(ORA_A::COLUMN_OTHER)
	.where(And(And(Eq(ORA_A::COLUMN_NAME, someValue), Eq(ORA_A::COLUMN_NAME2, someValue2)), Eq(ORA_A::COLUMN_NAME3, someValue3)))
	.query(m_pOraCnn);
```
`And` might still be not readable when there is a lot of And clause...

Even furthermore...
```
QueryResult result = SqlQuery(ORA_A::TABLE_NAME)
	.addQuery(ORA_A::COLUMN_OTHER)
	.where(Eq(ORA_A::COLUMN_NAME, someValue) & Eq(ORA_A::COLUMN_NAME2, someValue2) & Eq(ORA_A::COLUMN_NAME3, someValue3))
	.query(m_pOraCnn);
```

where_clause makes adding `where()` much more easier then before.
*/
namespace where_clause {
    class Exp {
    public :
        virtual ~Exp() = default;

        virtual std::string str() const { return ""; };

        /**
        This operator uses in two where_clause::Exp. It represent "AND"
        \sa And
        */
        And operator&(const Exp &exp) const;
    };

    /**
    Express "like", Like
    */
    class Like : public Exp {
        std::string m_var;
        std::string m_val;
    public :
        ~Like() = default;

        Like(const std::string &var, const std::string &val);

        std::string str() const;
    };

    /**
    Express "=", Equal
    */
    class Eq : public Exp {
        std::string m_var;
        std::string m_val;
    public :
        ~Eq() override = default;

        Eq(const std::string &var, const std::string &val);

        Eq(const std::string &var, int val);

        Eq(const std::string &var, double val);

        std::string str() const override;
    };

    /**
    Express "And", usually we can use operator& instead.
    */
    class And : public Exp {
        const Exp &m_lhs;
        const Exp &m_rhs;
    public:
        And(const Exp &, const Exp &);

        //And(const std::list<Exp>& exp);
        std::string str() const override;
    };

}


#endif //IRIS_SQLCMD_H
