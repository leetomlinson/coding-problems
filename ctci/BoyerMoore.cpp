/****************************************************************
 * These are my solutions to exercises in Cracking the Coding
 * Interview 6th ed. by Gayle Laakmann McDowell
 *
 * Lee Tomlinson
 ****************************************************************/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <gtest/gtest.h>

using namespace std;

/**
 * Boyer-Moore string search algorithm for Ch16 Ex2: Word Frequencies
 */

/**
 * Generates skip array for the 'good suffix rule' in the Boyer-Moore
 * algorithm.
 *
 * @param query Query string
 */
vector<int> GoodSuffixRule(string const &query) {
  vector<int> skip_arr(query.size(), 1);
  if (query.size() < 2) return skip_arr;
  
  for (int idx = query.size() - 2; idx >= 0; --idx) {
    int skip = skip_arr[idx + 1];
    if (query[idx] != query[idx + skip]) {
      skip = query.size() - idx;
    }
    skip_arr[idx] = skip;
  }
  
  return skip_arr;
}

/**
 * Generates skip array (for the specified character) for the 'bad
 * character rule' in the Boyer-Moore algorithm.
 *
 * @param query Query string
 */
vector<int> BadCharRule(char ch, string const &query) {
  vector<int> skip_arr(query.size(), 0);
  int skip = 1;

  for (int column = 0; column < query.size(); ++ column) {
    if (query[column] == ch) {
      skip = 0;
    }
    skip_arr[column] = skip;
    ++skip;
  }
  
  return skip_arr;
}

/**
 * Generates a skip table for the Boyer-Moore search algorithm for the
 * specified query string.  Table rows correspond to characters in the
 * string being searched.  Table columns correspond to the character
 * position of the first mismatch in the query string.  The table is
 * row major, so table[i][j] is the ith row and jth column.
 *
 * @param query Query string
 */
unordered_map<char, vector<int>> GenSkipTable(string const &query) {
  unordered_map<char, vector<int>> table;

  // Compute skip array for 'good suffix rule'
  vector<int> good_suffix_rule = GoodSuffixRule(query);
  
  for (char row : query) {
    if (table.find(row) == table.end()) {
      
      // Compute skip array for 'bad character rule'
      vector<int> bcr_skip_arr = BadCharRule(row, query);
      
      vector<int> skip_arr(query.size(), 0);
      
      for (int i = 0; i < skip_arr.size(); ++i) {
	skip_arr[i] = max(bcr_skip_arr[i], good_suffix_rule[i]);
      }
      
      table[row] = skip_arr;
    }
  }

  vector<int> bcr_skip_arr = BadCharRule(0, query);
  for (int i = 0; i < bcr_skip_arr.size(); ++i) {
    bcr_skip_arr[i] = max(bcr_skip_arr[i], good_suffix_rule[i]);
  }
  table[0] = bcr_skip_arr;

  return table;
}

class BoyerMooreSkipTable {
private:
  unordered_map<char, vector<int>> skip_table_;

public:
  BoyerMooreSkipTable(string const &query);

  int Skip(char row, int column);
};

BoyerMooreSkipTable::BoyerMooreSkipTable(string const &query) : skip_table_{GenSkipTable(query)} {
}

int BoyerMooreSkipTable::Skip(char row, int column) {
  if (skip_table_.find(row) != skip_table_.end()) {
    return skip_table_.at(row).at(column);
  } else {
    return skip_table_.at(0).at(column);
  }
}

/**
 * Searches string from specified character position for exact match
 * with query and returns position of first matching character.
 * Returns len(string) if no match.
 *
 * @param str String in which to search
 * @param query String for which to search
 * @param pos Character position from which to begin searching
 * @return Position of first matching character
 */
int BoyerMooreFind(string const &str, string const &query, int pos) {
  if (query.size() > str.size()) {
    return str.size();
  }
  
  // Initialize skips table
  BoyerMooreSkipTable skip(query);

  for (int idx_begin = pos; idx_begin < str.size() - query.size(); ) {
    // Could also use 'while' loop
    bool match = true;
    int idx_query = query.size() - 1;
      
    for (; idx_query >= 0; --idx_query) {
      // Could also use while loop
      if (query[idx_query] != str[idx_begin + idx_query]) {
	match = false;
	break;
      }
    }

    if (match) {
      return idx_begin;
    }

    idx_begin += skip.Skip(str[idx_begin + idx_query], idx_query);
  }

  return str.size();
}

/**
 * Assumptions:
 * - The null character may not appear in any string
 *
 * Concerns:
 *
 * Complexity: Is this analysis correct?  Brute-force search is O(M*N)
 * - Let 'searched' be string of length M - string being searched
 * - Let 'query' be string of length N - query string
 * - Typically better than O(M*N)
 * - Min skip is 1 --> Worst case: O(N); e.g. consider searching for 'A' in 'BCDEFGHIJ'
 * - Max skip is len(query) --> Best case: O(M/N)
 *
 * Notes:
 * - Step through algorithms to check they work!
 */

TEST(test_ch16_ex2, test_GoodSuffixRule_basic) {
  vector<int> output_actual = GoodSuffixRule("CCGTAACTGCTGAACTGCTG");
  vector<int> output_expected = {
    20, 19, 17, 17, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 3, 3, 3, 3, 2, 1};
  EXPECT_EQ(output_expected, output_actual);
}

TEST(test_ch16_ex2, test_BadCharRule_basic) {
  vector<int> output_actual = BadCharRule('C', "CCGTAACTGCTGAACTGCTG");
  vector<int> output_expected = {
    0, 0, 1, 2, 3, 4, 0, 1, 2, 0, 1, 2, 3, 4, 0, 1, 2, 0, 1, 2};
  EXPECT_EQ(output_expected, output_actual);
}

TEST(test_ch16_ex2, test_BadCharRule_default) {
  vector<int> output_actual = BadCharRule('*', "CCGTAACTGCTGAACTGCTG");
  vector<int> output_expected = {
    1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  EXPECT_EQ(output_expected, output_actual);
}

TEST(test_ch16_ex2, test_GenSkipTable_basic) {
  unordered_map<char, vector<int>> output_actual = GenSkipTable("CCGTAACTGCTGAACTGCTG");
  unordered_map<char, vector<int>> output_expected;
  output_expected['A'] = {20, 19, 17, 17, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 3, 3, 3, 4, 5, 6};
  output_expected['C'] = {20, 19, 17, 17, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 3, 3, 3, 3, 2, 2};
  output_expected['G'] = {20, 19, 17, 17, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 3, 4, 3, 3, 2, 1};
  output_expected['T'] = {20, 19, 17, 17, 8, 8, 8, 8, 8, 8, 8, 8, 8, 7, 4, 3, 3, 3, 2, 1};
  output_expected[0] = {20, 19, 17, 17, 8, 8, 8, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
  for (char ch : {'A', 'C', 'G', 'T', '\0'}) {
    EXPECT_EQ(output_expected[ch], output_actual[ch]);
  }
}

TEST(test_ch16_ex2, test_BoyerMooreFind_basic) {
  EXPECT_EQ(4, BoyerMooreFind("CCGTAACTGCTGAACTGCTG", "AACT", 0));
  EXPECT_EQ(4, BoyerMooreFind("CCGTAACTGCTGAACTGCTG", "AACT", 4));
  EXPECT_EQ(12, BoyerMooreFind("CCGTAACTGCTGAACTGCTG", "AACT", 5));
  EXPECT_EQ(20, BoyerMooreFind("CCGTAACTGCTGAACTGCTG", "AACTA", 0));
}
