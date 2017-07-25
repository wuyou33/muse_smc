#ifndef ENCLOSINGAA2D_H
#define ENCLOSINGAA2D_H

#include <muse_mcl/plugins/types/sampling_uniform.hpp>
#include <muse_mcl/pose_samplers/uniform.hpp>

namespace muse_mcl {
class UniformAllMaps2D : public UniformSampling
{
public:
    UniformAllMaps2D();

    virtual bool update(const std::string &frame) override;
    virtual void apply(ParticleSet &particle_set) override;
    virtual void apply(Particle &particle) override;

protected:
    using Metric              = muse_mcl::pose_generation::Metric;
    using Radian              = muse_mcl::pose_generation::Radian;
    using RandomPoseGenerator = muse_mcl::pose_generation::Uniform<Metric, Metric, Radian>;

    int random_seed_;
    RandomPoseGenerator::Ptr rng_;
    std::vector<Map::ConstPtr> maps_;
    std::vector<tf::Transform> maps_T_w_;

    virtual void doSetup(ros::NodeHandle &nh_private) override;


};
}

#endif // ENCLOSINGAA2D_H
