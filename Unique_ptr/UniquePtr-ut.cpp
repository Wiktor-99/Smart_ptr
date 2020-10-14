#include "UniquePtr.hpp"
#include "gtest/gtest.h"

constexpr int testValue = 5;

class UniquePtrTest : public testing::Test {
  public:
    UniquePtrTest() : testUniquePtr_{new int{testValue}} {}

  protected:
    nostd::unique_ptr<int> testUniquePtr_{};
};

TEST_F(UniquePtrTest, DereferenceOperatorOfUniquePtrShouldDereference) {
    EXPECT_EQ(*testUniquePtr_,testValue);
}