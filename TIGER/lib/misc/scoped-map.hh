/**
 ** \file misc/scoped-map.hh
 ** \brief Declaration of misc::scoped_map.
 **
 ** This implements a stack of dictionnaries.  Each time a scope is
 ** opened, a new dictionnary is added on the top of the stack; the
 ** dictionary is removed when the scope is closed.  Lookup of keys
 ** is done in the last added dictionnary first (LIFO).
 **
 ** In particular this class is used to implement symbol tables.
 **/

#pragma once

#include <map>
#include <ostream>
#include <vector>

namespace misc
{

  template <typename Data>
  concept ISPTR = std::is_pointer_v<Data>;

  template <typename Key, typename Data> class scoped_map
  {
    // FIXME: Some code was deleted here.
  public:
    void put(const Key& key, const Data& value);
    Data get(const Key& key) const;
    Data get(const Key& key) const requires ISPTR<Data>;
    std::ostream& dump(std::ostream& ostr) const;
    void scope_begin();
    void scope_end();

  private:
    std::vector<std::map<Key, Data>*> scopes_list;
    int list_size;
    std::map<Key, Data>* current_scope = nullptr;
  };

  template <typename Key, typename Data>
  std::ostream& operator<<(std::ostream& ostr,
                           const scoped_map<Key, Data>& tbl);

  // FIXME: Some code was deleted here.
  // fake news
} // namespace misc

#include <misc/scoped-map.hxx>
