  // Forward type declarations

  struct UC_TYPEDEF(foo);
  struct UC_TYPEDEF(bar);
  struct UC_TYPEDEF(baz);
  // Forward function declarations

UC_PRIMITIVE(void)
  UC_FUNCTION(main)(UC_ARRAY(UC_PRIMITIVE(string)));
  // Full type definitions
//template<>
struct UC_TYPEDEF(foo) {
  // equality operator
  bool operator==(const UC_TYPEDEF(foo) &rhs) const {
  return UC_PRIMITIVE(foo) == rhs.UC_PRIMITIVE(foo)
  }
  // inequality operator
  bool operator!=(const UC_REFERENCE(foo) &rhs) const {
  return UC_PRIMITIVE(int) != rhs.UC_PRIMITIVE(int)
}
UC_REFERENCE(foo) : UC_PRIMITIVE(int)() {}
UC_REFERENCE(foo)(UC_PRIMITIVE(int) UC_VAR(x)) : UC_VARx{UC_VAR(x)}{}
};
struct UC_REFERENCE(bar) {
  // equality operator
  UC_PRIMITIVE(bool) operator==(const UC_REFERENCE(bar) &rhs) const {
  return UC_REFERENCE(foo) == rhs.UC_REFERENCE(foo) && UC_PRIMITIVE(int) == rhs.UC_PRIMITIVE(int) && UC_ARRAY(UC_PRIMITIVE(string)) == rhs.UC_ARRAY(UC_PRIMITIVE(string))
  }
  // inequality operator
  UC_PRIMITIVE(bool) operator!=(const UC_REFERENCE(bar) &rhs) const {
  return UC_REFERENCE(foo) != rhs.UC_REFERENCE(foo) || UC_PRIMITIVE(int) != rhs.UC_PRIMITIVE(int) || UC_ARRAY(UC_PRIMITIVE(string)) != rhs.UC_ARRAY(UC_PRIMITIVE(string))
}
UC_REFERENCE(bar)() : 

  UC_REFERENCE(foo)(), UC_PRIMITIVE(int)(), UC_ARRAY(UC_PRIMITIVE(string))()
{}
UC_REFERENCE(bar)(UC_REFERENCE(foo) UC_VAR(f), UC_PRIMITIVE(int) UC_VAR(x), UC_ARRAY(UC_PRIMITIVE(string)) UC_VAR(a)) : UC_VARf{UC_VAR(f)}, UC_VARx{UC_VAR(x)}, UC_VARa{UC_VAR(a)}{}
};
struct UC_REFERENCE(baz) {
  // equality operator
  UC_PRIMITIVE(bool) operator==(const UC_REFERENCE(baz) &rhs) const {
  return
  }
  // inequality operator
  UC_PRIMITIVE(bool) operator!=(const UC_REFERENCE(baz) &rhs) const {
  return
}
UC_REFERENCE(baz)() : 

  
{}
UC_REFERENCE(baz)() :{}
};
