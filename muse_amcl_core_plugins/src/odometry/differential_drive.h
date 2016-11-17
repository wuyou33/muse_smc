#pragma once

#include <muse_amcl/particle_filter/propagation.hpp>

namespace muse_amcl {
class DifferentialDrive : public Propagation
{
public:
    DifferentialDrive();

    virtual void apply(const Data::ConstPtr &data,
                       ParticleSet::PoseIterator set) override;

protected:
    virtual void doSetup(ros::NodeHandle &nh) override;

};
}

