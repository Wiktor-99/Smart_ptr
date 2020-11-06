#include "SharedPtr.hpp"
#include "gtest/gtest.h"
#include <memory>

constexpr int intTestValue = 9;
constexpr double doubleTestValue = 11.111;
constexpr int otherIntTestValue = 39;
constexpr double otherDoubleTestValue = 1.111;
constexpr int base = 2;
constexpr int baseToThePower2 = base * base;

class SharedPtrTest : public testing::Test {
  public:
    SharedPtrTest() : intSharedPtr_{new int{intTestValue}}, doubleSharedPtr_{new double{doubleTestValue}} {}

  protected:
    nostd::shared_ptr<int> intSharedPtr_{};
    nostd::shared_ptr<double> doubleSharedPtr_{};
};
class ArrowOperatorTest {
  public:
    int pow() const {
        return base * base;
    }
};

TEST(SharedPtrArrrowOperatorTest, ArrowOperatorShouldGiveAccessToPublicMebersOfClass) {
    const nostd::shared_ptr<ArrowOperatorTest> testPtr_{new ArrowOperatorTest};
    EXPECT_EQ(testPtr_->pow(), baseToThePower2);
}

TEST_F(SharedPtrTest, DereferenceOperatorOfsharedPtrShouldDereference) {
    EXPECT_EQ(*intSharedPtr_, intTestValue);
    EXPECT_EQ(*doubleSharedPtr_, doubleTestValue);
}

TEST_F(SharedPtrTest, DereferenceOperatorShouldBeabelTochangeValueInsideSharedPtr) {
    *intSharedPtr_ = otherIntTestValue;
    *doubleSharedPtr_ = otherDoubleTestValue;
    EXPECT_EQ(*intSharedPtr_, otherIntTestValue);
    EXPECT_EQ(*doubleSharedPtr_, otherDoubleTestValue);
    
}
TEST_F(SharedPtrTest, operationCopySharedPtrShouldStorePointerToTheSameAddress) {
    auto intPtrCopy(intSharedPtr_);
    auto doublePtrCopy = doubleSharedPtr_;

    ASSERT_EQ(intSharedPtr_.get(), intPtrCopy.get());
    ASSERT_EQ(doubleSharedPtr_.get(), doublePtrCopy.get());
}