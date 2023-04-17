#ifndef UC_EXPR_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
#define UC_EXPR_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7

/**
 * expr.hpp
 *
 * This file includes function template overloads for polymorphic
 * operations, specifically obtaining the id of an object, accessing
 * the length field of an object, and adding two values together.
 *
 * Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
 */

#include "array.hpp"
// #include "defs.hpp"
namespace uc {

  // Template for obtaining the id of an object.
  template<class T>
  UC_PRIMITIVE(long) uc_id(T ref) {
    auto ptr_val = reinterpret_cast<std::uintptr_t>(ref.get());
    return static_cast<UC_PRIMITIVE(long)>(ptr_val);
  }

  // Basic template for accessing the length field of a non-array
  // object.
  template<class T>
  auto uc_length_field(T ref) -> decltype(ref->UC_VAR(length)) & {
    return ref->UC_VAR(length);
  }

  // add your overloads here
  //arr a [] {1,2,3};
  //a.length -> 3

  // Define a special case of uc_length_field for arrays
  template <class T>
  auto uc_length_field(UC_ARRAY(T) ref) -> decltype(uc_array_length(ref)) {
    return uc_array_length(ref);
  }

  // define your overloads for uc_add() here
  //Numeric type + numeric type -(add values)-> numeric type
  //boolean + string -(concat)-> string
  //string + boolean -(concat)> string 
  //string + something -(concat)-> string 
  //something + string -(concat)-> string
  // string + string -(concat)-> string

  template<class T, class A>
  auto uc_add(T ref1, A ref2) -> decltype(ref1 + ref2){
    return ref1 + ref2;
  }

  template<class T>
  auto uc_add(UC_PRIMITIVE(string) ref1, UC_PRIMITIVE(string) ref2) -> decltype(ref1 + ref2){
    return ref1 + ref2;
  }

  template<class T>
  auto uc_add(UC_PRIMITIVE(string) ref1, T ref2) -> decltype(ref1 + std::to_string(ref2)){
    return ref1 + std::to_string(ref2);
  }

  template<class T>
  auto uc_add(T ref1, UC_PRIMITIVE(string) ref2) -> decltype(std::to_string(ref1) + ref2){
    return std::to_string(ref1) + ref2;
  }

  template<>
  auto uc_add(bool ref1, UC_PRIMITIVE(string) ref2) -> decltype(ucp_f_boolean_to_string(ref1) + ref2){
    return ucp_f_boolean_to_string(ref1) + ref2;
  }

  template<>
  auto uc_add(UC_PRIMITIVE(string) ref1, bool ref2) -> decltype(ref1 + ucp_f_boolean_to_string(ref2)){
    return ref1 + ucp_f_boolean_to_string(ref2);
  }
  // another one reversed
  
  
} // namespace uc

#endif // UC_EXPR_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
