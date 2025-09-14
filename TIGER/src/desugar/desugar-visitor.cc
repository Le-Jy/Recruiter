/**
 ** \file desugar/desugar-visitor.cc
 ** \brief Implementation of desugar::DesugarVisitor.
 */

#include <ast/all.hh>
#include <ast/libast.hh>
#include <desugar/desugar-visitor.hh>
#include <misc/algorithm.hh>
#include <misc/symbol.hh>
#include <parse/libparse.hh>
#include <parse/tweast.hh>

namespace desugar
{
  DesugarVisitor::DesugarVisitor(bool desugar_for_p, bool desugar_string_cmp_p)
    : super_type()
    , desugar_for_p_(desugar_for_p)
    , desugar_string_cmp_p_(desugar_string_cmp_p)
  {}

  /*-----------------------------.
  | Desugar string comparisons.  |
  `-----------------------------*/
  void DesugarVisitor::operator()(const ast::OpExp& e)
  {
    // COMPLETED
    // checker quand la string est dans une var
    parse::Tweast in;
    //std::cout << recurse(&(e.left_get()))->type_get();
    const type::String* left =
      dynamic_cast<const type::String*>(&(e.left_get().type_get()));
    const type::String* right =
      dynamic_cast<const type::String*>(&(e.right_get().type_get()));
    if (!left || !right)
      {
        super_type::operator()(e);
        return;
      }

    parse::ast_type ast;

    switch (e.oper_get())
      {
      case ast::OpExp::Oper::eq:

        ast = parse::parse(in << "streq(" << e.left_get() << ", "
                              << e.right_get() << ")");
        break;
      case ast::OpExp::Oper::ne:
        ast = parse::parse(in << "streq(" << e.left_get() << ", "
                              << e.right_get() << ")"
                              << "<> 0");
        break;
      case ast::OpExp::Oper::lt:
        ast = parse::parse(in << "strcmp(" << e.left_get() << ", "
                              << e.right_get() << ")"
                              << "< 0");
        break;
      case ast::OpExp::Oper::le:
        ast = parse::parse(in << "strcmp(" << e.left_get() << ", "
                              << e.right_get() << ")"
                              << "<= 0");
        break;
      case ast::OpExp::Oper::gt:
        ast = parse::parse(in << "strcmp(" << e.left_get() << ", "
                              << e.right_get() << ")"
                              << "> 0");
        break;
      case ast::OpExp::Oper::ge:
        ast = parse::parse(in << "strcmp(" << e.left_get() << ", "
                              << e.right_get() << ")"
                              << ">= 0");
        break;
      case ast::OpExp::Oper::add:
        ast = parse::parse(in << "concat(" << e.left_get() << ", "
                              << e.right_get() << ")");
        break;
      default:
        super_type::operator()(e);
        return;
      }

    if (ast.index() == 0)
      result_ = std::get<ast::Exp*>(ast);
    else if (ast.index() == 1)
      result_ = std::get<ast::ChunkList*>(ast);
  }

  /*----------------------.
  | Desugar `for' loops.  |
  `----------------------*/

  /*<<-
    Desugar `for' loops as `while' loops:

       for i := lo to hi do
         body

     is transformed as:

       let
         var _lo := lo
         var _hi := hi
         var i := _lo
       in
         if i <= _hi then
           while 1 do
             (
               body;
               if i = _hi then
                 break;
               i := i + 1
             )
       end

     Notice that:

     - a `_hi' variable is introduced so that `hi' is evaluated only
       once;

     - a `_lo' variable is introduced to prevent `i' from being in the
       scope of `_hi';

     - a first test is performed before entering the loop, so that the
       loop condition becomes `i < _hi' (instead of `i <= _hi'); this
       is done to prevent overflows on INT_MAX.
       ->>*/

  void DesugarVisitor::operator()(const ast::ForExp& e)
  {
    // COMPLETED
    parse::Tweast in;

    //const type::Int* lo =
    //  dynamic_cast<const type::Int*>(&(e.vardec_get().init_get()->type_get()));
    //const ast::IntExp* lo_exp =
    //  dynamic_cast<const ast::IntExp*>(recurse((e.vardec_get().init_get())));
    //if (!lo)
    //  {
    //    super_type::operator()(e);
    //    return;
    //  }

    auto lo_rec = recurse(e.vardec_get().init_get());
    auto hi = recurse(e.hi_get());
    auto body = recurse(e.body_get());

    in << "let\n"
       << "var _lo := " << *lo_rec << "\n";
    in << "var _hi := " << hi << "\n";
    in << "var " << e.vardec_get().name_get() << " := _lo\n";
    in << "in\n"
       << "if " << e.vardec_get().name_get() << "<= _hi then\n";
    in << "while 1 do\n(\n" << body << ";\n";
    in << "if " << e.vardec_get().name_get() << " = _hi then\n";
    in << "break;\n";
    in << e.vardec_get().name_get() << " := " << e.vardec_get().name_get()
       << " + 1\n)\nend";

    parse::ast_type ast = parse::parse(in);
    if (ast.index() == 0)
      result_ = std::get<ast::Exp*>(ast);
    else if (ast.index() == 1)
      result_ = std::get<ast::ChunkList*>(ast);
  }

} // namespace desugar
