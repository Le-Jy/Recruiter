/**
 ** \file ast/method-call-exp.hxx
 ** \brief Inline methods of ast::MethodCallExp.
 */

#pragma once

#include <ast/method-call-exp.hh>
#include "ast/method-dec.hh"

namespace ast
{

  inline const Var& MethodCallExp::object_get() const { return *object_; }
  inline Var& MethodCallExp::object_get() { return *object_; }

  // FIXED.
  inline void MethodCallExp::def_set(MethodDec* methoddec)
  {
    this->def_ = methoddec;
  }
  // FIXED
  inline MethodDec* MethodCallExp::def_get() { return this->def_; }
  inline const MethodDec* MethodCallExp::def_get() const { return this->def_; }

} // namespace ast
