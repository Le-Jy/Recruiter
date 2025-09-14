/**
 ** \file bind/renamer.cc
 ** \brief Implementation of bind::Renamer.
 */

#include <bind/renamer.hh>

namespace bind
{
  using namespace ast;

  // OK: Some code was deleted here.
  Renamer::Renamer()
    : super_type()
    , names_()
  {}

  void Renamer::operator()(ast::VarDec& e) { Renamer::visit(e, &e); }

  void Renamer::operator()(ast::FunctionDec& e) { Renamer::visit(e, &e); }

  void Renamer::operator()(ast::TypeDec& e) { Renamer::visit(e, &e); }

  void Renamer::operator()(ast::SimpleVar& e)
  {
    Renamer::visit(e, e.def_get());
  }

  void Renamer::operator()(ast::CallExp& e) { Renamer::visit(e, e.def_get()); }

  void Renamer::operator()(ast::NameTy& e) { Renamer::visit(e, e.def_get()); }

} // namespace bind
