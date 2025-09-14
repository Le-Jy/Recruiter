/**
 ** \file bind/binder.cc
 ** \brief Implementation for bind/binder.hh.
 */

#include <ast/all.hh>
#include <bind/binder.hh>

#include <misc/contract.hh>

namespace bind
{
  /*-----------------.
  | Error handling.  |
  `-----------------*/

  /// The error handler.
  const misc::error& Binder::error_get() const { return error_; }

  Binder::Binder() { scope_begin(); }
  Binder::~Binder() { scope_end(); }

  void Binder::operator()(ast::LetExp& e)
  {
    scope_begin();
    super_type::operator()(e);
    scope_end();
  }

  void Binder::operator()(ast::ForExp& e)
  {
    auto last_loop = current_loop;
    current_loop = &e;

    scope_begin();
    var_map.put(e.vardec_get().name_get(), &(e.vardec_get()));
    super_type::operator()(e);
    scope_end();

    current_loop = last_loop;
  }

  void Binder::operator()(ast::WhileExp& e)
  {
    auto last_loop = current_loop;
    current_loop = &e;

    scope_begin();
    super_type::operator()(e);
    scope_end();

    current_loop = last_loop;
  }

  void Binder::operator()(ast::BreakExp& e)
  {
    if (current_loop != nullptr)
      {
        e.def_set(current_loop);
      }
    else
      {
        error_ << misc::error::error_type::bind;
        error_ << e.location_get();
        error_ << ": `break' outside any loop\n";
      }
  }

  void Binder::operator()(ast::VarChunk& e)
  {
    std::map<misc::symbol, ast::VarDec*> chunk_map;
    for (ast::VarDec* dec : e)
      {
        if (auto prev = chunk_map.find(dec->name_get());
            prev != chunk_map.end())
          {
            redefinition_error(dec, prev->second);
          }
        else
          {
            var_map.put(dec->name_get(), dec);
            chunk_map.insert({dec->name_get(), dec});
          }
      }

    for (const auto& dec : e)
      {
        scope_begin();
        dec->accept(*this);
        scope_end();
      }
  }

  void Binder::operator()(ast::FunctionChunk& e)
  {
    std::map<misc::symbol, ast::FunctionDec*> chunk_map;
    for (ast::FunctionDec* dec : e)
      {
        if (main_checked != nullptr
            && dec->name_get().get().compare("_main") == 0)

          {
            redefinition_error(dec, main_checked);
          }

        else if (dec->name_get().get().compare("_main") == 0)
          {
            main_checked = dec;
          }

        if (auto prev = chunk_map.find(dec->name_get());
            prev != chunk_map.end())
          {
            redefinition_error(dec, prev->second);
          }
        else
          {
            function_map.put(dec->name_get(), dec);
            chunk_map.insert({dec->name_get(), dec});
          }
      }
    for (const auto& dec : e)
      {
        scope_begin();
        dec->accept(*this);
        scope_end();
      }
  }

  void Binder::operator()(ast::TypeChunk& e)
  {
    std::map<misc::symbol, ast::TypeDec*> chunk_map;

    for (ast::TypeDec* dec : e)
      {
        if (auto prev = chunk_map.find(dec->name_get());
            prev != chunk_map.end())
          {
            redefinition_error(dec, prev->second);
          }
        else
          {
            types_map.put(dec->name_get(), dec);
            chunk_map.insert({dec->name_get(), dec});
          }
      }

    for (const auto& dec : e)
      {
        scope_begin();
        dec->accept(*this);
        scope_end();
      }
  }

  void Binder::operator()(ast::SimpleVar& e)
  {
    auto def = var_map.get(e.name_get());
    if (!def)
      undefined_error(&e);
    else
      {
        e.def_set(def);
        super_type::operator()(e);
      }
  }

  void Binder::operator()(ast::CallExp& e)
  {
    auto def = function_map.get(e.name_get());
    if (!def)
      undefined_error(&e);
    else
      {
        e.def_set(def);
        super_type::operator()(e);
      }
  }

  void Binder::operator()(ast::NameTy& e)
  {
    auto def = types_map.get(e.name_get());
    auto type_str = e.name_get().get();
    if (!def && type_str.compare("string") != 0 && type_str.compare("int") != 0)
      undefined_error(&e);
    else
      {
        e.def_set(def);
        super_type::operator()(e);
      }
  }

  void Binder::scope_begin()
  {
    types_map.scope_begin();
    function_map.scope_begin();
    var_map.scope_begin();
  }
  void Binder::scope_end()
  {
    types_map.scope_end();
    function_map.scope_end();
    var_map.scope_end();
  }

} // namespace bind
