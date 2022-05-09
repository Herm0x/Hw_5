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
ExtendedBook::ExtendedBook(std::string_view theTitle, std::string_view theAuthor, std::string_view theIsbn, double thePrice): Book(theTitle, theAuthor, theIsbn, thePrice)
{
  std::string disk = Book::isbn();
  disk += ".bok";
  std::ifstream fin(disk);

  std::string word;
  while(fin >> word)
  {
    word = sanitize(word);
    auto find = _number.find(word);

    if(find != _number.end())
    {
      find-> ++second;
    }
    else
    {
      _number[word] = 1;
    }
  }
}
/////////////////////// END-TO-DO (1) ////////////////////////////



///////////////////////// TO-DO (2) //////////////////////////////
  /// Implement numberOfWords - This function takes no arguments and returns the number of unique (sanitized) words.
std::size_t ExtendedBook::numberOfWords() const
{
  std::size_t size = 0;
  for( auto it = _number.begin(); it != _number.end(); ++it )
  {
    ++size;
  }
  return size;
}
/////////////////////// END-TO-DO (2) ////////////////////////////



///////////////////////// TO-DO (3) //////////////////////////////
  /// Implement wordCount - This function takes a constant reference to a standard string as a parameter and returns the frequency
  /// of occurrence of that sanitized word.
std::size_t ExtendedBook::wordCount(const std::string & word) const
{
  // make sure the word is sanitized
  std::string currentWord = sanitize(word);

  // return word count for the word
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
  std::size_t max = 0;
  std::string currentWord;
  auto word = _number.begin();

  while( word != _number.end() )
  {
    // for each word in container, if word count > max, set word count to max
    if(word-> second > max)
    {
      currentWord = word-> first;
      max = word-> second;
    }
    ++word;
  }
  return currentWord;
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
  std::size_t largestBucket = 0;
  std::size_t currentBucketSize = 0;
  std::size_t bucketCount = _number.bucket_count();

  // for each bucket in hash table
  for( std::size_t i = 0; i < bucketCount; ++i )
  {
    // size of bucket at index i in hash table
    currentBucketSize = _number.bucket_size( i );
    // if the current bucket size is greater than the size of the largest bucket
    if( currentBucketSize > largestBucket )
    {
      // assign current bucket size as the largest bucket size
      largestBucket = currentBucketSize;
    }
  }
  return largestBucket;
}
/////////////////////// END-TO-DO (5) ////////////////////////////
