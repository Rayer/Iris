//
// Created by Rayer Tung on 14/11/2017.
//

#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include <Main/Loopable.h>
#include <Main/MoMLayer.h>
#include <Main/MoManager.h>
#include <boost/uuid/uuid_io.hpp>
#include <boost/uuid/uuid_generators.hpp>

using namespace Iris;

int update_count = 0;

class TemplateModule : public Loopable {
    boost::uuids::uuid m_tag;
    std::string m_name;
public:
    TemplateModule(std::string name) : m_name(name), m_tag(boost::uuids::nil_uuid()) {
    }

    void update(double delta, Context *context) override {
        update_count++;
    }

    void set_tag(boost::uuids::uuid uuid) override {
        m_tag = uuid;
    }

    boost::uuids::uuid tag() override {
        return m_tag;
    }

    std::string name() override {
        return m_name;
    }
};


TEST(LoopSystemTest, Register_UUID_Test) {
    Loopable *clazz1, *clazz2;
    clazz1 = new TemplateModule("TestModule1");
    clazz2 = new TemplateModule("TestModule2");

    EXPECT_EQ(clazz1->tag(), boost::uuids::nil_uuid());
    EXPECT_EQ(clazz2->tag(), boost::uuids::nil_uuid());

    MoMLayer *ml = new MoManager();
    ml->register_module(clazz1);
    ml->register_module(clazz2);

    EXPECT_NE(clazz1->tag(), boost::uuids::nil_uuid());
    EXPECT_NE(clazz2->tag(), boost::uuids::nil_uuid());
    EXPECT_NE(clazz1->tag(), clazz2->tag());
    delete ml;
    delete clazz1;
    delete clazz2;
}

TEST(LoopSystemTest, Reg_Remove_Module_Test) {
    Loopable *clazz1, *clazz2;
    clazz1 = new TemplateModule("TestModule1");
    clazz2 = new TemplateModule("TestModule2");

    update_count = 0;

    typedef boost::uuids::uuid UUID;

    MoMLayer *ml = new MoManager();
    UUID u1 = ml->register_module(clazz1);
    UUID u2 = ml->register_module(clazz2);

    ml->update(0, nullptr);

    EXPECT_EQ(update_count, 2);

    ml->remove_module(u2);
    ml->update(0, nullptr);

    EXPECT_EQ(update_count, 3);

    ml->remove_module(u1);
    ml->update(0, nullptr);
    EXPECT_EQ(update_count, 3);

    delete ml;
    delete clazz1;
    delete clazz2;
}
