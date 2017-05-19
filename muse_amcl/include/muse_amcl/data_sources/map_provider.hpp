#ifndef MAP_PROVIDER_HPP
#define MAP_PROVIDER_HPP

#include <memory>
#include <muse_amcl/data_types/map.hpp>
#include <ros/ros.h>

#include <muse_amcl/utils/logger.hpp>

namespace muse_mcl {
class MapProvider {
public:
    typedef std::shared_ptr<MapProvider> Ptr;

    virtual ~MapProvider()
    {
    }

    inline const static std::string Type()
    {
        return "muse_mcl::MapProvider";
    }

    inline std::string getName() const
    {
        return name_;
    }

    inline void setup(const std::string &name,
                      ros::NodeHandle   &nh_private)
    {
            name_ = name;
            Logger &l = Logger::getLogger();
            l.info("Setup", "MapProvider:" + name_);

            doSetup(nh_private);
    }

    virtual Map::ConstPtr getMap() const = 0;

protected:
    std::string  name_;

    virtual void doSetup(ros::NodeHandle &nh_private) = 0;

    std::string privateParameter(const std::string &name)
    {
        return name_ + "/" + name;
    }

};
}

#endif /* MAP_PROVIDER_HPP */
