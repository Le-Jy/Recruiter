#include "node.hh"

Node::Node(int v)
    : val_(v)
{}

int Node::get_val() const
{
    return val_;
}

void Node::set_val(int val)
{
    val_ = val;
}

std::shared_ptr<Node> Node::get_next() const
{
    return next_;
}

void Node::set_next(std::shared_ptr<Node> next)
{
    next_ = next;
}

std::shared_ptr<Node> Node::get_prev() const
{
    return prev_.lock();
}

void Node::set_prev(std::shared_ptr<Node> prev)
{
    prev_ = prev;
}
