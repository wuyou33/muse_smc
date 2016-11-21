#pragma once

#include "../particle_filter/pose_generation.hpp"

namespace muse_amcl {
namespace pose_generation {
class PoseGeneration3D : public PoseGeneration
{
public:
    PoseGeneration3D(ParticleSet &particle_set);

    void normal(const tf::Pose &pose,
                const Covariance &covariance) override;
    void uniform();
};
}
}

