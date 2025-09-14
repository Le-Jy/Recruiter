#include "compute_visitor.hh"

#include <stdexcept>

#include "add.hh"
#include "div.hh"
#include "leaf.hh"
#include "mul.hh"
#include "node.hh"
#include "sub.hh"
#include "tree.hh"

namespace visitor
{
    ComputeVisitor::ComputeVisitor()
        : value_(0)
    {}

    int ComputeVisitor::get_value()
    {
        return value_;
    }
    void ComputeVisitor::visit(const tree::Tree& e)
    {
        e.accept(*this);
    }
    void ComputeVisitor::visit(const tree::Node& e)
    {
        e.accept(*this);
    }
    void ComputeVisitor::visit(const tree::AddNode& e)
    {
        e.get_lhs()->accept(*this);
        int value_l = value_;
        e.get_rhs()->accept(*this);
        int value_r = value_;
        value_ = value_l + value_r;
    }
    void ComputeVisitor::visit(const tree::SubNode& e)
    {
        e.get_lhs()->accept(*this);
        int value_l = value_;
        e.get_rhs()->accept(*this);
        int value_r = value_;
        value_ = value_l - value_r;
    }
    void ComputeVisitor::visit(const tree::MulNode& e)
    {
        e.get_lhs()->accept(*this);
        int value_l = value_;
        e.get_rhs()->accept(*this);
        int value_r = value_;
        value_ = value_l * value_r;
    }
    void ComputeVisitor::visit(const tree::DivNode& e)
    {
        e.get_lhs()->accept(*this);
        int value_l = value_;
        e.get_rhs()->accept(*this);
        int value_r = value_;
        if (value_r == 0)
            throw std::overflow_error("Divide by zero exception");
        value_ = value_l / value_r;
    }
    void ComputeVisitor::visit(const tree::Leaf& e)
    {
        value_ = std::stoi(e.get_value());
    }
} // namespace visitor
