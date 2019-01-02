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

#include <iostream>
#include <tuple>

#include <mgpp/ao.hpp>

using StateRecord = std::tuple<mgpp::ao::StateHandler, int>;

template <class T>
StateRecord CreateRecord(T state, int sig) {
  return std::make_tuple(mgpp::ao::StateCast(state), sig);
}

enum TestEvent {
  A_SIG = mgpp::ao::USER_SIG,
  B_SIG,
  C_SIG,
  D_SIG,
  E_SIG,
  F_SIG,
  G_SIG,
  H_SIG
};

class TestHsm : public mgpp::ao::Hsm {
 public:
  TestHsm() : mgpp::ao::Hsm(mgpp::ao::StateCast(TestTop)) {}

  static mgpp::ao::StateAction TestTop(TestHsm *const me,
                                       mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "TestTop: Enter" << std::endl;
        me->records_.push_back(CreateRecord(TestTop, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "TestTop: Init" << std::endl;
        me->records_.push_back(CreateRecord(TestTop, evt->id()));
        return me->InitialTransition(S3);
      case mgpp::ao::EXIT_SIG:
        std::cout << "TestTop: Exit" << std::endl;
        me->records_.push_back(CreateRecord(TestTop, evt->id()));
        return me->Handled();
    }

    return me->Super(mgpp::ao::Hsm::Top);
  }

  static mgpp::ao::StateAction S1(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S1: Enter" << std::endl;
        me->records_.push_back(CreateRecord(S1, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S1: Init" << std::endl;
        me->records_.push_back(CreateRecord(S1, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S1: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S1, evt->id()));
        return me->Handled();
    }

    return me->Super(TestTop);
  }

  static mgpp::ao::StateAction S2(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S2: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S2, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S2: Init" << std::endl;
        me->records_.push_back(CreateRecord(S2, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S2: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S2, evt->id()));
        return me->Handled();
    }

    return me->Super(S1);
  }

  static mgpp::ao::StateAction S3(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S3: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S3: Init" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Handled();
      case A_SIG:
        std::cout << "S3: A" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S3);
      case B_SIG:
        std::cout << "S3: B" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S4);
      case C_SIG:
        std::cout << "S3: C" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S7);
      case D_SIG:
        std::cout << "S3: D" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S2);
      case E_SIG:
        std::cout << "S3: E" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S6);
      case F_SIG:
        std::cout << "S3: F" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S10);
      case G_SIG:
        std::cout << "S3: G" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Transition(S13);
      case mgpp::ao::EXIT_SIG:
        std::cout << "S3: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S3, evt->id()));
        return me->Handled();
    }

    return me->Super(S2);
  }

  static mgpp::ao::StateAction S4(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S4: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S4, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S4: Init" << std::endl;
        me->records_.push_back(CreateRecord(S4, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S4: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S4, evt->id()));
        return me->Handled();
    }

    return me->Super(S3);
  }

  static mgpp::ao::StateAction S5(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S5: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S5, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S5: Init" << std::endl;
        me->records_.push_back(CreateRecord(S5, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S5: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S5, evt->id()));
        return me->Handled();
    }

    return me->Super(S4);
  }

  static mgpp::ao::StateAction S6(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S6: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S6, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S6: Init" << std::endl;
        me->records_.push_back(CreateRecord(S6, evt->id()));
        return me->Handled();
      case H_SIG:
        std::cout << "S6: H" << std::endl;
        me->records_.push_back(CreateRecord(S6, evt->id()));
        return me->Transition(S1);
      case mgpp::ao::EXIT_SIG:
        std::cout << "S6: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S6, evt->id()));
        return me->Handled();
    }

    return me->Super(S5);
  }

  static mgpp::ao::StateAction S7(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S7: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S7, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S7: Init" << std::endl;
        me->records_.push_back(CreateRecord(S7, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S7: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S7, evt->id()));
        return me->Handled();
    }

    return me->Super(S2);
  }

  static mgpp::ao::StateAction S8(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S8: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S8, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S8: Init" << std::endl;
        me->records_.push_back(CreateRecord(S8, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S8: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S8, evt->id()));
        return me->Handled();
    }

    return me->Super(S7);
  }

  static mgpp::ao::StateAction S9(TestHsm *const me,
                                  mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S9: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S9, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S9: Init" << std::endl;
        me->records_.push_back(CreateRecord(S9, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S9: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S9, evt->id()));
        return me->Handled();
    }

    return me->Super(S8);
  }

  static mgpp::ao::StateAction S10(TestHsm *const me,
                                   mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S10: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S10, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S10: Init" << std::endl;
        me->records_.push_back(CreateRecord(S10, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S10: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S10, evt->id()));
        return me->Handled();
    }

    return me->Super(S9);
  }

  static mgpp::ao::StateAction S11(TestHsm *const me,
                                   mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S11: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S11, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S11: Init" << std::endl;
        me->records_.push_back(CreateRecord(S11, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S11: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S11, evt->id()));
        return me->Handled();
    }

    return me->Super(TestTop);
  }

  static mgpp::ao::StateAction S12(TestHsm *const me,
                                   mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S12: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S12, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S12: Init" << std::endl;
        me->records_.push_back(CreateRecord(S12, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S12: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S12, evt->id()));
        return me->Handled();
    }

    return me->Super(S11);
  }

  static mgpp::ao::StateAction S13(TestHsm *const me,
                                   mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S13: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S13, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S13: Init" << std::endl;
        me->records_.push_back(CreateRecord(S13, evt->id()));
        return me->InitialTransition(S14);
      case mgpp::ao::EXIT_SIG:
        std::cout << "S13: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S13, evt->id()));
        return me->Handled();
    }

    return me->Super(S12);
  }

  static mgpp::ao::StateAction S14(TestHsm *const me,
                                   mgpp::ao::EventConstPtr evt) {
    switch (evt->id()) {
      case mgpp::ao::ENTRY_SIG:
        std::cout << "S14: Entry" << std::endl;
        me->records_.push_back(CreateRecord(S14, evt->id()));
        return me->Handled();
      case mgpp::ao::INIT_SIG:
        std::cout << "S14: Init" << std::endl;
        me->records_.push_back(CreateRecord(S14, evt->id()));
        return me->Handled();
      case mgpp::ao::EXIT_SIG:
        std::cout << "S14: Exit" << std::endl;
        me->records_.push_back(CreateRecord(S14, evt->id()));
        return me->Handled();
    }

    return me->Super(S13);
  }

  void ClearRecords() { records_.clear(); }

  std::vector<StateRecord> records_;
};

class HsmTest : public ::testing::Test {
 protected:
  virtual void SetUp() { hsm.Init(); }

  virtual void TearDown() {}

  void CompareStateRecord(const std::vector<StateRecord> &records) {
    EXPECT_EQ(hsm.records_.size(), records.size());
    for (std::size_t i = 0; i < records.size(); ++i) {
      EXPECT_EQ(std::get<0>(hsm.records_[i]), std::get<0>(records[i]));
      EXPECT_EQ(std::get<1>(hsm.records_[i]), std::get<1>(records[i]));
    }
  }

  TestHsm hsm;
};

TEST_F(HsmTest, HsmInit) {
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S3));

  // Verify entry and init sequence of HSM init
  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::TestTop, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::TestTop, mgpp::ao::INIT_SIG));
  records.push_back(CreateRecord(TestHsm::S1, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S2, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
}

TEST_F(HsmTest, TransitionA) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr A(mgpp::ao::MakeEvent<mgpp::ao::Event>(A_SIG));
  hsm.Dispatch(A);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, A_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S3));
}

TEST_F(HsmTest, TransitionB) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr B(mgpp::ao::MakeEvent<mgpp::ao::Event>(B_SIG));
  hsm.Dispatch(B);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, B_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S4));
}

TEST_F(HsmTest, TransitionC) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr C(mgpp::ao::MakeEvent<mgpp::ao::Event>(C_SIG));
  hsm.Dispatch(C);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, C_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S7, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S7, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S7));
}

TEST_F(HsmTest, TransitionD) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr D(mgpp::ao::MakeEvent<mgpp::ao::Event>(D_SIG));
  hsm.Dispatch(D);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, D_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S2, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S2));
}

TEST_F(HsmTest, TransitionE) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr E(mgpp::ao::MakeEvent<mgpp::ao::Event>(E_SIG));
  hsm.Dispatch(E);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, E_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S5, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S6, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S6, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S6));
}

TEST_F(HsmTest, TransitionF) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr F(mgpp::ao::MakeEvent<mgpp::ao::Event>(F_SIG));
  hsm.Dispatch(F);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, F_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S7, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S8, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S9, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S10, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S10, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S10));
}

TEST_F(HsmTest, TransitionG) {
  hsm.ClearRecords();
  mgpp::ao::EventConstPtr G(mgpp::ao::MakeEvent<mgpp::ao::Event>(G_SIG));
  hsm.Dispatch(G);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, G_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S2, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S1, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S11, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S12, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S13, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S13, mgpp::ao::INIT_SIG));
  records.push_back(CreateRecord(TestHsm::S14, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S14, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S14));
}

TEST_F(HsmTest, TransitionH) {
  // Need to start in S6 for this test
  mgpp::ao::EventConstPtr E(mgpp::ao::MakeEvent<mgpp::ao::Event>(E_SIG));
  hsm.Dispatch(E);

  hsm.ClearRecords();
  mgpp::ao::EventConstPtr H(mgpp::ao::MakeEvent<mgpp::ao::Event>(H_SIG));
  hsm.Dispatch(H);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S6, H_SIG));
  records.push_back(CreateRecord(TestHsm::S6, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S5, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S2, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S1, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S1));
}

TEST_F(HsmTest, TransitionASuperHandle) {
  // Need to start in S6 for this test
  mgpp::ao::EventConstPtr E(mgpp::ao::MakeEvent<mgpp::ao::Event>(E_SIG));
  hsm.Dispatch(E);

  hsm.ClearRecords();
  mgpp::ao::EventConstPtr A(mgpp::ao::MakeEvent<mgpp::ao::Event>(A_SIG));
  hsm.Dispatch(A);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, A_SIG));
  records.push_back(CreateRecord(TestHsm::S6, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S5, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S3));
}

TEST_F(HsmTest, TransitionBSuperHandle) {
  // Need to start in S6 for this test
  mgpp::ao::EventConstPtr E(mgpp::ao::MakeEvent<mgpp::ao::Event>(E_SIG));
  hsm.Dispatch(E);

  hsm.ClearRecords();
  mgpp::ao::EventConstPtr B(mgpp::ao::MakeEvent<mgpp::ao::Event>(B_SIG));
  hsm.Dispatch(B);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, B_SIG));
  records.push_back(CreateRecord(TestHsm::S6, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S5, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S4));
}

TEST_F(HsmTest, TransitionFSuperHandle) {
  // Need to start in S6 for this test
  mgpp::ao::EventConstPtr E(mgpp::ao::MakeEvent<mgpp::ao::Event>(E_SIG));
  hsm.Dispatch(E);

  hsm.ClearRecords();
  mgpp::ao::EventConstPtr F(mgpp::ao::MakeEvent<mgpp::ao::Event>(F_SIG));
  hsm.Dispatch(F);

  std::vector<StateRecord> records;
  records.push_back(CreateRecord(TestHsm::S3, F_SIG));
  records.push_back(CreateRecord(TestHsm::S6, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S5, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S4, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S3, mgpp::ao::EXIT_SIG));
  records.push_back(CreateRecord(TestHsm::S7, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S8, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S9, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S10, mgpp::ao::ENTRY_SIG));
  records.push_back(CreateRecord(TestHsm::S10, mgpp::ao::INIT_SIG));
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S10));
}

TEST_F(HsmTest, IgnoreUnhandledEvent) {
  // Need to start in S10 for this test
  mgpp::ao::EventConstPtr F(mgpp::ao::MakeEvent<mgpp::ao::Event>(F_SIG));
  hsm.Dispatch(F);

  hsm.ClearRecords();
  for (int sig = A_SIG; sig <= H_SIG; sig++) {
    TestEvent evt_sig = static_cast<TestEvent>(sig);
    mgpp::ao::EventConstPtr evt(mgpp::ao::MakeEvent<mgpp::ao::Event>(evt_sig));
    hsm.Dispatch(evt);
  }

  // Create empty state record vector. No events should be handled.
  std::vector<StateRecord> records;
  CompareStateRecord(records);
  EXPECT_EQ(hsm.state(), mgpp::ao::StateCast(TestHsm::S10));
}
