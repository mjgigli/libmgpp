/*
 * Copyright (c) 2018 Matt Gigli
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to
 * deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE
 * SOFTWARE.
 */

#include <gtest/gtest.h>

#include <string>

#include <mgpp/signals.hpp>

enum TestEvents { INT_EVENT, STRING_EVENT };

class IntEvent : public mgpp::signals::Event {
 public:
  explicit IntEvent(int arg) : mgpp::signals::Event(INT_EVENT), arg_(arg) {}
  int arg() const { return arg_; }

 private:
  int arg_;
};

class StringEvent : public mgpp::signals::Event {
 public:
  explicit StringEvent(std::string arg)
      : mgpp::signals::Event(STRING_EVENT), arg_(arg) {}
  const std::string &arg() const { return arg_; }

 private:
  std::string arg_;
};

void IntCb(mgpp::signals::EventConstPtr event) {
  const IntEvent &int_evt = static_cast<const IntEvent &>(*event);
  EXPECT_EQ(int_evt.id(), int_evt.arg());
}

void StringCb(mgpp::signals::EventConstPtr event) {
  const StringEvent &str_evt = static_cast<const StringEvent &>(*event);
  EXPECT_EQ("foo", str_evt.arg());
}

class EventDispatcherTest : public ::testing::Test {
 protected:
  virtual void SetUp() {
    int_conn_ = mgpp::signals::Subscribe(INT_EVENT, &IntCb);
    string_conn_ = mgpp::signals::Subscribe(STRING_EVENT, &StringCb);
  }
  virtual void TearDown() { mgpp::signals::UnsubscribeAll(); }

  mgpp::signals::Connection int_conn_;
  mgpp::signals::Connection string_conn_;
};

TEST(EventDispatcher, Defaults) {
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(0, mgpp::signals::NumSlots(STRING_EVENT));
  EXPECT_EQ(0, mgpp::signals::NumSlots(100));
}

TEST_F(EventDispatcherTest, Subscribe) {
  EXPECT_EQ(1, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(1, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, Unsubscribe) {
  mgpp::signals::Unsubscribe(INT_EVENT, int_conn_);
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(1, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, UnsubscribeAll) {
  mgpp::signals::UnsubscribeAll();
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(0, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, UnsubscribeAllSignal) {
  mgpp::signals::UnsubscribeAll(INT_EVENT);
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(1, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventDispatcherTest, Publish) {
  mgpp::signals::EventConstPtr int_evt(mgpp::signals::MakeEvent<IntEvent>(0));
  mgpp::signals::Publish(int_evt);
  mgpp::signals::EventConstPtr str_evt(
      mgpp::signals::MakeEvent<StringEvent>("foo"));
  mgpp::signals::Publish(str_evt);
}

class Foo {
 public:
  void IntCb(mgpp::signals::EventConstPtr event) {
    const IntEvent &int_evt = static_cast<const IntEvent &>(*event);
    EXPECT_EQ(int_evt.id(), int_evt.arg());
  }

  void StringCb(mgpp::signals::EventConstPtr event) {
    const StringEvent &str_evt = static_cast<const StringEvent &>(*event);
    EXPECT_EQ("foo", str_evt.arg());
  }
};

class EventMemberDispatcherTest : public ::testing::Test {
 public:
  EventMemberDispatcherTest() : foo_(), int_conn_(), string_conn_() {}

 protected:
  virtual void SetUp() {
    int_conn_ = mgpp::signals::Subscribe(INT_EVENT, &Foo::IntCb, foo_);
    string_conn_ = mgpp::signals::Subscribe(STRING_EVENT, &Foo::StringCb, foo_);
  }

  virtual void TearDown() { mgpp::signals::UnsubscribeAll(); }

  Foo foo_;
  mgpp::signals::Connection int_conn_;
  mgpp::signals::Connection string_conn_;
};

TEST_F(EventMemberDispatcherTest, Subscribe) {
  EXPECT_EQ(1, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(1, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, Unsubscribe) {
  mgpp::signals::Unsubscribe(INT_EVENT, int_conn_);
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(1, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, UnsubscribeAll) {
  mgpp::signals::UnsubscribeAll();
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(0, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, UnsubscribeAllSignal) {
  mgpp::signals::UnsubscribeAll(INT_EVENT);
  EXPECT_EQ(0, mgpp::signals::NumSlots(INT_EVENT));
  EXPECT_EQ(1, mgpp::signals::NumSlots(STRING_EVENT));
}

TEST_F(EventMemberDispatcherTest, Publish) {
  mgpp::signals::EventConstPtr int_evt(mgpp::signals::MakeEvent<IntEvent>(0));
  mgpp::signals::Publish(int_evt);
  mgpp::signals::EventConstPtr str_evt(
      mgpp::signals::MakeEvent<StringEvent>("foo"));
  mgpp::signals::Publish(str_evt);
}
