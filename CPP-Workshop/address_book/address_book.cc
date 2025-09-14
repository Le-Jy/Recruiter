#include "address_book.hh"

#include <optional>

#include "contact_details.hh"

bool AddressBook::add(const std::string& full_name, const std::string& email,
                      const std::string& number)
{
    std::optional<ContactDetails> n =
        ContactDetails::makeDetails(number, email);
    if (n == std::nullopt || full_name == "")
        return false;
    book_.insert({ full_name, n.value() });
    return true;
}

std::vector<ContactDetails> AddressBook::find(const std::string& full_name)
{
    std::vector<ContactDetails> res;
    for (auto itr = book_.find(full_name); itr != book_.end(); itr++)
        res.emplace_back(itr->second);
    return res;
}

std::size_t AddressBook::count(const std::string& full_name)
{
    std::size_t res = 0;
    for (auto itr = book_.find(full_name); itr != book_.end(); itr++)
        res++;
    return res;
}

bool AddressBook::remove(const std::string& full_name, std::size_t index)
{
    size_t ct = 0;
    auto itr = book_.find(full_name);
    while (itr != book_.end())
    {
        if (itr->first == full_name)
        {
            if (ct == index)
            {
                book_.erase(itr);
                return true;
            }
            ct++;
        }
        itr++;
    }
    return false;
}

void AddressBook::remove_all(const std::string& full_name)
{
    this->book_.erase(full_name);
}

std::ostream& operator<<(std::ostream& os, const AddressBook& b)
{
    os << b.book_.size() << " contact(s) in the address book.\n";
    for (auto itr = b.book_.begin(); itr != b.book_.end(); itr++)
    {
        os << "- " << itr->first << ": " << itr->second;
    }
    return os;
}
