/**
 ** \file bind/renamer.hxx
 ** \brief Template methods of bind::Renamer.
 */

#pragma once

#include <bind/renamer.hh>

namespace bind
{
  // OK: Some code was deleted here.
  template <class Def> misc::symbol Renamer::new_name(const Def& e)
  {
    if (!names_.contains(&e))
      names_[&e] = e.name_get().fresh(e.name_get());

    return names_[&e];
  }

  inline misc::symbol Renamer::new_name(const ast::FunctionDec& e)
  {
    if (!e.body_get() || e.name_get().get() == "_main")
      return e.name_get();

    if (!names_.contains(&e))
      names_[&e] = e.name_get().fresh(e.name_get());

    return names_[&e];
  }

  template <class E, class Def> void Renamer::visit(E& e, const Def* def)
  {
    super_type::operator()(e);
    if (def == nullptr)
      return;

    e.name_set(new_name(*def));
  }
} // namespace bind
