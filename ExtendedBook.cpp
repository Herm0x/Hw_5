#include <fstream>
#include <iostream>
#include <string>
#include <locale>     // tolower()

#include "ExtendedBook.hpp"


namespace
{
  // Non-member helper function
  std::string sanitize( const std::string & word )
  {
    constexpr char bad_char[] = " \t\n\b\v_-\"'(){}+/*,=.!?:;";            // leading and trailing characters to be removed
    static std::locale locality;

    auto startIndex = word.find_first_not_of( bad_char );                  // start with the first non-bad character
    if( startIndex == std::string::npos ) startIndex = word.size();        // if the word contains only bad characters ...

    std::size_t count    = 0;                                              // assume the word contains only bad characters ...
    auto        endIndex = word.find_last_not_of( bad_char );              // end with the first non-bad character

    if( endIndex != std::string::npos ) count = endIndex - startIndex + 1; // number of characters to use in results

    auto result = word.substr( startIndex, count );                        // strip the leading and trailing bad characters
    for( auto & c : result ) c = std::tolower( c, locality );              // convert to lower case

    return result;
  }
}    // namespace







///////////////////////// TO-DO (1) //////////////////////////////
  /// Implement ExtendedBook's constructor.  Avoid setting the base class's attributes within the body of this function.  Instead,
  /// be sure to use a Constructor Member Initialization List to construct the base class passing the proper values. Look up member
  /// initialization if you don't remember what that is.  See
  ///  - https://en.cppreference.com/w/cpp/language/constructor and
  ///  - https://www.learncpp.com/cpp-tutorial/constructor-member-initializer-lists/
  ///
  ///
    /// This function constructs an extended book by first constructing the base class and then populating a word frequency table as
    /// the book's content is read.  In the function's body:
    ///   i  Open the disk file containing this book's content as an input file stream.  The name of the disk file, if it exists, is
    ///      ISBN.bok where ISBN is the book's 10 or 13 digit ISBN.  For example, 9789999275842.bok contains the text of book with
    ///      an ISBN of "9789999275842" titled "Billboard Music Week (1st edition)" by "Joel Whitburn".
    ///  ii. Read from the input stream a single word at a time (delimited by whitespace as defined in standard C++) until end of
    ///      file, and for each word read
    /// iii. increment the number of times this (sanitized) word has appeared in the text if it has been seen before, otherwise add
    ///      it to the table and initialize the frequency.
    ///
    /// Constraint: Only "sanitized" words should be added to the frequency table. For example, leading and trailing punctuation,
    /// parentheses, brackets, etc. should be removed, but intra - word punctuation should remain. A working sanitize function has
    /// been provided.
ExtendedBook::ExtendedBook(std::string theTitle, std::string theAuthor, std::string theIsbn, double thePrice): Book{theTitle, theAuthor, theIsbn, thePrice}
{
  std::string disk = Book::isbn();
  std::ifstream fin(disk);
  disk += ".bok";

  std::string readWord;
  while(fin >> readWord)
  {
    readWord = sanitize(readWord);
    auto find = _number.find(readWord);

    if(find != _number.end())
    {
      find-> second++;
    }
    else
    {
      _number[readWord] = 1;
    }
  }
}
/////////////////////// END-TO-DO (1) ////////////////////////////



///////////////////////// TO-DO (2) //////////////////////////////
  /// Implement numberOfWords - This function takes no arguments and returns the number of unique (sanitized) words.
std::size_t ExtendedBook::numberOfWords() const
{
  return this-> _number.size();
}
/////////////////////// END-TO-DO (2) ////////////////////////////



///////////////////////// TO-DO (3) //////////////////////////////
  /// Implement wordCount - This function takes a constant reference to a standard string as a parameter and returns the frequency
  /// of occurrence of that sanitized word.
std::size_t ExtendedBook::wordCount(const std::string & word) const
{
  std::string currentWord = sanitize(word);
  return _number.at(currentWord);
}
/////////////////////// END-TO-DO (3) ////////////////////////////



///////////////////////// TO-DO (4) //////////////////////////////
  /// Implement mostFrequentWord - This function takes no arguments and returns the most frequent word, or the empty string if there are no words.
    /// If the frequency table is empty, return the empty string.  Otherwise, assume the most frequent word is at the beginning of your
    /// frequency table. Then visit every word in your frequency table comparing its frequency to the current most frequent word.
    /// Adopt that word as your most frequent if its frequency is grater than your current most frequent.
std::string ExtendedBook::mostFrequentWord() const
{
  std::string recent;
  for(auto it = _number.begin(); it != _number.end(); ++it)
  {
    std::size_t i = 0;
    if(it-> second > i)
    {
      recent = it-> first;
      i = it-> second;
    }
  }
  return recent;
}
/////////////////////// END-TO-DO (4) ////////////////////////////




///////////////////////// TO-DO (5) //////////////////////////////
  /// Implement maxBucketSize - This function takes no arguments and returns the size of the largest bucket in the hash table
  ///
  /// Hint: see the unordered_map's bucket interface at https://en.cppreference.com/w/cpp/container/unordered_map
    /// Assume the size of the bucket with the most word/count pairs is zero.  Then visit each bucket (indexed from 0..bucket_count)
    /// and if the size of that bucket (bucket_size) is greater than your current max size, adopt that as your new current max size.
std::size_t ExtendedBook::maxBucketSize() const
{
  std::size_t bucket = _number.bucket_count();
  std::size_t currentSize = 0;
  std::size_t largeBucket = 0;

  std::size_t i = 0;
  while(i < bucket)
  {
    currentSize = _number.bucket_size(i);
    if (currentSize > largeBucket)
    {
      largeBucket = currentSize;
    }
    ++i;
  }
  return largeBucket;
}
/////////////////////// END-TO-DO (5) ////////////////////////////
