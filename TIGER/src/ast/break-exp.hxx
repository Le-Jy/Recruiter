/**
 ** \file ast/break-exp.hxx
 ** \brief Inline methods of ast::BreakExp.
 */

#pragma once

#include <ast/break-exp.hh>

// Hint: this needs to be done at TC-3.

namespace ast
{
  // FIXED
  inline void BreakExp::def_set(Exp* exp) { this->def_ = exp; }
  // FIXED
  inline Exp* BreakExp::def_get() { return this->def_; }
  inline const Exp* BreakExp::def_get() const { return this->def_; }

} // namespace ast
