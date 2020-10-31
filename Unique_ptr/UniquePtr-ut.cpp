#include "UniquePtr.hpp"
#include "gtest/gtest.h"
#include <memory>

constexpr int testValue = 5;
constexpr int otherTestValue = 15;

class UniquePtrTest : public testing::Test {
  public:
    UniquePtrTest() : testUniquePtr_{new int{testValue}} {}

  protected:
    nostd::unique_ptr<int> testUniquePtr_{};
};

class ArrowOperatorTest {
  public:
    int returnTestValue() const { return testValue; }
};

TEST(UniquePtrArrrowOperatorTest, ArrowOperatorShouldGiveAccessToPublicMebersOfClass) {
    const nostd::unique_ptr<ArrowOperatorTest> testPtr_{new ArrowOperatorTest};
    EXPECT_EQ(testPtr_->returnTestValue(), testValue);
}

TEST_F(UniquePtrTest, DereferenceOperatorOfUniquePtrShouldDereference) {
    EXPECT_EQ(*testUniquePtr_, testValue);
}

TEST_F(UniquePtrTest, DereferenceOperatorShouldBeabelTochangeValueInsideUniquePtr) {
    *testUniquePtr_ = otherTestValue;
    EXPECT_EQ(*testUniquePtr_, otherTestValue);
}
TEST_F(UniquePtrTest, UniqePtrShouldBeAbleToMoveOnwershipByConstructor) {
    const nostd::unique_ptr<int> newPtr_(std::move(testUniquePtr_));

    EXPECT_EQ(*newPtr_, testValue);
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
}

TEST_F(UniquePtrTest, UniqePtrShouldBeAbleToMoveOnwershipByAssignmentMoveOperator) {
    nostd::unique_ptr<int> newPtr_;
    newPtr_ = std::move(testUniquePtr_);
    EXPECT_EQ(*newPtr_, testValue);
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
}
TEST_F(UniquePtrTest, GetMethodShouldReturnAdressOfUniquePtr) {
    const auto ptr = testUniquePtr_.get();
    EXPECT_EQ(*testUniquePtr_, *ptr);
}
TEST_F(UniquePtrTest, ResetMethodWithoutParameterShouldResetUniquePtrAndMakeItNullptr) {
    testUniquePtr_.reset();
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
}
TEST_F(UniquePtrTest, ResetMethodWithtParameterShouldResetUniquePtrAndFillItWithNewValue) {
    testUniquePtr_.reset(new int{otherTestValue});
    EXPECT_EQ(*testUniquePtr_, otherTestValue);
}
TEST_F(UniquePtrTest, ReleaseMethodShouldReleaseUniquePtrOnwership) {
    auto ptr = testUniquePtr_.release();
    EXPECT_EQ(*ptr, testValue);
    EXPECT_EQ(testUniquePtr_.get(), nullptr);
    delete ptr;
}
