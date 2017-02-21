/****************************************************************
 * These are my solutions to exercises in Cracking the Coding
 * Interview 6th ed. by Gayle Laakmann McDowell
 *
 * Lee Tomlinson
 ****************************************************************/

#include <gtest/gtest.h>
#include <vector>

using namespace std;

/**
 * Ch16 Ex4: Tic Tac Win
 */

/**
 * Returns 1 if 'X' wins, -1 if 'Y' wins, and 0 otherwise.
 *
 * @param board 2D character array representation of board
 * @param size Size of board in each dimension
 */
int IsWin(char board[], int size) {
  // Validate input:
  // size > 0

  vector<int> rtally(size, 0);
  vector<int> ctally(size, 0);
  int pdiag = 0;
  int ndiag = 0;

  for (int r = 0; r < size; ++r) {
    for (int c = 0; c < size; ++c) {
      if (board[r * size + c] == 'X') {
	++rtally[r];
	++ctally[c];
	if (r == c) ++pdiag;
	if (r + c == 0) ++ndiag;
      }
      if (board[r * size + c] == 'O') {
	--rtally[r];
	--ctally[c];
	if (r == c) --pdiag;
	if (r + c == 0) --ndiag;
      }      
    }
  }

  for (int tot : rtally) {
    if (abs(tot) == size) return tot / size;
  }

  for (int tot : ctally) {
    if (abs(tot) == size) return tot / size;
  }

  if (abs(pdiag) == size) return pdiag / size;
  if (abs(ndiag) == size) return ndiag / size;

  return 0;
}

/**
 * Assumptions:
 * - 2 players 'X' and 'O'
 *
 * Concerns:
 * - Erroneous input: incorrect size specified would lead to
 *   out-of-bounds error
 *
 * Complexity:
 * - O(N^2) time and O(N) space, where N is side length of board
 *
 * Notes:
 * 
 */

TEST(test_ch16_ex4, test_IsWin_basic) {
  char board[9] = {'X',  'O', '\0', 'O', '\0',  'O', 'X',  'X',  'X'};
  // EXPECT_EQ(board[0][1], 'O');
  // EXPECT_EQ(board[2][0], 'X');
  EXPECT_EQ(1, IsWin(board, 3));
}
