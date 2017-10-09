#ifndef OCCUPANCY_GRID_MAPPER_NODE_H
#define OCCUPANCY_GRID_MAPPER_NODE_H

#include <ros/ros.h>
#include <sensor_msgs/LaserScan.h>

#include "occupancy_grid_mapper.h"

#include <muse_mcl_2d/tf/tf_provider.hpp>

namespace muse_mcl_2d_mapping {
class OccupancyGridMapperNode
{
public:
    OccupancyGridMapperNode();

    bool setup();
    void run();

private:
    using interval_t = std::array<double, 2>;

    ros::NodeHandle nh_;
    std::vector<ros::Subscriber> sub_lasers_;
    ros::Publisher               pub_map_;
    muse_mcl_2d::TFProvider::Ptr tf_;

    double      rate_;

    bool            undistortion_;              /// check if undistortion shall be applied
    std::string     undistortion_fixed_frame_;  /// the fixed frame necessary for the undistortion
    ros::Duration   undistortion_tf_timeout_;   /// time out for the tf listener

    interval_t linear_interval_;                /// linear field of view
    interval_t angular_interval_;               /// angular field of view


    void laserscan(const sensor_msgs::LaserScanConstPtr &msg);



};
}

#endif // OCCUPANCY_GRID_MAPPER_NODE_H
