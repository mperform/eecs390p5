#include "defs.hpp"
#include "ref.hpp"
#include "array.hpp"
#include "library.hpp"
#include "expr.hpp"

namespace uc {

  // Forward type declarations

  struct UC_TYPEDEF(foo);
  struct UC_TYPEDEF(bar);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
  // Full type definitions

struct UC_TYPEDEF(foo) {
  // member variable declaratons
  UC_PRIMITIVE(int) UC_VAR(x);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) == rhs.UC_VAR(x);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) != rhs.UC_VAR(x);
}
//default constructor
UC_TYPEDEF(foo)() : 

  UC_VAR(x)()
{}
//non default constructor
UC_TYPEDEF(foo)(UC_PRIMITIVE(int) UC_VAR(x)) : UC_VAR(x){UC_VAR(x)}{}
};
struct UC_TYPEDEF(bar) {
  // member variable declaratons
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(bar) &rhs) const {
  return true;
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(bar) &rhs) const {
  return false;
}
};
  // Full function definitions

UC_PRIMITIVE(void) UC_FUNCTION(main) (UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(args)){
  // decl local uC vars
  UC_PRIMITIVE(int) UC_VAR(i);
  UC_PRIMITIVE(float) UC_VAR(f);
  // Block Body
(UC_VAR(i) = 3); //Statement
(UC_VAR(f) = 4.0); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((UC_VAR(i) == UC_VAR(i)))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((UC_VAR(f) != UC_VAR(f)))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((UC_VAR(i) == UC_VAR(f)))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((UC_VAR(i) != UC_VAR(f)))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(foo)>(3)
 == uc_construct<UC_REFERENCE(foo)>(3)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(foo)>(3)
 != uc_construct<UC_REFERENCE(foo)>(3)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(foo)>(3)
 == uc_construct<UC_REFERENCE(foo)>(4)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(foo)>(3)
 != uc_construct<UC_REFERENCE(foo)>(4)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(foo)>(3)
 == nullptr))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(foo)>(3)
 != nullptr))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
)
 == uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
)
 != uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(4)
)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
)
 != uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
, uc_construct<UC_REFERENCE(foo)>(4)
)
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
)
 == nullptr))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_ARRAY(UC_REFERENCE(foo))>(uc_construct<UC_REFERENCE(foo)>(3)
)
 != nullptr))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(bar)>()
 == uc_construct<UC_REFERENCE(bar)>()
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(bar)>()
 != uc_construct<UC_REFERENCE(bar)>()
))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(bar)>()
 == nullptr))); //Statement
UC_FUNCTION(println)(UC_FUNCTION(boolean_to_string)((uc_construct<UC_REFERENCE(bar)>()
 != nullptr))); //Statement
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
