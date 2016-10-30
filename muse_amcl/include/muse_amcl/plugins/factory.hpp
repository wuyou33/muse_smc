#pragma once

#include <string>
#include <muse_amcl/plugin/plugin_manager.hpp>

namespace muse_amcl {
template<typename PluginType>
class PluginFactory {
public:
    PluginFactory() :
        plugin_manager(PluginType::Type())
    {
        plugin_manager.load();
    }

    virtual typename PluginType::Ptr create(const std::string class_name)
    {
        auto constructor = plugin_manager.getConstructor(class_name);
        if(constructor) {
            return constructor();
        } else {
            std::cerr << "[PluginManager] :"
                      << " Cannot create '"  << class_name
                      << "' derivded from '" << PluginType::Type
                      << "'" << std::endl;
            return nullptr;
        }
    }


protected:
    PluginManager<PluginType> plugin_manager;

};
}

