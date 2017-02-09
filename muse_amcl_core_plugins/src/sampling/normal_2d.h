#ifndef NORMAL2D_H
#define NORMAL2D_H

#include <muse_amcl/particle_filter/sampling_normal.hpp>

namespace muse_amcl {
class Normal2D : public NormalSampling
{
public:
    virtual void update(const std::string &frame) override;

    virtual void apply(const math::Pose       &pose,
                       const math::Covariance &covariance,
                       ParticleSet            &particle_set) override;

protected:

    int random_seed_;
    std::vector<Map::ConstPtr>  maps_;
    std::vector<tf::Transform>  maps_T_w_;

    virtual void doSetup(ros::NodeHandle &nh_private) override;


};
}

#endif // NORMAL2D_H
