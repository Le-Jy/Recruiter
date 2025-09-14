/**
 ** \file ast/typable.hh
 ** \brief Declaration of ast::Typable.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
  /** \class ast::Typable
   ** \brief Hold a type information.
   **
   ** A Typable node holds a type information (type::Type) about
   ** this node.  This can be:
   ** \li the type of the node itself, if it is a Exp or a Ty, or
   ** \li the type of of the declared object, in case of a Dec.
   */

  class Typable
  {
    // DONE
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a TypeDec node.
    Typable() = default;
    explicit Typable(type::Type* type);
    Typable(const Dec&) = delete;
    Typable& operator=(const Dec&) = delete;
    /// Destroy a Typable node.
    ~Typable() = default;
    /** \} */

    /// \name Visitors entry point.
    /// \{ */
    /// Accept a const visitor \a v.
    virtual void accept(ConstVisitor& v) const = 0;
    /// Accept a non-const visitor \a v.
    virtual void accept(Visitor& v) = 0;
    /// \}

    /** \name Accessors.
     ** \{ */
    /// Return type definition.
    [[nodiscard]] const type::Type& type_get() const;
    /// Return type definition.
    const type::Type& type_get();
    /** \} */

    /** \name Mutator.
     ** \{ */
    /// Set type definition.
    void type_set(type::Type* type);
    void type_set(const type::Type* type);
    /** \} */

  protected:
    /// Type definition.
    const type::Type* type_ = nullptr;
  };
} // namespace ast
#include <ast/typable.hxx>
