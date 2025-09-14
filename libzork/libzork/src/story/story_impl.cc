#include "story/story_impl.hh"

#include <cassert>
#include <iostream>
#include <libzork/store/store.hh>
#include <yaml-cpp/yaml.h>

#include "exceptions.hh"
#include "node_impl.hh"
#include "store/store_impl.hh"
#include "story/node_impl.hh"

namespace libzork::story
{
    StoryImpl::StoryImpl(const fs::path& path)
    {
        YAML::Node config = YAML::LoadFile(path.string());

        title_ = config["title"].as<std::string>();

        std::string scripts_path = std::string(path.parent_path().c_str()) + "/"
            + config["scripts-path"].as<std::string>();
        size_t ssize = config["story"].size();

        for (size_t tmpsize = 0; tmpsize < ssize; tmpsize++)
        {
            std::string name =
                config["story"][tmpsize]["name"].as<std::string>();
            std::string corres_path = scripts_path + '/'
                + config["story"][tmpsize]["script"].as<std::string>();
            nodes_.push_back(libzork::story::make_node(name, corres_path));
        }

        for (size_t tmpsize = 0; tmpsize < ssize; tmpsize++)
        {
            size_t csize = config["story"][tmpsize]["choices"].size();
            for (size_t choicetmp = 0; choicetmp < csize; choicetmp++)
            {
                size_t currentnodessize = nodes_.size();
                size_t ntmpsize = 0;
                while (ntmpsize < currentnodessize
                       && nodes_[ntmpsize]->get_name()
                           != config["story"][tmpsize]["choices"][choicetmp]
                                    ["target"]
                                        .as<std::string>())
                {
                    ntmpsize++;
                }
                nodes_[tmpsize]->add_choice(
                    nodes_[ntmpsize].get(),
                    config["story"][tmpsize]["choices"][choicetmp]["text"]
                        .as<std::string>(),
                    std::vector<std::unique_ptr<vars::Condition>>(),
                    std::vector<std::unique_ptr<vars::Action>>());
            }
        }
        actual_ = libzork::store::make_store();
        if (ssize != 0)
            actual_->set_active_node(nodes_[0].get());
    }

    const std::string& StoryImpl::get_title() const
    {
        return title_;
    }

    const Node* StoryImpl::get_current() const
    {
        if (actual_)
            return actual_->get_active_node();
        return nullptr;
    }

    void StoryImpl::set_current(const Node* node)
    {
        actual_->set_active_node(node);
    }

    const store::Store* StoryImpl::get_store() const
    {
        return actual_.get();
    }

    std::ostream& StoryImpl::display(std::ostream& os) const
    {
        os << "digraph "
           << "\"" << title_ << "\" "
           << " {\n";
        size_t vsize = nodes_.size();
        for (size_t i = 0; i < vsize; i++)
        {
            os << '\t' << '\"' << nodes_[i].get()->get_name() << '\"';
            NodeImpl* n = static_cast<NodeImpl*>(nodes_[i].get());
            auto choices = n->list_name(true);
            size_t csize = choices.size();
            if (csize == 0)
            {
                os << ";\n";
                continue;
            }
            os << " -> {";

            for (size_t j = 0; j < csize; j++)
            {
                if (j != 0)
                    os << " ";
                os << '\"' << choices[j] << "\"";
            }
            os << "};\n";
        }
        os << "}\n";
        return os;
    }

} // namespace libzork::story
