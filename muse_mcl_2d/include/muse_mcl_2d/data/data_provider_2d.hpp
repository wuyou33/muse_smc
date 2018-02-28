#ifndef DATA_PROVIDER_2D_HPP
#define DATA_PROVIDER_2D_HPP

#include <muse_smc/data/data.hpp>

#include <muse_smc/data/data.hpp>
#include <muse_smc/data/data_provider.hpp>

#include <muse_mcl_2d/samples/sample_2d.hpp>
#include <cslibs_math_ros/tf/tf_listener_2d.hpp>

namespace muse_mcl_2d {
class DataProvider2D : public muse_smc::DataProvider<Sample2D>
{
public:
    using Ptr = std::shared_ptr<DataProvider2D>;

    inline const static std::string Type()
    {
        return "muse_mcl_2d::DataProvider2D";
    }

    inline void setup(const cslibs_math_ros::tf::TFListener2d::Ptr &tf,
                      ros::NodeHandle       &nh)
    {
        auto param_name = [this](const std::string &name){return name_ + "/" + name;};
        tf_ = tf;
        tf_timeout_       = ros::Duration(nh.param<double>(param_name("tf_timeout"), 0.1));
        doSetup(nh);
    }

protected:
    cslibs_math_ros::tf::TFListener2d::Ptr tf_;
    ros::Duration   tf_timeout_;

    virtual void doSetup(ros::NodeHandle &nh) = 0;

};
}

#endif // DATA_PROVIDER_2D_HPP