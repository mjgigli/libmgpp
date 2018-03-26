#include <gtest/gtest.h>
#include <mgpp/signals.hpp>
#include <string>

enum TestEvents {
   INT_EVENT,
   STRING_EVENT
};

class IntEvent: public mgpp::signals::Event {
   public:
      IntEvent(int arg) :
         mgpp::signals::Event(INT_EVENT),
         arg_(arg) {}
      int arg() const { return arg_; }

   private:
      int arg_;
};

class StringEvent: public mgpp::signals::Event {
   public:
      StringEvent(std::string arg) :
         mgpp::signals::Event(STRING_EVENT),
         arg_(arg) {}
      const std::string& arg() const { return arg_; }

   private:
      std::string arg_;
};

void int_cb(const mgpp::signals::Event& event)
{
   const IntEvent& int_evt = static_cast<const IntEvent&>(event);
   EXPECT_EQ(int_evt.id(), int_evt.arg());
}

void string_cb(const mgpp::signals::Event& event)
{
   const StringEvent& str_evt = static_cast<const StringEvent&>(event);
   EXPECT_EQ("foo", str_evt.arg());
}

class EventDispatcherTest: public ::testing::Test {
   protected:
      virtual void SetUp() {
         int_conn_ = mgpp::signals::subscribe(INT_EVENT, &int_cb);
         string_conn_ = mgpp::signals::subscribe(STRING_EVENT, &string_cb);
      }
      virtual void TearDown() {
         mgpp::signals::unsubscribe_all();
      }

      mgpp::signals::Connection int_conn_;
      mgpp::signals::Connection string_conn_;
};

TEST(EventDispatcher, Defaults)
{
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(0, mgpp::signals::num_slots(STRING_EVENT));
   EXPECT_EQ(0, mgpp::signals::num_slots(100));
}

TEST_F(EventDispatcherTest, Subscribe)
{
   EXPECT_EQ(1, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(1, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, Unsubscribe)
{
   mgpp::signals::unsubscribe(INT_EVENT, int_conn_);
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(1, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, UnsubscribeAll)
{
   mgpp::signals::unsubscribe_all();
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(0, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, UnsubscribeAllSignal)
{
   mgpp::signals::unsubscribe_all(INT_EVENT);
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(1, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, Publish)
{
   IntEvent int_evt = IntEvent(0);
   mgpp::signals::publish(int_evt);
   StringEvent str_evt = StringEvent("foo");
   mgpp::signals::publish(str_evt);
}

class Foo {
   public:
      void int_cb(const mgpp::signals::Event& event)
      {
         const IntEvent& int_evt = static_cast<const IntEvent&>(event);
         EXPECT_EQ(int_evt.id(), int_evt.arg());
      }

      void string_cb(const mgpp::signals::Event& event)
      {
         const StringEvent& str_evt = static_cast<const StringEvent&>(event);
         EXPECT_EQ("foo", str_evt.arg());
      }
};

class EventMemberDispatcherTest: public ::testing::Test {
   public:
      EventMemberDispatcherTest() : foo_(), int_conn_(), string_conn_() {}

   protected:
      virtual void SetUp() {
         int_conn_ = mgpp::signals::subscribe(INT_EVENT, &Foo::int_cb, foo_);
         string_conn_ = mgpp::signals::subscribe(STRING_EVENT, &Foo::string_cb, foo_);
      }

      virtual void TearDown() {
         mgpp::signals::unsubscribe_all();
      }

      Foo foo_;
      mgpp::signals::Connection int_conn_;
      mgpp::signals::Connection string_conn_;
};

TEST_F(EventMemberDispatcherTest, Subscribe)
{
   EXPECT_EQ(1, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(1, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, Unsubscribe)
{
   mgpp::signals::unsubscribe(INT_EVENT, int_conn_);
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(1, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, UnsubscribeAll)
{
   mgpp::signals::unsubscribe_all();
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(0, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, UnsubscribeAllSignal)
{
   mgpp::signals::unsubscribe_all(INT_EVENT);
   EXPECT_EQ(0, mgpp::signals::num_slots(INT_EVENT));
   EXPECT_EQ(1, mgpp::signals::num_slots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, Publish)
{
   IntEvent int_evt = IntEvent(0);
   mgpp::signals::publish(int_evt);
   StringEvent str_evt = StringEvent("foo");
   mgpp::signals::publish(str_evt);
}
