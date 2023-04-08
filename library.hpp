#ifndef UC_LIBRARY_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
#define UC_LIBRARY_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7

/**
 * library.hpp
 *
 * This file provides the implementation for built-in uC types and
 * functions.
 *
 * Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
 */

#include <iostream>
#include <cstdint>
#include <string>
#include <cmath>
#include "defs.hpp"

// A macro for defining a numerical conversion function.
#define UC_NUM_CONV(target, src)                               \
  static UC_PRIMITIVE(target)                                  \
    UC_FUNCTION(src ## _to_ ## target)(UC_PRIMITIVE(src) i) { \
    return static_cast<UC_PRIMITIVE(target)>(i);               \
  }

// A macro for defining a function to convert a built-in type to a
// string.
#define UC_STR_CONV(src)                                       \
  static UC_PRIMITIVE(string)                                  \
    UC_FUNCTION(src ## _to_string)(UC_PRIMITIVE(src) i) {     \
    return std::to_string(i);                                   \
  }

// A macro for defining a function to convert from a string to a
// built-in type.
#define UC_FROM_STR(target, func)                                      \
  static UC_PRIMITIVE(target)                                          \
    UC_FUNCTION(string_to_ ## target)(UC_PRIMITIVE(string) i) {       \
    return func(i);                                                     \
  }

namespace uc {

  // Enable literals for C++ strings.
  using namespace std::string_literals;

  // Type aliases for built-in types.
  using UC_PRIMITIVE(int) = std::int32_t;
  using UC_PRIMITIVE(long) = std::int64_t;
  using UC_PRIMITIVE(float) = double;
  using UC_PRIMITIVE(boolean) = bool;
  using UC_PRIMITIVE(string) = std::string;
  using UC_PRIMITIVE(void) = void;

  // Numerical conversions.
  UC_NUM_CONV(int, long)
  UC_NUM_CONV(int, float)
  UC_NUM_CONV(long, int)
  UC_NUM_CONV(long, float)
  UC_NUM_CONV(float, int)
  UC_NUM_CONV(float, long)

  // Conversions to string.
  UC_STR_CONV(int)
  UC_STR_CONV(long)
  UC_STR_CONV(float)

  // Conversions from string.
  UC_FROM_STR(int, std::stol)
  UC_FROM_STR(long, std::stoll)
  UC_FROM_STR(float, std::stod)

  // Boolean conversions.
  static UC_PRIMITIVE(string)
    UC_FUNCTION(boolean_to_string)(UC_PRIMITIVE(boolean) i) {
    return i ? "true" : "false";
  }

  static UC_PRIMITIVE(boolean)
    UC_FUNCTION(string_to_boolean)(UC_PRIMITIVE(string) i) {
    return i == "false" ? false : true;
  }

  // Built-in length() function. Takes a string and returns its length.
  static UC_PRIMITIVE(int) UC_FUNCTION(length)(UC_PRIMITIVE(string) s) {
    return static_cast<UC_PRIMITIVE(int)>(s.length());
  }

  // Built-in substr() function. Takes a string, a start, and a length
  // and returns the corresponding substring.
  static UC_PRIMITIVE(string) UC_FUNCTION(substr)(UC_PRIMITIVE(string) s,
                                                    UC_PRIMITIVE(int) start,
                                                    UC_PRIMITIVE(int) len) {
    return s.substr(start, len);
  }

  // Built-in ordinal() function. Takes a single-character string and
  // returns the ASCII value of the character.
  static UC_PRIMITIVE(int) UC_FUNCTION(ordinal)(UC_PRIMITIVE(string) s) {
    if (s.length() != 1) {
      return -1;
    }
    return static_cast<UC_PRIMITIVE(int)>(s[0]);
  }

  // Built-in character() function. Takes an ASCII value and returns a
  // a single-character string corresponding to that value. Returns an
  // empty string if the value is outside the range [1, 127].
  static UC_PRIMITIVE(string) UC_FUNCTION(character)(UC_PRIMITIVE(int) c) {
    if (c < 1 || c > 127) {
      return UC_PRIMITIVE(string)();
    }
    return UC_PRIMITIVE(string)() + static_cast<char>(c);
  }

  // Built-in pow() function. Raises a number to the power of another.
  static UC_PRIMITIVE(float) UC_FUNCTION(pow)(UC_PRIMITIVE(float) a,
                                                UC_PRIMITIVE(float) b) {
    return std::pow(a, b);
  }

  // Built-in sqrt() function. Computes the square root of a number.
  static UC_PRIMITIVE(float) UC_FUNCTION(sqrt)(UC_PRIMITIVE(float) i) {
    return std::sqrt(i);
  }

  // Built-in ceil() function. Rounds a number to the next highest
  // integer value.
  static UC_PRIMITIVE(float) UC_FUNCTION(ceil)(UC_PRIMITIVE(float) i) {
    return std::ceil(i);
  }

  // Built-in floor() function. Rounds a number to the next lowest
  // integer value.
  static UC_PRIMITIVE(float) UC_FUNCTION(floor)(UC_PRIMITIVE(float) i) {
    return std::floor(i);
  }

  // Built-in print() function. Takes a string and prints it to
  // standard out, without a trailing newline.
  static void UC_FUNCTION(print)(UC_PRIMITIVE(string) i) {
    std::cout << i;
  }

  // Built-in println() function. Takes a string and prints it to
  // standard out, with a trailing newline.
  static void UC_FUNCTION(println)(UC_PRIMITIVE(string) i) {
    std::cout << i << std::endl;
  }

  // Built-in peekchar() function. Returns the next character in
  // standard in. Returns an empty string if the stream is at EOF.
  static UC_PRIMITIVE(string) UC_FUNCTION(peekchar)() {
    char c[2] = { static_cast<char>(std::cin.peek()) };
    if (std::cin.eof()) {
      return "";
    } else {
      return UC_PRIMITIVE(string)(c);
    }
  }

  // Built-in readchar() function. Returns the next character in
  // standard in, removing it from the stream. Returns an empty string
  // if the stream is at EOF.
  static UC_PRIMITIVE(string) UC_FUNCTION(readchar)() {
    auto result = UC_FUNCTION(peekchar)();
    std::cin.get();
    return result;
  }

  // Built-in readline() function. Returns the line in standard in,
  // including the trailine newline if there is one. Returns an empty
  // string if the stream is at EOF.
  static UC_PRIMITIVE(string) UC_FUNCTION(readline)() {
    UC_PRIMITIVE(string) result;
    std::getline(std::cin, result);
    if (std::cin && !std::cin.eof()) {
      result.push_back('\n');
    }
    return result;
  }

} // namespace uc

#undef UC_NUM_CONV
#undef UC_STR_CONV
#undef UC_FROM_STR
#undef UC_INIT

#endif // UC_LIBRARY_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
