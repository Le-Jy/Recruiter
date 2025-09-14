/**
 ** \file escapes/escapes-visitor.cc
 ** \brief Implementation for escapes/escapes-visitor.hh.
 */

#include <ast/all.hh>
#include <escapes/escapes-visitor.hh>
#include <misc/contract.hh>

namespace escapes
{

  void EscapesVisitor::operator()(ast::SimpleVar& e)
  {
    auto scope_nb = scoped_map.get(e.def_get());
    if (scope_nb != actual_scope)
      e.def_get()->set_escaped(true);
  }

  void EscapesVisitor::operator()(ast::FunctionDec& e)
  {
    ast::FunctionDec* prev = current_fun;
    current_fun = &e;
    scoped_map.scope_begin();
    actual_scope++;
    super_type::operator()(e);
    scoped_map.scope_end();
    actual_scope--;
    current_fun = prev;
  }

  void EscapesVisitor::operator()(ast::VarDec& e)
  {
    scoped_map.put(&e, actual_scope);
    e.set_escaped(false);
    e.def_site_set(current_fun);
  }

} // namespace escapes
