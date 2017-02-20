/****************************************************************
 * These are my solutions to exercises in Cracking the Coding
 * Interview 6th ed. by Gayle Laakmann McDowell
 *
 * Lee Tomlinson
 ****************************************************************/

#include <iostream>
#include <gtest/gtest.h>

/**
 * Ch16 Ex1: Number Swapper
 */

/**
 * Swaps two integers in place using arithmetic.
 * @param a First integer
 * @param b Second integer
 */
void Swap1(int &a, int &b) {
  a += b;
  b -= a;
  a += b;
  b *= -1;
}

/**
 * Swaps two integers in place using bit logic.
 * @param a First integer
 * @param b Second integer
 */
void Swap2(int &a, int &b) {
  b ^= a;
  a ^= b;
  b ^= a;
}

/**
 * Assumptions:
 * - Numbers are integers in [-2^31, 2^31)
 *
 * Concerns:
 * - Integer overflow
 *
 * Complexity:
 * - Both Swap1 and Swap two are O(1) time and O(1) space
 *
 * Notes:
 * - Must pass integers by reference
 */

TEST(test_ch16_ex1, test_Swap1_basic) {
  int a = -5;
  int b = 42;
  Swap1(a, b);
  EXPECT_EQ(a, 42);
  EXPECT_EQ(b, -5);
}

TEST(test_ch16_ex1, test_Swap2_basic) {
  int a = -5;
  int b = 42;
  Swap2(a, b);
  EXPECT_EQ(a, 42);
  EXPECT_EQ(b, -5);
}
