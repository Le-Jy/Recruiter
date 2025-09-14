/**
 ** \file type/type-checker.cc
 ** \brief Implementation for type/type-checker.hh.
 */

#include <algorithm>
#include <iostream>
#include <memory>
#include <ranges>

#include <ast/all.hh>
#include <type/type-checker.hh>
#include <type/types.hh>
#include "ast/name-ty.hh"
#include "ast/seq-exp.hh"
#include "ast/simple-var.hh"
#include "ast/typable.hh"
#include "ast/var-dec.hh"
#include "type/array.hh"
#include "type/builtin-types.hh"
#include "type/function.hh"

namespace type
{
  TypeChecker::TypeChecker()
    : super_type()
    , error_()
  {}

  const Type* TypeChecker::type(ast::Typable& e)
  {
    // DONE: Some code was deleted here.

    auto t = &e.type_get();
    if (!t)
      {
        e.accept(*this);
      }
    return &e.type_get();
  }

  const Record* TypeChecker::type(const ast::fields_type& e)
  {
    auto res = new Record;
    // DONE: Some code was deleted here.
    for (auto field : e)
      {
        auto field_name = field->name_get();
        auto field_type = type(field->type_name_get());
        res->field_add(field_name, *field_type);
      }
    return res;
  }

  const Record* TypeChecker::type(const ast::VarChunk& e)
  {
    auto res = new Record;
    for (const auto& var : e)
      res->field_add(var->name_get(), *type(*var));

    return res;
  }

  const misc::error& TypeChecker::error_get() const { return error_; }

  /*-----------------.
  | Error handling.  |
  `-----------------*/

  void TypeChecker::error(const ast::Ast& ast, const std::string& msg)
  {
    error_ << misc::error::error_type::type << ast.location_get() << ": " << msg
           << std::endl;
  }

  void TypeChecker::type_mismatch(const ast::Ast& ast,
                                  const std::string& exp1,
                                  const Type& type1,
                                  const std::string& exp2,
                                  const Type& type2)
  {
    error_ << misc::error::error_type::type << ast.location_get()
           << ": type mismatch" << misc::incendl << exp1 << " type: " << type1
           << misc::iendl << exp2 << " type: " << type2 << misc::decendl;
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                const Type& type1,
                                const std::string& exp2,
                                const Type& type2)
  {
    // DONE: Some code was deleted here (Check for type mismatch).
    if (!type1.actual().compatible_with(type2.actual()))
      {
        type_mismatch(ast, exp1, type1, exp2, type2);
      }

    // If any of the type is Nil, set its `record_type_` to the other type.
    if (!error_)
      {
        // DONE: Some code was deleted here.
        auto niltype1 = dynamic_cast<const Nil*>(&type1.actual());
        auto niltype2 = dynamic_cast<const Nil*>(&type2.actual());
        if (niltype1)
          {
            niltype1->record_type_set(type2.actual());
          }
        else if (niltype2)
          {
            niltype2->record_type_set(type1.actual());
          }
      }
  }

  void TypeChecker::check_types(const ast::Ast& ast,
                                const std::string& exp1,
                                ast::Typable& type1,
                                const std::string& exp2,
                                ast::Typable& type2)
  {
    // Ensure evaluation order.
    type(type1);
    type(type2);
    // DONE: Some code was deleted here (Check types).
    if (!type1.type_get().actual().compatible_with(type2.type_get().actual()))
      {
        type_mismatch(ast, exp1, type1.type_get(), exp2, type2.type_get());
      }

    if (!error_)
      {
        // DONE: Some code was deleted here.
        auto niltype1 = dynamic_cast<const Nil*>(&type1.type_get().actual());
        auto niltype2 = dynamic_cast<const Nil*>(&type2.type_get().actual());
        if (niltype1)
          {
            niltype1->record_type_set(type2.type_get().actual());
          }
        else if (niltype2)
          {
            niltype2->record_type_set(type1.type_get().actual());
          }
      }
  }

  /*--------------------------.
  | The core of the visitor.  |
  `--------------------------*/

  /*-----------------.
  | Visiting /Var/.  |
  `-----------------*/

  void TypeChecker::operator()(ast::SimpleVar& e)
  {
    // DONE: Some code was deleted here.
    if (e.def_get())
      {
        type(*e.def_get());
        type_default(e, &e.def_get()->type_get());
      }
    else if (e.name_get() == "string")
      {
        type_default(e, &String::instance());
      }
    else if (e.name_get() == "int")
      {
        type_default(e, &Int::instance());
      }
  }

  // DONE: Some code was deleted here.
  void TypeChecker::operator()(ast::SubscriptVar& e)
  {
    type(e.var_get());
    if (&e.var_get().type_get() != nullptr)
      {
        auto temp =
          dynamic_cast<const Array*>(&e.var_get().type_get().actual());
        if (temp && type(e.index_get())->compatible_with(Int::instance()))
          {
            e.type_set(temp->type_get());
          }
        else
          {
            error(e, "error in typechecker for SubscriptVar");
            e.type_set(&Void::instance());
          }
      }
  }

  void TypeChecker::operator()(ast::FieldVar& e)
  {
    type(e.var_get());
    if (&e.type_get() == nullptr)
      e.type_set(&Void::instance());
    auto temp = dynamic_cast<const Record*>(&e.var_get().type_get().actual());
    if (temp)
      {
        e.type_set(temp->field_type(e.name_get()));
      }
    else
      {
        error(e, "error in typechecker for FieldVar");
      }
  }

  /*-----------------.
  | Visiting /Exp/.  |
  `-----------------*/

  // Literals.
  void TypeChecker::operator()(ast::NilExp& e)
  {
    auto nil_ptr = std::make_unique<Nil>();
    type_default(e, nil_ptr.get());
    created_type_default(e, nil_ptr.release());
  }

  void TypeChecker::operator()(ast::IntExp& e)
  {
    // DONE: Some code was deleted here.
    e.type_set(&Int::instance());
  }

  void TypeChecker::operator()(ast::StringExp& e)
  {
    // DONE: Some code was deleted here.
    e.type_set(&String::instance());
  }

  // Complex values.

  void TypeChecker::operator()(ast::RecordExp& e)
  {
    // FIXME: Some code was deleted here.
    auto cast2 = dynamic_cast<ast::Typable*>(&e.type_name_get());
    auto t = type(*cast2);
    e.type_set(t);
    //e.type_set(&Int::instance());
  }

  void TypeChecker::operator()(ast::OpExp& e)
  {
    // FIXME: Some code was deleted here.
    //error(e, "c'est moi");
    const Type* type_left = type(e.left_get());
    const Type* type_right = type(e.right_get());
    if (!type_right->compatible_with(*type_left)
        && !type_left->compatible_with(*type_right))
      {
        type_mismatch(e, "right operand", *type_right, "expected type",
                      *type_left);
      }
    e.type_set(&Int::instance());
  }

  void TypeChecker::operator()(ast::CastExp& e)
  {
    e.type_set(type(dynamic_cast<ast::Typable&>(e.ty_get())));
  }

  void TypeChecker::operator()(ast::IfExp& e)
  {
    const Type* test_type = type(e.test_get());
    const Type* then_type = type(e.thenclause_get());
    const Type* else_type = type(e.elseclause_get());

    // ici pour verifier si y'a un else ou pas -> si le cast foncionne il n'y en a pas
    auto test_cast = dynamic_cast<const ast::SeqExp*>(&e.elseclause_get());
    if (test_type && !test_type->compatible_with(Int::instance()))
      {
        if (test_type)
          type_mismatch(e, "test clause", *test_type, "expected",
                        Int::instance());
        else
          type_mismatch(e, "test clause", Void::instance(), "expected",
                        Int::instance());
      }
    // y'a un else mais pas le meme type avec then
    if (then_type && test_cast == nullptr
        && e.thenclause_get().type_get() != *else_type)
      {
        type_mismatch(e, "then clause", *then_type, "else clause", *else_type);
      }
    // y'a un else du meme type que then
    else if (then_type && test_cast == nullptr)
      e.type_set(then_type);
    // y'a pas de else
    else if (then_type && test_cast)
      {
        if (e.thenclause_get().type_get() != Void::instance())
          {
            type_mismatch(e, "then clause", *then_type, "expected",
                          Void::instance());
          }
        e.type_set(&Void::instance());
      }
  }

  // FIXME: Some code was deleted here.
  void TypeChecker::operator()(ast::SeqExp& e)
  {
    for (auto s : e.exps_get())
      {
        type(*s);
      }
    if (e.exps_get().size() == 0)
      {
        e.type_set(&Void::instance());
      }
    else
      {
        e.type_set(&e.exps_get()[e.exps_get().size() - 1]->type_get());
      }
  }

  void TypeChecker::operator()(ast::ForExp& e)
  {
    var_read_only_.insert(&e.vardec_get());

    auto vardec_type = type(e.vardec_get());
    auto hi_type = type(e.hi_get());
    auto body_type = type(e.body_get());
    if (dynamic_cast<ast::AssignExp*>(&e.body_get()))
      body_type = nullptr;
    if (!vardec_type
        || (vardec_type && !vardec_type->compatible_with(Int::instance())))
      {
        if (vardec_type)
          type_mismatch(e, "vardec clause", *vardec_type, "expected",
                        Int::instance());
        else
          type_mismatch(e, "vardec clause", Void::instance(), "expected",
                        Int::instance());
      }

    if (!hi_type->compatible_with(Int::instance()))
      {
        if (hi_type)
          type_mismatch(e, "hi clause", *hi_type, "expected", Int::instance());
        else
          type_mismatch(e, "hi clause", Void::instance(), "expected",
                        Int::instance());
      }

    if (!body_type
        || (body_type && !body_type->compatible_with(Void::instance())))
      {
        if (body_type)
          type_mismatch(e, "body clause", *body_type, "expected",
                        Void::instance());
      }
    e.type_set(&Void::instance());
  }

  void TypeChecker::operator()(ast::CallExp& e)
  {
    ast::VarChunk& args_dec = e.def_get()->formals_get();
    auto args_gived = e.args_get();
    auto nb_args_dec = args_dec.decs_get().size();
    auto nb_args_gived = args_gived.size();
    if (nb_args_dec < nb_args_gived)
      {
        error(e, "Too much args");
      }
    if (nb_args_dec > nb_args_gived)
      {
        error(e, "Not enough args");
      }
    for (size_t i = 0; i < nb_args_gived; i++)
      {
        type(*args_gived[i]);
        if (!args_dec[i]->type_get().compatible_with(
              args_gived[i]->type_get().actual()))
          {
            type_mismatch(e, "gived", args_gived[i]->type_get(), "expected",
                          args_dec[i]->type_get());
          }
      }
    if (e.def_get()->result_get())
      {
        e.type_set(type(*e.def_get()->result_get()));
      }
    else
      {
        e.type_set(&Void::instance());
      }
  }

  void TypeChecker::operator()(ast::BreakExp& e)
  {
    e.type_set(&Void::instance());
  }
  void TypeChecker::operator()(ast::AssignExp& e)
  {
    auto var_type = type(e.var_get());
    auto exp_type = type(e.exp_get());
    if (dynamic_cast<const ast::SimpleVar*>(&e.var_get()))
      {
        for (auto it = var_read_only_.begin(); it != var_read_only_.end(); it++)
          {
            if ((*it)->name_get()
                == dynamic_cast<const ast::SimpleVar*>(&e.var_get())
                     ->name_get())
              {
                error(e, "variable is read only");
              }
          }
      }
    if (e.exp_get().type_get() != e.var_get().type_get())
      {
        type_mismatch(e, "variable", *var_type, "expression", *exp_type);
      }
    e.type_set(&Void::instance());
  }

  void TypeChecker::operator()(ast::WhileExp& e)
  {
    auto test_type = type(e.test_get());
    auto body_type = type(e.body_get());
    if (!test_type->actual().compatible_with(Int::instance()))
      {
        if (test_type)
          type_mismatch(e, "test clause", *test_type, "expected",
                        Int::instance());
        else
          type_mismatch(e, "test clause", Void::instance(), "expected",
                        Int::instance());
      }
    if (body_type && !body_type->compatible_with(Void::instance()))
      {
        if (body_type)
          type_mismatch(e, "body clause", *body_type, "expected",
                        Void::instance());
        else
          type_mismatch(e, "body clause", Void::instance(), "expected",
                        Void::instance());
      }
    e.type_set(body_type);
  }

  void TypeChecker::operator()(ast::LetExp& e)
  {
    /*for (auto chunk : e.chunks_get())
    {
        // doing my own type cause no type for chunk
        chunk->accept(*this);
    }*/
    e.chunks_get().accept(*this);
    auto body_type = type(e.body_get());
    e.type_set(body_type);
  }

  void TypeChecker::operator()(ast::ArrayExp& e)
  {
    type(e.type_name_get());
    auto type_size = type(e.size_get());
    auto type_init = type(e.init_get());

    auto res = dynamic_cast<const Array*>(
      &(e.type_name_get().def_get()->type_get().actual()));

    if (*type_size != Int::instance())
      {
        type_mismatch(e, "size", *type_size, "expected", Int::instance());
      }
    if (!e.init_get().type_get().actual().compatible_with(
          res->type_get()->actual()))
      {
        type_mismatch(e, "init", *type_init, "expected",
                      res->type_get()->actual());
      }
    e.type_set(res);
  }

  /*-----------------.
  | Visiting /Dec/.  |
  `-----------------*/

  /*------------------------.
  | Visiting FunctionChunk. |
  `------------------------*/

  void TypeChecker::operator()(ast::FunctionChunk& e)
  {
    chunk_visit<ast::FunctionDec>(e);
  }

  void TypeChecker::operator()(ast::FunctionDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store the type of this function.
  template <>
  void TypeChecker::visit_dec_header<ast::FunctionDec>(ast::FunctionDec& e)
  {
    // FIXME: Some code was deleted here.
    if (e.result_get())
      {
        Function* t =
          new Function(type(e.formals_get()), *type(*e.result_get()));
        e.type_set(t);
        e.build_type_set(t);
      }
    else
      {
        Function* t = new Function(type(e.formals_get()), Void::instance());
        e.type_set(t);
        e.build_type_set(t);
      }
  }

  // Type check this function's body.
  template <>
  void TypeChecker::visit_dec_body<ast::FunctionDec>(ast::FunctionDec& e)
  {
    if (e.body_get())
      visit_routine_body<Function>(e);
  }

  /*---------------.
  | Visit VarDec.  |
  `---------------*/

  void TypeChecker::operator()(ast::VarDec& e)
  {
    auto init_type = e.init_get();
    auto name_type = e.type_name_get();
    if (init_type)
      {
        init_type->accept(*this);
        if (!name_type)
          {
            e.type_set(&init_type->type_get());
          }
        else if (!name_type->def_get())
          {
            if (name_type->name_get() == "int")
              {
                e.type_set(&Int::instance());
              }
            else if (name_type->name_get() == "string")
              {
                e.type_set(&String::instance());
              }
            if (!e.type_get().compatible_with(init_type->type_get()))
              type_mismatch(e, "var declaration", e.type_get(), "var init",
                            init_type->type_get());
          }
      }
    else if (name_type)
      {
        name_type->accept(*this);
        e.type_set(&name_type->type_get());
      }
    else
      {
        e.type_set(&Void::instance());
      }
  }

  /*--------------------.
  | Visiting TypeChunk. |
  `--------------------*/

  void TypeChecker::operator()(ast::TypeChunk& e)
  {
    chunk_visit<ast::TypeDec>(e);
  }

  void TypeChecker::operator()(ast::TypeDec&)
  {
    // We must not be here.
    unreachable();
  }

  // Store this type.
  template <> void TypeChecker::visit_dec_header<ast::TypeDec>(ast::TypeDec& e)
  {
    // We only process the head of the type declaration, to set its
    // name in E.  A declaration has no type in itself; here we store
    // the type declared by E.
    // FIXME: Some code was deleted here.
    auto name = new Named(e.name_get());
    e.build_type_set(name);
    e.type_set(name);
  }

  // Bind the type body to its name.
  template <> void TypeChecker::visit_dec_body<ast::TypeDec>(ast::TypeDec& e)
  {
    // FIXME: Some code was deleted here.
    auto tmp = dynamic_cast<const type::Named*>(&e.type_get());
    dynamic_cast<const type::Named*>(&e.type_get())->type_set(type(e.ty_get()));
    /*
    if (!tmp->sound())
      error(e, "gnegne recusif");*/
  }

  /*------------------.
  | Visiting /Chunk/. |
  `------------------*/

  template <class D> void TypeChecker::chunk_visit(ast::Chunk<D>& e)
  {
    // FIXME: Some code was deleted here.
    for (size_t i = 0; i < e.decs_get().size(); i++)
      {
        visit_dec_header<D>(*e.decs_get()[i]);
      }
    for (size_t i = 0; i < e.decs_get().size(); i++)
      {
        visit_dec_body<D>(*e.decs_get()[i]);
      }
  }

  /*-------------.
  | Visit /Ty/.  |
  `-------------*/

  void TypeChecker::operator()(ast::NameTy& e)
  {
    // DONE: Some code was deleted here (Recognize user defined types, and built-in types).
    if (e.name_get() == "int")
      {
        e.type_set(&Int::instance());
      }
    else if (e.name_get() == "string")
      {
        e.type_set(&String::instance());
      }
    else
      {
        e.type_set(&e.def_get()->type_get());
      }
  }

  void TypeChecker::operator()(ast::RecordTy& e)
  {
    auto tmp = e.fields_get(); // debug purposes
    auto tmpbis = type(tmp);
    e.type_set(tmpbis);
    e.build_type_set(tmpbis);
    // FIXME: Some code was deleted here.
  }

  void TypeChecker::operator()(ast::ArrayTy& e)
  {
    // FIXME: Some code was deleted here.
    e.base_type_get().accept(*this);
    type_default(e, new Array(&e.base_type_get().type_get()));
  }

} // namespace type
