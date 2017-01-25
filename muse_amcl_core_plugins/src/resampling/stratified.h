#ifndef STRATIFIED_H
#define STRATIFIED_H

#include <muse_amcl/particle_filter/resampling.hpp>

namespace muse_amcl {
class Stratified : public Resampling
{
public:
    Stratified() = default;

protected:
    virtual void doApply(ParticleSet &particle_set) override;
    virtual void doSetup(ros::NodeHandle &nh_private) override;
};
}

#endif // STRATIFIED_H
