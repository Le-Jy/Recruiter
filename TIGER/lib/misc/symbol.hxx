/**
 ** \file misc/symbol.hxx
 ** \brief Inline implementation of misc::symbol.
 */

#pragma once

#include <misc/symbol.hh>

namespace misc
{
  inline symbol& symbol::operator=(const symbol& rhs)
  {
    // FIXME: implementing.
    if (this != &rhs)
      super_type::operator=(rhs);
    return *this;
  }

  inline bool symbol::operator==(const symbol& rhs) const
  {
    // FIXME: implementing.
    return super_type::operator==(rhs);
  }

  inline bool symbol::operator!=(const symbol& rhs) const
  {
    // FIXME: implementing.
    return super_type::operator!=(rhs);
  }

  inline std::ostream& operator<<(std::ostream& ostr, const symbol& the)
  {
    // FIXME: implementing.
    return ostr << the.get();
  }

} // namespace misc
