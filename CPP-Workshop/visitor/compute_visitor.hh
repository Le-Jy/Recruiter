#pragma once

#include "visitor.hh"
namespace visitor
{
    class ComputeVisitor : public Visitor
    {
    public:
        ComputeVisitor();
        int get_value();
        void visit(const tree::Tree& e) override;
        void visit(const tree::Node& e) override;
        void visit(const tree::AddNode& e) override;
        void visit(const tree::SubNode& e) override;
        void visit(const tree::MulNode& e) override;
        void visit(const tree::DivNode& e) override;
        void visit(const tree::Leaf& e) override;

    private:
        int value_;
    };

}; // namespace visitor
