#pragma once

#include <string>
#include <ros/node_handle.h>
#include "plugin_manager.hpp"

namespace muse_amcl {
template<typename PluginType>
class PluginFactory {
public:
    PluginFactory() :
        plugin_manager(PluginType::Type()),
        nh_private_("~")
    {
        plugin_manager.load();
    }

    virtual typename PluginType::Ptr create(const std::string &class_name,
                                            const std::string &plugin_name)
    {
        auto constructor = plugin_manager.getConstructor(class_name);
        if(constructor) {
            typename PluginType::Ptr plugin = constructor();
            plugin->setup(plugin_name, nh_private_);
            return plugin;
        } else {
            std::cerr << "[Factory] :"
                      << " Cannot create '"  << class_name
                      << "' derivded from '" << PluginType::Type()
                      << "'" << std::endl;
            return nullptr;
        }
    }

    static const std::string Type()
    {
        return PluginType::Type();
    }


protected:
    PluginManager<PluginType> plugin_manager;
    ros::NodeHandle           nh_private_;

};
}

