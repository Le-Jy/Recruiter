/**
 ** \file type/record.cc
 ** \brief Implementation for type/record.hh.
 */

#include <ostream>

#include <type/builtin-types.hh>
#include <type/nil.hh>
#include <type/record.hh>
#include <type/visitor.hh>

namespace type
{
  void Record::accept(ConstVisitor& v) const { v(*this); }

  void Record::accept(Visitor& v) { v(*this); }

  // FIXME: Some code was deleted here (Field manipulators).

  // Done: Some code was deleted here (Special implementation of "compatible_with" for Record).
  bool Record::compatible_with(const Type& other) const
  {
    if (dynamic_cast<const Record*>(&other) == this)
      {
        return true;
      }
    else if (dynamic_cast<const Nil*>(&other) != nullptr)
      {
        return true;
      }
    return false;
  }
  const Type* Record::field_type(misc::symbol key) const
  {
    for (auto field : fields_)
      {
        if (field.name_get() == key)
          return &field.type_get();
      }
    return nullptr;
  }
  int Record::field_index(misc::symbol key) const
  {
    int res = 0;
    for (auto field : fields_)
      {
        if (field.name_get() == key)
          return res;
        res++;
      }
    return -1;
  }

} // namespace type
