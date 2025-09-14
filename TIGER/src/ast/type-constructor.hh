/**
 ** \file ast/type-constructor.hh
 ** \brief Declaration of ast::TypeConstructor.
 */

#pragma once

#include <ast/fwd.hh>
#include <type/fwd.hh>

namespace ast
{
  /** \class ast::TypeConstructor
   ** \brief Create a new type.
   */

  class TypeConstructor
  {
    // DONE
  public:
    /** \name Ctor & dtor.
     ** \{ */
    /// Construct a TypeDec node.
    TypeConstructor() = default;
    explicit TypeConstructor(type::Type* build_type);
    TypeConstructor(const Dec&) = delete;
    TypeConstructor& operator=(const Dec&) = delete;
    /// Destroy a Typable node.
    ~TypeConstructor() = default;
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
    [[nodiscard]] const type::Type& build_type_get() const;
    /// Return type definition.
    const type::Type& build_type_get();
    /** \} */

    /** \name Mutator.
     ** \{ */
    /// Set type definition.
    void build_type_set(type::Type* buildType);
    void build_type_set(const type::Type* buildType);
    /** \} */

  protected:
    /// Type definition.
    const type::Type* build_type_ = nullptr;
  };
} // namespace ast
#include <ast/type-constructor.hxx>
