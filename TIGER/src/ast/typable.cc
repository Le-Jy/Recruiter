/**
 ** \file ast/typable.cc
 ** \brief Implementation of ast::Typable.
 */

#include <ast/typable.hh>
#include <ast/visitor.hh>

namespace ast
{
  // DONE
  Typable::Typable(type::Type* type)
    : type_(type)
  {}
} // namespace ast
