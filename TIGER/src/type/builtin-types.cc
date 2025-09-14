/**
 ** \file type/builtin-types.cc
 ** \brief Implementation for type/builtin-types.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/visitor.hh>
#include "misc/singleton.hh"

namespace type
{
  // FIXME: Some code was deleted here (Int, String, Void).
  const Type& Int::actual() const
  {
    return *this; // TO remove or not
  }

  void Int::accept(ConstVisitor& v) const { v(*this); }
  void Int::accept(Visitor& v) { v(*this); }

  const Type& String::actual() const
  {
    // TODO when singleton is implemented
    return *this; // TO remove or not
  }

  void String::accept(ConstVisitor& v) const { v(*this); }
  void String::accept(Visitor& v) { v(*this); }

  const Type& Void::actual() const
  {
    // TODO when singleton is implemented
    return *this; // TO remove or not
  }

  void Void::accept(ConstVisitor& v) const { v(*this); }
  void Void::accept(Visitor& v) { v(*this); }

} // namespace type
