#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  // Forward type declarations

  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
  // Full type definitions

  // Full function definitions

UC_PRIMITIVE(void) UC_FUNCTION(main) (UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args)){
  // decl local uC vars
  UC_PRIMITIVE(int) UC_VAR(f);
  UC_PRIMITIVE(int) UC_VAR(b);
  UC_PRIMITIVE(int) UC_VAR(z);
  // Block Body
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)((uc_add(1, 1)))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(int_to_string)((uc_add(1, 1.5)))); //Statement
UC_FUNCTION(println)((uc_add(1, "hello"s))); //Statement
UC_FUNCTION(println)((uc_add("hello"s, 1))); //Statement
UC_FUNCTION(println)((uc_add(true, "hello"s))); //Statement
UC_FUNCTION(println)((uc_add(false, "hello"s))); //Statement
UC_FUNCTION(println)((uc_add("Hello"s, true))); //Statement
UC_FUNCTION(println)((uc_add("Hello"s, false))); //Statement
}
} // namespace uc

int main(int argc, char **argv) {
  uc::UC_ARRAY(uc::UC_PRIMITIVE(string)) args = uc::uc_make_array_of<uc::UC_PRIMITIVE(string)>();
  for (int i = 1; i < argc; i++) {
    uc::uc_array_push(args, uc::UC_PRIMITIVE(string)(argv[i]));
  }
  uc::UC_FUNCTION(main)(args);
  return 0;
}
