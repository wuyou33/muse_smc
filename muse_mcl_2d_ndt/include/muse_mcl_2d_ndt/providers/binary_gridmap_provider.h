#ifndef MUSE_MCL_2D_NDT_BINARY_GRIDMAP_PROVIDER_H
#define MUSE_MCL_2D_NDT_BINARY_GRIDMAP_PROVIDER_H

#include <mutex>
#include <thread>
#include <atomic>
#include <condition_variable>

#include <muse_mcl_2d/map/map_provider_2d.hpp>
#include <muse_mcl_2d_gridmaps/maps/binary_gridmap.h>

namespace muse_mcl_2d_ndt {
class BinaryGridmapProvider : public muse_mcl_2d::MapProvider2D
{
public:
    BinaryGridmapProvider();

    state_space_t::ConstPtr getStateSpace() const override;
    void setup(ros::NodeHandle &nh) override;

protected:
    std::string                                 path_;
    std::string                                 frame_id_;
    bool                                        blocking_;

    double                                      sampling_resolution_;
    double                                      threshold_;

    mutable std::mutex                          map_mutex_;
    mutable std::condition_variable             map_notify_;
    muse_mcl_2d_gridmaps::BinaryGridmap::Ptr    map_;
    std::thread                                 worker_;

    void loadMap();
};
}

#endif // MUSE_MCL_2D_NDT_BINARY_GRIDMAP_PROVIDER_H