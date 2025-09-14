#include "person.hh"

#include <ostream>
#include <string>
#include <vector>

Person::Person(const std::string& name, uint money)
    : name_(name)
    , money_(money)
    , nfts_(std::vector<NFT>())
{}

std::vector<std::string> Person::enumerate_nfts() const
{
    std::vector<std::string> res;

    for (auto iter = nfts_.begin(); iter < nfts_.end(); iter++)
    {
        if (iter->get())
            res.push_back(*(iter->get()));
    }
    return res;
}

void Person::add_nft(NFT nft)
{
    nfts_.push_back(std::move(nft));
}

NFT Person::remove_nft(const std::string& name)
{
    for (auto iter = nfts_.begin(); iter < nfts_.end(); iter++)
    {
        if (*iter && *(iter->get()) == name)
        {
            auto res = std::move(*iter);
            nfts_.erase(iter);
            return res;
        }
    }
    return create_empty_nft();
}

void Person::add_money(uint money)
{
    money_ += money;
}

bool Person::remove_money(uint money)
{
    if (money_ < money)
        return false;
    money_ -= money;
    return true;
}

uint Person::get_money() const
{
    return money_;
}

const std::string& Person::get_name() const
{
    return name_;
}

std::ostream& operator<<(std::ostream& os, const Person& p)
{
    os << "Name: " << p.get_name() << '\n';
    os << "Money: " << p.get_money() << '\n';
    os << "NFTs:";
    auto all_nfts = p.enumerate_nfts();
    for (auto an : all_nfts)
        os << ' ' << an;
    os << '\n';
    return os;
}
