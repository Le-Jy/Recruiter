/**
 ** \file type/type-checker.hxx
 ** \brief Inline methods of type::TypeChecker.
 */

#pragma once

#include <iostream>
#include <ast/all.hh>
#include <type/pretty-printer.hh>
#include <type/type-checker.hh>
#include <type/types.hh>

namespace type
{
  namespace
  {
    const Nil nil_error_instance{};

  }

  /*----------------.
  | Setting types.  |
  `----------------*/

  template <typename NodeType>
  void TypeChecker::type_default(NodeType& e, const type::Type* type)
  {
    // DONE
    if (!&e.type_get())
      e.type_set(type);
  }

  template <typename NodeType>
  void TypeChecker::created_type_default(NodeType& e, const type::Type* type)
  {
    // DONE
    if (&e.build_type_get() != nullptr)
      e.build_type_set(type);
  }

  template <typename NodeType>
  void TypeChecker::type_set(NodeType& e, const type::Type* type)
  {
    // DONE (Basically e.type_set(type)).
    e.type_set(type);
  }

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  template <typename T>
  void
  TypeChecker::error(const ast::Ast& ast, const std::string& msg, const T& exp)
  {
    error_ << misc::error::error_type::type << ast.location_get() << ": " << msg
           << ": " << exp << std::endl;
  }

  template <typename T, typename U>
  void
  TypeChecker::error_and_recover(T& loc, const std::string& msg, const U& exp)
  {
    error(loc, msg, exp);
    loc.type_set(&nil_error_instance);
  }

  template <typename NodeType>
  void TypeChecker::check_type(NodeType& e,
                               const std::string& s,
                               const Type& expected)
  {
    // FIXME: Some code was deleted here.
    if (!expected.compatible_with(e.type_get()))
      {
        error(e, s);
      }
  }

  /*------------.
  | Functions.  |
  `------------*/

  template <typename Routine_Type, typename Routine_Node>
  void TypeChecker::visit_routine_body(Routine_Node& e)
  {
    // DONE
    if (e.body_get())
      {
        // je visite
        type(*e.body_get());
        // je verifie
        auto cast = dynamic_cast<const Routine_Type*>(&e.type_get());
        if (cast && cast->result_get() != Void::instance())
          {
            check_types(e, "the result type", cast->result_get(),
                        "the body type", e.body_get()->type_get());
          }
      }
  }

} // namespace type
