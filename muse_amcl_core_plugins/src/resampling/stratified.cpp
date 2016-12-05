#include "stratified.h"

#include <class_loader/class_loader_register_macro.h>
CLASS_LOADER_REGISTER_CLASS(muse_amcl::Stratified, muse_amcl::Resampling)

#include <muse_amcl/math/random.hpp>

using namespace muse_amcl;

void Stratified::apply(ParticleSet &particle_set)
{
    /// initalize particle new particle set
    ParticleSet::Particles &p = particle_set.getParticles();
    const std::size_t size        = p.size();
    ParticleSet::Particles  p_new(size);

    /// prepare ordered sequence of random numbers
    math::random::Uniform<1> rng(0.0, 1.0);
    std::vector<double> u(size);
    {
        for(std::size_t i = 0 ; i < size ; ++i) {
            u[i] = (i + rng.get()) / size;
        }
    }
    /// draw samples
    {
        auto p_it = p.begin();
        auto p_new_it = p_new.begin();
        double cumsum_last = 0.0;
        double cumsum = p_it->weight_;

        auto in_range = [&cumsum, &cumsum_last] (double u)
        {
            return u >= cumsum_last && u < cumsum;
        };

        for(auto &u_r : u) {
            while(!in_range(u_r)) {
                ++p_it;
                cumsum_last = cumsum;
                cumsum += p_it->weight_;
            }

            *p_new_it = *p_it;
            ++p_new_it;
        }
    }
    /// assign new content
    assert(p_new.size() == p.size());
    p.assign(p_new.begin(), p_new.end());
}

void Stratified::doSetup(ros::NodeHandle &nh_private)
{

}
