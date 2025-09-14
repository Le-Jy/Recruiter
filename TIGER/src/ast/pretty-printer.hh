/**
 ** \file ast/pretty-printer.hh
 ** \brief Declaration of ast::PrettyPrinter.
 */

#pragma once

#include <ast/default-visitor.hh>
#include <ast/object-visitor.hh>

namespace ast
{
  /// Visit an Ast and print the content of each node.
  class PrettyPrinter
    : virtual public DefaultConstVisitor
    , virtual public ObjectConstVisitor
  {
  public:
    using super_type = DefaultConstVisitor;
    // Import overloaded virtual functions.
    using super_type::operator();

    /// Build to print on \a ostr.
    PrettyPrinter(std::ostream& ostr);

    /// Visit methods.
    /// \{
    void operator()(const SimpleVar& e) override;
    void operator()(const FieldVar& e) override;
    void operator()(const SubscriptVar& e) override;
    void operator()(const CastExp& e) override;
    // FIXME: Some code was deleted here.

    /** \name Visit Expression related nodes.
     ** \{ */
    void operator()(const NilExp& e) override;
    void operator()(const IntExp& e) override;
    void operator()(const StringExp& e) override;
    void operator()(const CallExp& e) override;
    void operator()(const OpExp& e) override;
    void operator()(const RecordExp& e) override;
    void operator()(const SeqExp& e) override;
    void operator()(const AssignExp& e) override;
    void operator()(const IfExp& e) override;
    void operator()(const WhileExp& e) override;
    void operator()(const ForExp& e) override;
    void operator()(const BreakExp& e) override;
    void operator()(const LetExp& e) override;
    void operator()(const ArrayExp& e) override;
    void operator()(const FieldInit& e) override;
    /** \} */

    /** \name Visit Declaration related nodes.
     **
     ** Visiting declarations is simple, but there are many clauses.
     ** This is because, in Tiger, the declarations are processed by
     ** chunks (a chunk of Function declarations, then Var or Type,
     ** then ...).
     ** So we have to explain
     ** \li How to visit a list of chunks;
     ** \li how to visit chunks of function, var, or type declarations;
     ** \li how to visit a single function, var, or type declaration.
     ** \{ */

    /// Visit a list of function, type and/or variables declarations.
    void operator()(const ChunkList& e) override;

    /// Visit a ChunkInterface chunks.
    void operator()(const ChunkInterface& e) override;

    //template <typename ChunkType>
    /** \brief Visit a chunk (i.e., a list of Function, Var, and Type declarations).
     **
     ** It is exactly the same in the three cases, so the code is
     ** factored via a template method. */
    //void chunk_visit(const<ChunkType>& e);

    /// Visit Var declarations.
    void operator()(const VarChunk& e) override;
    void operator()(const VarDec& e) override;

    /// Visit Function declarations.
    void operator()(const FunctionChunk& e) override;
    void operator()(const FunctionDec& e) override;

    /// Visit Type declarations.
    void operator()(const TypeChunk& e) override;
    void operator()(const TypeDec& e) override;

    /** \} */

    /** \name Visit Type related nodes.
     ** \{ */
    void operator()(const NameTy& e) override;
    void operator()(const RecordTy& e) override;
    void operator()(const ArrayTy& e) override;
    /** \} */

    /** \name Visit Field related nodes. */
    void operator()(const Field& e) override;

    void operator()(const ClassTy& e) override;

    void operator()(const MethodChunk& e) override;
    void operator()(const MethodDec& e) override;

    void operator()(const MethodCallExp& e) override;
    void operator()(const ObjectExp& e) override;

    /// \}

  private:
    // Factor pretty-printing of RecordExp and RecordTy.
    template <typename RecordClass> void print_record(const RecordClass& e);

    // Whether we are in a ast::ClassTy.
    bool within_classty_p_ = false;

  protected:
    /// The stream to print on.
    std::ostream& ostr_;
  };

} // namespace ast
