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
  // Block Body
UC_FUNCTION(println)((uc_add(""s, false))); //Statement
UC_FUNCTION(println)((uc_add(""s, true))); //Statement
UC_FUNCTION(println)((uc_add(""s, "hello"s))); //Statement
UC_FUNCTION(println)((uc_add(""s, 3))); //Statement
UC_FUNCTION(println)((uc_add(""s, 31415926535L))); //Statement
UC_FUNCTION(println)((uc_add(""s, 3.0))); //Statement
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
