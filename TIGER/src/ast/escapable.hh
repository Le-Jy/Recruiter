/**
 ** \file ast/escapable.hh
 ** \brief Declaration of ast::Escapable.
 */

#pragma once

#include <ast/fwd.hh>

namespace ast
{
  /// Escapable.
  class Escapable
  {
  public:
    bool get_escaped() const;
    void set_escaped(const bool new_val);

    const FunctionDec* def_site_get() const;
    void def_site_set(FunctionDec* new_val);

  protected:
    bool escaped = true;
    FunctionDec* def_site = nullptr;
  };
} // namespace ast
#include <ast/escapable.hxx>
