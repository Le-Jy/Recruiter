/** \file misc/scoped-map.hxx
 ** \brief Implementation of misc::scoped_map.
 */

#pragma once

#include <list>
#include <sstream>
#include <stdexcept>
#include <type_traits>

#include <ranges>
#include <misc/algorithm.hh>
#include <misc/contract.hh>
#include <misc/indent.hh>
#include "scoped-map.hh"

namespace misc
{
  // FIXME: Some code was deleted here.

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::put(const Key& key, const Data& value)
  {
    current_scope->insert({key, value});
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const requires ISPTR<Data>

  {
    for (auto iter = scopes_list.rbegin(); iter != scopes_list.rend(); ++iter)
      {
        auto& scope = **iter;
        auto it = scope.find(key);
        if (it != scope.end())
          {
            return it->second;
          }
      }

    return nullptr;
  }

  template <typename Key, typename Data>
  Data scoped_map<Key, Data>::get(const Key& key) const
  {
    for (auto iter = scopes_list.rbegin(); iter != scopes_list.rend(); ++iter)
      {
        auto& scope = **iter;
        auto it = scope.find(key);
        if (it != scope.end())
          {
            return it->second;
          }
      }
    throw std::range_error("Key not found in any scope");
  }

  template <typename Key, typename Data>
  std::ostream& scoped_map<Key, Data>::dump(std::ostream& ostr) const
  {
    int i = -1;
    for (std::map<Key, Data>* scope : scopes_list)
      {
        i++;
        ostr << "scope " << i << ":\n";
        for (const auto& elem : *scope)
          {
            ostr << "key: " << elem.first << ", value: " << elem.second << "\n";
          }
      }
    return ostr;
  }

  template <typename Key, typename Data>
  void scoped_map<Key, Data>::scope_begin()
  {
    this->current_scope = new std::map<Key, Data>();
    this->scopes_list.push_back(this->current_scope);
  }

  template <typename Key, typename Data> void scoped_map<Key, Data>::scope_end()
  {
    scopes_list.pop_back();
    current_scope = scopes_list.empty() ? nullptr : scopes_list.back();
  }

  template <typename Key, typename Data>
  inline std::ostream& operator<<(std::ostream& ostr,
                                  const scoped_map<Key, Data>& tbl)
  {
    return tbl.dump(ostr);
  }

} // namespace misc
