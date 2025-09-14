/**
 ** \file ast/escapable.hxx
 ** \brief Inline methods of ast::Escapable.
 */

#pragma once

#include <ast/escapable.hh>

namespace ast
{
  inline bool Escapable::get_escaped() const { return escaped; }

  inline void Escapable::set_escaped(const bool new_val) { escaped = new_val; }

  inline const FunctionDec* Escapable::def_site_get() const { return def_site; }
  inline void Escapable::def_site_set(FunctionDec* new_val)
  {
    def_site = new_val;
  }
} // namespace ast
