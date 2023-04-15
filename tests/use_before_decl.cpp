  // Forward type declarations

  struct UC_TYPEDEF(foo);
  struct UC_TYPEDEF(baz);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
UC_PRIMITIVE(void)
  UC_FUNCTION(bar)(UC_REFERENCE(foo));
  // Full type definitions

struct UC_TYPEDEF(foo) {
  // member variable declaratons
  UC_REFERENCE(baz) UC_VAR(b);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(b) == rhs.UC_VAR(b);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(b) != rhs.UC_VAR(b);
}
//default constructor
UC_TYPEDEF(foo)() : 

  UC_VAR(b)()
{}
//non default constructor
UC_TYPEDEF(foo)(UC_REFERENCE(baz) UC_VAR(b)) : UC_VAR(b){UC_VAR(b)}{}
};
struct UC_TYPEDEF(baz) {
  // member variable declaratons
  UC_PRIMITIVE(string) UC_VAR(s);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(baz) &rhs) const {
  return UC_VAR(s) == rhs.UC_VAR(s);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(baz) &rhs) const {
  return UC_VAR(s) != rhs.UC_VAR(s);
}
//default constructor
UC_TYPEDEF(baz)() : 

  UC_VAR(s)()
{}
//non default constructor
UC_TYPEDEF(baz)(UC_PRIMITIVE(string) UC_VAR(s)) : UC_VAR(s){UC_VAR(s)}{}
};
