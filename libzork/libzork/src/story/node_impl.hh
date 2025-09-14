#pragma once

#include <libzork/story/node.hh>

namespace libzork::story
{

    class Choice
    {
    public:
        Choice(const std::string& text, const Node* target);
        const std::string& get_text() const;
        const Node* get_target() const;

    private:
        std::string text_;
        const Node* target_;
    };

    class NodeImpl : public Node
    {
    public:
        NodeImpl(const std::string& name, const fs::path& script);
        ~NodeImpl() override = default;

        const std::string& get_name() const override;
        const std::string& get_text() const override;

        const Node* make_choice(std::size_t index) const override;
        std::vector<std::string>
        list_choices(bool check_conditions = true) const override;
        std::vector<std::string> list_name(bool check_conditions) const;
        void add_choice(
            const Node* other, const std::string& text,
            std::vector<std::unique_ptr<vars::Condition>> conditions = {},
            std::vector<std::unique_ptr<vars::Action>> operations = {})
            override;

    private:
        std::string name_;
        std::string text_;
        std::vector<Choice> choices_;
    };

} // namespace libzork::story
