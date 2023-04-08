#ifndef UC_REF_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
#define UC_REF_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7

/**
 * ref.hpp
 *
 * This file provides the implementation for uC references, as well as
 * operations on them.
 *
 * Project UID c49e54971d13f14fbc634d7a0fe4b38d421279e7
 */

#include <memory>
#include "defs.hpp"

namespace uc {

  // The class type representing a uC reference. It is built on top of
  // std::shared_ptr, which performs reference counting. The latter is
  // not used directly, since operations such as == are defined
  // differently in uC than they are in C++.
  template<class T>
  struct uc_reference : std::shared_ptr<T> {
    uc_reference() {}
    uc_reference(std::nullptr_t n) : std::shared_ptr<T>(n) {}
    template<class Y>
    explicit uc_reference(Y *ptr) : std::shared_ptr<T>(ptr) {}
    uc_reference(const std::shared_ptr<T> &sp) : std::shared_ptr<T>(sp) {}
    uc_reference(std::shared_ptr<T> &&sp) : std::shared_ptr<T>(sp) {}
  };

  // A function template to construct a uC object and wrap it in a uC
  // reference.
  template<class T, class... Args>
  T uc_make_object(Args&&... args) {
    return T(std::make_shared<typename T::element_type>(
      std::forward<Args>(args)...)
    );
  }

  // A class type for dispatching to the correct object-creation
  // function. This implementation is for standard uC objects, and the
  // specialization for uC arrays is in array.h.
  template<class T>
  struct uc_construct_dispatch {
    template<class... Args>
    static T construct(Args&&... args) {
      return T(std::make_shared<typename T::element_type>(
        std::forward<Args>(args)...
      ));
    }
  };

  // Generic construction of a uC array or user-defined object.
  // Dispatches to uc_construct_dispatch for the actual
  // implementation.
  template<class T, class... Args>
  T uc_construct(Args&&... args) {
    return uc_construct_dispatch<T>::construct(
      std::forward<Args>(args)...
    );
  }

  // Comparisons between two uC references. Two uC references are
  // equal if they are both null, or if the underlying objects have
  // the same contents.
  template<class T>
  bool operator==(const uc_reference<T> &p1, const uc_reference<T> &p2) {
    if (p1 == nullptr) {
      return p2 == nullptr;
    } else if (p2 == nullptr) {
      return false;
    }
    return *p1 == *p2;
  }

  template<class T>
  bool operator!=(const uc_reference<T> &p1, const uc_reference<T> &p2) {
    return !(p1 == p2);
  }

  // Comparisons between uC references and null-pointer literals.
  template<class T>
  bool operator==(const uc_reference<T> &p, std::nullptr_t) {
    return static_cast<const std::shared_ptr<T> &>(p) == nullptr;
  }

  template<class T>
  bool operator==(std::nullptr_t, const uc_reference<T> &p) {
    return static_cast<const std::shared_ptr<T> &>(p) == nullptr;
  }

  template<class T>
  bool operator!=(const uc_reference<T> &p, std::nullptr_t) {
    return static_cast<const std::shared_ptr<T> &>(p) != nullptr;
  }

  template<class T>
  bool operator!=(std::nullptr_t, const uc_reference<T> &p) {
    return static_cast<const std::shared_ptr<T> &>(p) != nullptr;
  }

} // namespace uc

#endif // UC_REF_HPP_c49e54971d13f14fbc634d7a0fe4b38d421279e7
