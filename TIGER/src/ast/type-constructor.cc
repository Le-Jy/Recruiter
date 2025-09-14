/**
 ** \file ast/type-constructor.cc
 ** \brief Implementation of ast::TypeConstructor.
 */

#include <ast/type-constructor.hh>
#include <ast/visitor.hh>

namespace ast
{
  // DONE
  TypeConstructor::TypeConstructor(type::Type* build_type)
    : build_type_(build_type)
  {}
} // namespace ast
