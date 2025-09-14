/**
 ** \file ast/call-exp.hxx
 ** \brief Inline methods of ast::CallExp.
 */

#pragma once

#include <ast/call-exp.hh>
#include "ast/function-dec.hh"

namespace ast
{

  inline misc::symbol CallExp::name_get() const { return name_; }
  inline void CallExp::name_set(misc::symbol name) { name_ = name; }

  inline const exps_type& CallExp::args_get() const { return *args_; }
  inline exps_type& CallExp::args_get() { return *args_; }

  // FIXED
  inline void CallExp::def_set(FunctionDec* exp) { this->def_ = exp; }
  // FIXED
  inline const FunctionDec* CallExp::def_get() const { return this->def_; }
  inline FunctionDec* CallExp::def_get() { return this->def_; }

} // namespace ast
