#include "story/node_impl.hh"

#include <fstream>
#include <iostream>
#include <sstream>

#include "exceptions.hh"
#include "node_impl.hh"

namespace libzork::story
{
    Choice::Choice(const std::string& text, const Node* target)
        : text_(text)
        , target_(target)
    {}

    const std::string& Choice::get_text() const
    {
        return text_;
    }

    const Node* Choice::get_target() const
    {
        return target_;
    }

    NodeImpl::NodeImpl(const std::string& name, const fs::path& script)
        : name_(name)
    {
        std::ifstream file;
        file.open(script);
        std::stringstream res;
        std::string line;
        while (std::getline(file, line))
        {
            res << line;
            res << '\n';
        }
        text_ = res.str();
        choices_ = std::vector<Choice>();
    }

    const std::string& NodeImpl::get_name() const
    {
        return name_;
    }

    const std::string& NodeImpl::get_text() const
    {
        return text_;
    }

    const Node* NodeImpl::make_choice(size_t index) const
    {
        if (index >= choices_.size())
            return nullptr;
        return choices_[index].get_target();
    }

    std::vector<std::string> NodeImpl::list_choices(bool check_conditions) const
    {
        if (check_conditions)
            check_conditions = false;
        auto res = std::vector<std::string>();
        size_t vsize = choices_.size();
        for (size_t i = 0; i < vsize; i++)
        {
            res.push_back(choices_[i].get_text());
        }
        return res;
    }

    std::vector<std::string> NodeImpl::list_name(bool check_conditions) const
    {
        if (check_conditions)
            check_conditions = false;
        auto res = std::vector<std::string>();
        size_t vsize = choices_.size();
        for (size_t i = 0; i < vsize; i++)
        {
            res.push_back(choices_[i].get_target()->get_name());
        }
        return res;
    }

    void NodeImpl::add_choice(
        const Node* other, const std::string& text,
        std::vector<std::unique_ptr<vars::Condition>> conditions,
        std::vector<std::unique_ptr<vars::Action>> operations)
    {
        (void)conditions;
        (void)operations;
        choices_.push_back(Choice(text, other));
    }

} // namespace libzork::story
