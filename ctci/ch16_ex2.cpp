/****************************************************************
 * These are my solutions to exercises in Cracking the Coding
 * Interview 6th ed. by Gayle Laakmann McDowell
 *
 * Lee Tomlinson
 ****************************************************************/

#include <gtest/gtest.h>
#include <unordered_map>
#include <string>
#include <stdexcept>
#include "BoyerMoore.h"

using namespace std;

/**
 * Ch16 Ex2: Word Frequencies
 */

class WordHist {
private:
  unordered_map<string, int> hist_;
  string const &book_;

public:
  WordHist(string const &book) : book_{book} {
  }

  int Frequency(string const &word);
};

/**
 * Returns the frequency of occurrence of the specified word in the
 * book.
 *
 * @param word Search word
 */
int WordHist::Frequency(string const &word) {
  // Validate input
  if (word.size() == 0) {
    throw std::length_error("Word cannot be empty string");
  }
  
  if (hist_.find(word) == hist_.end()) {
    hist_[word] = 0;
    int pos = 0;
    while (pos < book_.size()) {
      // BoyerMooreFind returns len(book_) if word not found
      pos = BoyerMooreFind(book_, word, pos) + 1;  // Note we must
						   // skip pass found
						   // position to
						   // avoid infinite
						   // loop
      if (pos < book_.size()) {
	++hist_[word];
      }
    }
  }
  
  return hist_[word];
}

/**
 *
 */

TEST(test_ch16_ex2, test_WordHist_Frequency_basic) {
  string book = "Lorem ipsum dolor sit amet, consectetur adipiscing elit, sed do "
    "eiusmod tempor incididunt ut labore et dolore magna aliqua. Ut enim ad "
    "minim veniam, quis nostrud exercitation ullamco laboris nisi ut "
    "aliquip ex ea commodo consequat. Duis aute irure dolor in "
    "reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla "
    "pariatur. Excepteur sint occaecat cupidatat non proident, sunt in "
    "culpa qui officia deserunt mollit anim id est laborum.";
  WordHist wh(book);
  // Ideally want to consider words in general, not just words
  // followed by a space:
  EXPECT_EQ(3, wh.Frequency("in "));
  EXPECT_EQ(3, wh.Frequency("in "));
}
