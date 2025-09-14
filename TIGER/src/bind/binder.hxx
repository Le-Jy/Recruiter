/**
 ** \file bind/binder.hxx
 ** \brief Inline methods of bind::Binder.
 **/

// COMPLETED

#pragma once

#include <bind/binder.hh>

namespace bind
{
  inline void Binder::undefined_error(ast::Ast* e)
  {
    error_ << misc::error::error_type::bind;
    error_ << e->location_get() << ": undeclared ";

    if (ast::CallExp* call_exp = dynamic_cast<ast::CallExp*>(e);
        call_exp != nullptr)
      {
        error_ << "function: " << call_exp->name_get();
      }
    else if (ast::SimpleVar* simple_var = dynamic_cast<ast::SimpleVar*>(e);
             simple_var != nullptr)
      {
        error_ << "variable: " << simple_var->name_get() << "\n";
      }
    else if (ast::NameTy* name_type = dynamic_cast<ast::NameTy*>(e);
             name_type != nullptr)
      {
        error_ << "type: " << name_type->name_get() << "\n";
      }
  }

  inline void Binder::redefinition_error(ast::Dec* e, ast::Dec* first)
  {
    error_ << misc::error::error_type::bind;
    error_ << e->location_get() << ": redefinition: " << e->name_get() << "\n";
    error_ << first->location_get() << ": first definition\n";
  }

} // namespace bind
