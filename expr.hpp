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

  // define your overloads for uc_add() here

} // namespace uc

#endif // UC_EXPR_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
