  // Forward type declarations

  struct UC_TYPEDEF(foo);
  struct UC_TYPEDEF(bar);
  struct UC_TYPEDEF(baz);
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
  UC_REFERENCE(foo) UC_VAR(f);
  UC_PRIMITIVE(int) UC_VAR(x);
  UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(a);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(bar) &rhs) const {
  return UC_VAR(f) == rhs.UC_VAR(f) && UC_VAR(x) == rhs.UC_VAR(x) && UC_VAR(a) == rhs.UC_VAR(a);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(bar) &rhs) const {
  return UC_VAR(f) != rhs.UC_VAR(f) || UC_VAR(x) != rhs.UC_VAR(x) || UC_VAR(a) != rhs.UC_VAR(a);
}
//default constructor
UC_TYPEDEF(bar)() : 

  UC_VAR(f)(), UC_VAR(x)(), UC_VAR(a)()
{}
//non default constructor
UC_TYPEDEF(bar)(UC_REFERENCE(foo) UC_VAR(f), UC_PRIMITIVE(int) UC_VAR(x), UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(a)) : UC_VAR(f){UC_VAR(f)}, UC_VAR(x){UC_VAR(x)}, UC_VAR(a){UC_VAR(a)}{}
};
struct UC_TYPEDEF(baz) {
  // member variable declaratons
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(baz) &rhs) const {
  return true;
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(baz) &rhs) const {
  return false;
}
};
