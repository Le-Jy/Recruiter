#pragma once

#include <libzork/store/store.hh>
#include <libzork/story/story.hh>

namespace libzork::story
{

    class StoryImpl : public Story
    {
    public:
        StoryImpl(const fs::path& path);
        ~StoryImpl() override = default;

        const std::string& get_title() const override;
        const Node* get_current() const override;
        void set_current(const Node* node) override;
        const store::Store* get_store() const override;
        std::ostream& display(std::ostream& os) const override;

    private:
        std::unique_ptr<store::Store> actual_;
        std::vector<std::unique_ptr<Node>> nodes_;
        std::string title_;
    };

} // namespace libzork::story
