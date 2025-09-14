#include "auction.hh"

#include <string>
#include <utility>

Auction::Auction(Person& organizer, NFT nft, uint initial_bid)
    : organizer_(organizer)
    , nft_(std::move(nft))
    , highest_bidder_(nullptr)
    , highest_bid_(initial_bid)
{
    if (!nft_)
        throw std::invalid_argument("NFT is empty");
}

Auction::~Auction()
{
    if (highest_bidder_ == nullptr)
        organizer_.add_nft(std::move(nft_));
    else
    {
        highest_bidder_->add_nft(std::move(nft_));
        organizer_.add_money(highest_bid_);
    }
}

bool Auction::bid(Person& person, uint money)
{
    if (highest_bidder_ == nullptr && highest_bid_ < money
        && person.remove_money(money))
    {
        highest_bidder_ = &person;
        highest_bid_ = money;
        return true;
    }
    if (money <= highest_bid_ || !person.remove_money(money))
        return false;
    highest_bidder_->add_money(highest_bid_);
    highest_bidder_ = &person;
    highest_bid_ = money;
    return true;
}

uint Auction::get_highest_bid() const
{
    return highest_bid_;
}

const std::string& Auction::get_nft_name() const
{
    return *nft_.get();
}
