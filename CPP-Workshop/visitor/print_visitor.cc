#include "print_visitor.hh"

#include <iostream>
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
    std::string PrintVisitor::get_value()
    {
        return value_;
    }
    void PrintVisitor::visit(const tree::Tree& e)
    {
        e.accept(*this);
    }
    void PrintVisitor::visit(const tree::Node& e)
    {
        e.accept(*this);
    }
    void PrintVisitor::visit(const tree::AddNode& e)
    {
        std::cout << '(';
        e.get_lhs()->accept(*this);
        std::cout << " + ";
        e.get_rhs()->accept(*this);
        std::cout << ')';
    }
    void PrintVisitor::visit(const tree::SubNode& e)
    {
        std::cout << '(';
        e.get_lhs()->accept(*this);
        std::cout << " - ";
        e.get_rhs()->accept(*this);
        std::cout << ')';
    }
    void PrintVisitor::visit(const tree::MulNode& e)
    {
        std::cout << '(';
        e.get_lhs()->accept(*this);
        std::cout << " * ";
        e.get_rhs()->accept(*this);
        std::cout << ')';
    }
    void PrintVisitor::visit(const tree::DivNode& e)
    {
        std::cout << '(';
        e.get_lhs()->accept(*this);
        std::cout << " / ";
        e.get_rhs()->accept(*this);
        if (value_ == "0")
            throw std::overflow_error("Divide by zero exception");
        std::cout << ')';
    }
    void PrintVisitor::visit(const tree::Leaf& e)
    {
        std::cout << e.get_value();
    }

} // namespace visitor
