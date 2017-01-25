#ifndef KLD2D_H
#define KLD2D_H

#include <muse_amcl/particle_filter/resampling.hpp>

namespace muse_amcl {
class KLD2D : public Resampling
{
public:
    KLD2D() = default;


protected:
    virtual void doApply(ParticleSet &particle_set) override;
    virtual void doSetup(ros::NodeHandle &nh_private) override;

    double kld_error_;              /// error between histgram based distribution and particle filter posterior
    double kld_z_;                  /// upper standard normal quantile for (1-p) distributions
    double recovery_alpha_slow_;    ///
    double recovery_alpha_fast_;    ///
};
}

#endif // KLD2D_H
