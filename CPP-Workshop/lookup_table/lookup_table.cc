#include "lookup_table.hh"

#include <optional>
#include <unordered_map>

std::optional<long> LookupTable::get(int x)
{
    std::unordered_map<int, long>::iterator it = table_.find(x);
    if (it != table_.end())
        return it->second;
    return std::nullopt;
}
void LookupTable::set(int x, long value)
{
    table_.insert({ x, value });
}
