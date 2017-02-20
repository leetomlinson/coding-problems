/****************************************************************
 * These are my solutions to exercises in Cracking the Coding
 * Interview 6th ed. by Gayle Laakmann McDowell
 *
 * Lee Tomlinson
 ****************************************************************/

#include <iostream>
#include <vector>
#include <stdexcept>
#include <gtest/gtest.h>

/**
 * Ch8 Ex1: Triple Step
 */

class NumberOfWaysClass {
private:
  std::vector<int> num_ways_;
  
public:
  NumberOfWaysClass() : num_ways_{0, 1, 2, 4} {
  }

  /**
   * Computes the number of ways of arriving at a given step.
   * @param step The step number
   */
  int operator()(int step) {
    if (step < 1) {
      throw std::invalid_argument("Step must be > 0");
    }
    
    if (step < num_ways_.size()) {
      return num_ways_[step];
    }

    num_ways_.push_back((*this)(step - 1) +
			(*this)(step - 2) +
			(*this)(step - 3));
    
    return num_ways_[step];
  }
} NumberOfWays;

/**
 * Assumptions:
 *
 * Concerns:
 * - Integer overflow
 *
 * Complexity:
 * - For first calculation of step N the complexity is O(N) time and
 *   O(N) space (because of the recursive call stack).
 *
 * Notes:
 */

TEST(test_ch8_ex1, test_NumberOfWays_basic) {
  EXPECT_EQ(NumberOfWays(1), 1);
  EXPECT_EQ(NumberOfWays(2), 2);
  EXPECT_EQ(NumberOfWays(3), 4);
  EXPECT_EQ(NumberOfWays(4), 7);
}
