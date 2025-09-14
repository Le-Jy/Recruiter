/**
 ** \file ast/pretty-printer.cc
 ** \brief Implementation of ast::PrettyPrinter.
 */

#include "pretty-printer.hh"
#include <ast/all.hh>
#include <ast/libast.hh>
#include <ast/pretty-printer.hh>
#include <misc/escape.hh>
#include <misc/indent.hh>
#include <misc/separator.hh>

#include <iostream>
#include <type/class.hh>

namespace ast
{
  // Anonymous namespace: these functions are private to this file.
  namespace
  {
    /// Output \a e on \a ostr.
    inline std::ostream& operator<<(std::ostream& ostr, const Escapable& e)
    {
      if (escapes_display(ostr) && e.get_escaped())
        ostr << "/* escaping */ ";

      return ostr;
    }

    /// \brief Output \a e on \a ostr.
    ///
    /// Used to factor the output of the name declared,
    /// and its possible additional attributes.
    inline std::ostream& operator<<(std::ostream& ostr, const Dec& e)
    {
      ostr << e.name_get();
      if (bindings_display(ostr))
        ostr << " /* " << &e << " */";
      return ostr;
    }
  } // namespace

  PrettyPrinter::PrettyPrinter(std::ostream& ostr)
    : ostr_(ostr)
  {}

  void PrettyPrinter::operator()(const SimpleVar& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const FieldVar& e)
  {
    //COMPLETED
    ostr_ << e.var_get();
    ostr_ << "." << e.name_get();
  }

  /* Foo[10]. */
  void PrettyPrinter::operator()(const SubscriptVar& e)
  {
    ostr_ << e.var_get() << '[' << e.index_get() << ']';
  }

  void PrettyPrinter::operator()(const CastExp& e)
  {
    ostr_ << "_cast(" << e.exp_get() << ", " << e.ty_get() << ')';
  }

  // COMPLETED

  void PrettyPrinter::operator()(const NilExp& e) { ostr_ << "nil"; }

  void PrettyPrinter::operator()(const IntExp& e) { ostr_ << e.value_get(); }

  void PrettyPrinter::operator()(const StringExp& e)
  {
    ostr_ << '"' << misc::escape(e.value_get()) << '"';
  }

  void PrettyPrinter::operator()(const CallExp& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";

    ostr_ << '(';
    const auto& args = e.args_get();
    if (args.size() > 0)
      {
        for (size_t i = 0; i < args.size() - 1; i++)
          {
            ostr_ << *(args[i]) << ", ";
          }
        ostr_ << *(args[args.size() - 1]);
      }

    ostr_ << ')';
  }

  void PrettyPrinter::operator()(const OpExp& e)
  {
    ostr_ << '(' << e.left_get() << ' ' << str(e.oper_get()) << ' '
          << e.right_get() << ')';
  }

  void PrettyPrinter::operator()(const RecordExp& e)
  {
    ostr_ << e.type_name_get();
    ostr_ << '{';

    const auto& fields = e.fields_get();

    if (fields.size() > 0)
      {
        for (size_t i = 0; i < fields.size() - 1; i++)
          {
            ostr_ << *(fields[i]) << ", ";
          }
        ostr_ << *(fields[fields.size() - 1]);
      }

    ostr_ << '}';
  }

  void PrettyPrinter::operator()(const SeqExp& e)
  {
    ostr_ << "(" << misc::incindent;

    const auto& exps = e.exps_get();

    if (exps.size() > 0)
      {
        for (size_t i = 0; i < exps.size() - 1; i++)
          {
            ostr_ << misc::iendl << *(exps[i]) << ";";
          }

        ostr_ << misc::iendl << *(exps[exps.size() - 1]);
        ostr_ << misc::decendl << ")";
      }
    else
      ostr_ << misc::decindent << ")";
  }

  void PrettyPrinter::operator()(const AssignExp& e)
  {
    ostr_ << e.var_get() << " := " << e.exp_get();
  }

  void PrettyPrinter::operator()(const IfExp& e)
  {
    ostr_ << "(if " << e.test_get() << misc::incendl;
    ostr_ << "then " << e.thenclause_get() << misc::iendl;
    ostr_ << "else " << e.elseclause_get() << ")" << misc::decindent;
  }

  void PrettyPrinter::operator()(const WhileExp& e)
  {
    ostr_ << "while ";

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    ostr_ << e.test_get() << " do" << misc::incendl;
    ostr_ << e.body_get() << misc::decindent;
  }

  void PrettyPrinter::operator()(const ForExp& e)
  {
    ostr_ << "for ";

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    ostr_ << e.vardec_get().name_get();

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e.vardec_get() << " */";

    ostr_ << " := " << *(e.vardec_get().init_get()) << " to " << e.hi_get()
          << " do" << misc::incendl;

    ostr_ << e.body_get() << misc::decindent;
  }

  void PrettyPrinter::operator()(const BreakExp& e)
  {
    ostr_ << "break";
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const LetExp& e)
  {
    ostr_ << "let" << misc::incendl;
    ostr_ << e.chunks_get() << misc::decendl;
    ostr_ << "in" << misc::incendl;
    ostr_ << e.body_get() << misc::decendl;
    ostr_ << "end";
  }

  void PrettyPrinter::operator()(const ArrayExp& e)
  {
    ostr_ << e.type_name_get();
    ostr_ << "[" << e.size_get() << "] of " << e.init_get();
  }

  void PrettyPrinter::operator()(const FieldInit& e)
  {
    ostr_ << e.name_get() << " = " << e.init_get();
  }

  void PrettyPrinter::operator()(const ChunkList& e)
  {
    for (const auto& chunk : e.chunks_get())
      {
        ostr_ << *chunk;
      }
  }

  void PrettyPrinter::operator()(const ChunkInterface& e) { ostr_ << e; }

  void PrettyPrinter::operator()(const VarChunk& e)
  {
    chunk_visit<VarChunk>(e);
  }

  void PrettyPrinter::operator()(const VarDec& e)
  {
    ostr_ << "var ";
    if (escapes_display(ostr_) && e.get_escaped())
      ostr_ << "/* escaping */ ";
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    if (e.type_name_get() != nullptr)
      {
        ostr_ << " : " << *e.type_name_get();
      }
    if (e.init_get() != nullptr)
      {
        ostr_ << " := " << *e.init_get();
      }
    ostr_ << misc::iendl;
  }

  void PrettyPrinter::operator()(const FunctionChunk& e)
  {
    chunk_visit<FunctionChunk>(e);
  }

  void PrettyPrinter::operator()(const FunctionDec& e)
  {
    if (!e.body_get())
      ostr_ << "primitive " << e.name_get();
    else
      ostr_ << "function " << e.name_get();

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    ostr_ << '(';

    const auto& formals = e.formals_get();
    for (const auto& vardec : e.formals_get())
      {
        if (escapes_display(ostr_) && vardec->get_escaped())
          ostr_ << "/* escaping */ ";

        ostr_ << vardec->name_get();

        if (bindings_display(ostr_))
          ostr_ << " /* " << vardec << " */";

        if (vardec->type_name_get() != nullptr)
          ostr_ << " : " << *vardec->type_name_get();

        if (vardec != formals.decs_get().back())
          ostr_ << ", ";
      }

    ostr_ << ')';

    if (e.result_get())
      {
        ostr_ << " : " << *e.result_get();
      }
    if (e.body_get())
      {
        ostr_ << " = " << misc::incendl;
        ostr_ << *e.body_get() << misc::decendl;
      }
    else
      ostr_ << misc::iendl;
  }

  void PrettyPrinter::operator()(const TypeChunk& e)
  {
    chunk_visit<TypeChunk>(e);
  }

  void PrettyPrinter::operator()(const TypeDec& e)
  {
    ostr_ << "type " << e.name_get();

    if (bindings_display(ostr_))
      ostr_ << " /* " << &e << " */";

    ostr_ << " = " << e.ty_get() << misc::iendl;
  }

  void PrettyPrinter::operator()(const NameTy& e)
  {
    ostr_ << e.name_get();
    if (bindings_display(ostr_))
      ostr_ << " /* " << e.def_get() << " */";
  }

  void PrettyPrinter::operator()(const RecordTy& e)
  {
    ostr_ << '{' << misc::incendl;

    const auto& fields = e.fields_get();

    if (fields.size() > 0)
      {
        for (size_t i = 0; i < fields.size() - 1; i++)
          {
            ostr_ << *(fields[i]) << ", ";
          }
        ostr_ << *(fields[fields.size() - 1]);
      }
    ostr_ << misc::decendl << '}';
  }

  void PrettyPrinter::operator()(const ArrayTy& e)
  {
    ostr_ << "array of " << e.base_type_get();
  }

  void PrettyPrinter::operator()(const Field& e)
  {
    ostr_ << e.name_get() << " : " << e.type_name_get();
  }

  void PrettyPrinter::operator()(const ClassTy& e)
  {
    ostr_ << "class extends ";
    ostr_ << e.super_get() << misc::iendl;

    ostr_ << '{' << misc::incendl << e.chunks_get() << misc::decendl << '}';
  }

  void PrettyPrinter::operator()(const MethodChunk& e)
  {
    for (const auto dec : e)
      dec->accept(*this);
  }

  void PrettyPrinter::operator()(const MethodDec& e)
  {
    ostr_ << "method " << e.name_get();

    ostr_ << '(';

    const auto& formals = e.formals_get();
    for (const auto& vardec : e.formals_get())
      {
        ostr_ << vardec->name_get();
        if (vardec->type_name_get() != nullptr)
          ostr_ << " : " << *vardec->type_name_get();
        if (vardec != formals.decs_get().back())
          ostr_ << ", ";
      }

    ostr_ << ')';

    if (e.result_get())
      ostr_ << " : " << *e.result_get();
    if (e.body_get())
      {
        ostr_ << " = " << misc::incendl;
        ostr_ << *e.body_get() << misc::decendl;
      }
    else
      ostr_ << misc::iendl;
  }

  void PrettyPrinter::operator()(const MethodCallExp& e)
  {
    ostr_ << e.object_get() << ".";
    ostr_ << e.name_get() << '(';
    const auto& args = e.args_get();
    if (args.size() > 0)
      {
        for (size_t i = 0; i < args.size() - 1; i++)
          {
            ostr_ << *(args[i]) << ", ";
          }
        ostr_ << *(args[args.size() - 1]);
      }

    ostr_ << ')';
  }
  void PrettyPrinter::operator()(const ObjectExp& e)
  {
    ostr_ << "new " << e.type_name_get();
  }
} // namespace ast
