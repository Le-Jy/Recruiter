/**
 ** \file ast/type-constructor.hxx
 ** \brief Inline methods of ast::TypeConstructor.
 */

#pragma once

#include <ast/type-constructor.hh>
#include <type/types.hh>

namespace ast
{
  // DONE
  inline const type::Type& TypeConstructor::build_type_get() const
  {
    return *build_type_;
  }
  inline const type::Type& TypeConstructor::build_type_get()
  {
    return *build_type_;
  }
  inline void TypeConstructor::build_type_set(type::Type* buildType)
  {
    build_type_ = buildType;
  }
  inline void TypeConstructor::build_type_set(const type::Type* buildType)
  {
    build_type_ = buildType;
  }
} // namespace ast
