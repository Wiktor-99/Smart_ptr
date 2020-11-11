#include "SharedPtr.hpp"
#include "gtest/gtest.h"
#include <memory>

constexpr int intTestValue = 9;
constexpr double doubleTestValue = 11.111;
constexpr int otherIntTestValue = 39;
constexpr double otherDoubleTestValue = 1.111;
constexpr int base = 2;
constexpr int baseToThePower2 = base * base;
constexpr std::size_t firstPtrCount = 1;
constexpr std::size_t secondPtrCount = 2;
constexpr std::size_t thirdPtrCount = 3;
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
TEST_F(SharedPtrTest, forFirstPtrCountShouldBeEqualOneAndShouldIncrementCounterAndDecrementeCounter) {
    ASSERT_EQ(intSharedPtr_.use_count(), firstPtrCount);
    auto newPtr1 = intSharedPtr_;
    ASSERT_EQ(intSharedPtr_.use_count(), secondPtrCount);
    ASSERT_EQ(newPtr1.use_count(), secondPtrCount);
    {
        auto newPtr2 = intSharedPtr_;
        ASSERT_EQ(intSharedPtr_.use_count(), thirdPtrCount);
        ASSERT_EQ(newPtr1.use_count(), thirdPtrCount);
        ASSERT_EQ(newPtr2.use_count(), thirdPtrCount);
    }
    ASSERT_EQ(intSharedPtr_.use_count(), secondPtrCount);
    ASSERT_EQ(newPtr1.use_count(), secondPtrCount);
}
TEST_F(SharedPtrTest, sharedPtrShouldBeAbleToCastToBool) {
    nostd::shared_ptr<int> empty;
    ASSERT_FALSE(empty);
    ASSERT_TRUE(intSharedPtr_);
    ASSERT_TRUE(doubleSharedPtr_);
}
TEST_F(SharedPtrTest, resetMethodShouldResetSharedPtr) {
    intSharedPtr_.reset();
    doubleSharedPtr_.reset();
    ASSERT_EQ(intSharedPtr_.get(),nullptr);
    ASSERT_EQ(doubleSharedPtr_.get(),nullptr);
    constexpr int newIntValue = 13;
    constexpr double newDoubleValue = 13.05;
  
    intSharedPtr_.reset(new int{newIntValue});
    doubleSharedPtr_.reset(new double(newDoubleValue));
    ASSERT_EQ(*intSharedPtr_,newIntValue);
    ASSERT_EQ(*doubleSharedPtr_,newDoubleValue);
}
TEST_F(SharedPtrTest, afterUsingResetMethodCounterShouldBeDecremented){
    auto ptr2(intSharedPtr_);
    ASSERT_EQ(intSharedPtr_.use_count(), secondPtrCount);
    intSharedPtr_.reset();
    ASSERT_EQ(intSharedPtr_.use_count(), firstPtrCount);    
}
TEST_F(SharedPtrTest, DecrementOfCounterShouldNotCauseDestructionOfObject){
  {
    auto ptr2(intSharedPtr_);
  }
  ASSERT_EQ(*intSharedPtr_, intTestValue);
}