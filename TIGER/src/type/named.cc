/**
 ** \file type/named.cc
 ** \brief Implementation for type/named.hh.
 */

#include <set>

#include <type/named.hh>
#include <type/visitor.hh>
#include "misc/singleton.hh"

namespace type
{
  Named::Named(misc::symbol name)
    : name_(name)
    , type_(nullptr)
  {}

  Named::Named(misc::symbol name, const Type* type)
    : name_(name)
    , type_(type)
  {}

  // Inherited functions
  void Named::accept(ConstVisitor& v) const
  {
    // Done: Some code was deleted here.
    v(*this);
  }

  void Named::accept(Visitor& v)
  {
    // Done: Some code was deleted here.
    v(*this);
  }

  bool Named::sound() const
  {
    // FIXME: Some code was deleted here (Sound).
    auto typetest = this;
    typetest = dynamic_cast<const Named*>(typetest);
    while (typetest)
      {
        if (typetest == this)
          {
            return false;
          }
        typetest = dynamic_cast<const Named*>(typetest->type_);
      }
    return true;
  }

  bool Named::compatible_with(const Type& other) const
  {
    // FIXME: Some code was deleted here (Special implementation of "compatible_with" for Named).
    return this->actual().compatible_with(other);
  }

} // namespace type
