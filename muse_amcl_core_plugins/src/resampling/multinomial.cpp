#include "multinomial.h"

#include <class_loader/class_loader_register_macro.h>
CLASS_LOADER_REGISTER_CLASS(muse_amcl::Multinomial, muse_amcl::Resampling)

#include <muse_amcl/math/random.hpp>

#include "impl/multinomial.hpp"

using namespace muse_amcl;

void Multinomial::apply(ParticleSet &particle_set)
{
    ParticleSet::Particles &p_t_1 = particle_set.getParticles();
    ParticleSet::Particles  p_t;

    resampling::impl::Multinomial::apply(p_t_1, p_t, particle_set.getMaximumSize());

    /// assign new content
    assert(p_t.size() == p_t_1.size());
    std::swap(p_t, p_t_1);
}

void Multinomial::doSetup(ros::NodeHandle &nh_private)
{
}
