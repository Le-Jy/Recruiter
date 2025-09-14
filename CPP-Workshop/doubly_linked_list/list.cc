#include "list.hh"

List::List()
    : nb_elts_(0)
    , first_(nullptr)
    , last_(nullptr)
{}

void List::push_front(int i)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>(i);
    if (!first_)
    {
        first_ = newNode;
        last_ = newNode;
    }
    else
    {
        newNode->set_next(first_);
        first_->set_prev(newNode);
        first_ = newNode;
    }
    nb_elts_++;
}

void List::push_back(int i)
{
    std::shared_ptr<Node> newNode = std::make_shared<Node>(i);
    if (!last_)
    {
        first_ = newNode;
        last_ = newNode;
    }
    else
    {
        last_->set_next(newNode);
        newNode->set_prev(last_);
        last_ = newNode;
    }
    nb_elts_++;
}

std::optional<int> List::pop_front()
{
    if (!first_)
    {
        return std::nullopt;
    }
    int val = first_->get_val();
    if (first_ == last_)
    {
        first_ = nullptr;
        last_ = nullptr;
    }
    else
    {
        first_ = first_->get_next();
        first_->set_prev(nullptr);
    }
    nb_elts_--;
    return val;
}

std::optional<int> List::pop_back()
{
    if (!last_)
    {
        return std::nullopt;
    }
    int val = last_->get_val();
    if (first_ == last_)
    {
        first_ = nullptr;
        last_ = nullptr;
    }
    else
    {
        last_ = last_->get_prev();
        last_->set_next(nullptr);
    }
    nb_elts_--;
    return val;
}

void List::print(std::ostream& os) const
{
    std::shared_ptr<Node> current = first_;
    if (!current)
        return;
    while (current->get_next())
    {
        os << current->get_val() << " ";
        current = current->get_next();
    }
    os << current->get_val();
}

size_t List::length() const
{
    return nb_elts_;
}
