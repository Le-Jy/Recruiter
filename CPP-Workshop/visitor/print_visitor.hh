#pragma once

#include <string>

#include "visitor.hh"
namespace visitor
{
    class PrintVisitor : public Visitor
    {
    public:
        PrintVisitor() = default;
        std::string get_value();
        void visit(const tree::Tree& e) override;
        void visit(const tree::Node& e) override;
        void visit(const tree::AddNode& e) override;
        void visit(const tree::SubNode& e) override;
        void visit(const tree::MulNode& e) override;
        void visit(const tree::DivNode& e) override;
        void visit(const tree::Leaf& e) override;

    private:
        std::string value_;
    };

}; // namespace visitor
