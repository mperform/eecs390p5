  // Forward type declarations

  struct UC_TYPEDEF(foo);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
UC_PRIMITIVE(void)
  UC_FUNCTION(bar)(UC_REFERENCE(foo));
  // Full type definitions

struct UC_TYPEDEF(foo) {
  // member variable declaratons
  UC_PRIMITIVE(int) UC_VAR(x);
  UC_PRIMITIVE(string) UC_VAR(length);
  // equality operator
  UC_PRIMITIVE(boolean) operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) == rhs.UC_VAR(x) && UC_VAR(length) == rhs.UC_VAR(length);
  }
  // inequality operator
  UC_PRIMITIVE(boolean) operator!=(const UC_TYPEDEF(foo) &rhs) const {
  return UC_VAR(x) != rhs.UC_VAR(x) || UC_VAR(length) != rhs.UC_VAR(length);
}
//default constructor
UC_TYPEDEF(foo)() : 

  UC_VAR(x)(), UC_VAR(length)()
{}
//non default constructor
UC_TYPEDEF(foo)(UC_PRIMITIVE(int) UC_VAR(x), UC_PRIMITIVE(string) UC_VAR(length)) : UC_VAR(x){UC_VAR(x)}, UC_VAR(length){UC_VAR(length)}{}
};
