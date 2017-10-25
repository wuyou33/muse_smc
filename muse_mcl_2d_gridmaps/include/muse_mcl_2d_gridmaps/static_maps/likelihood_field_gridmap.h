#ifndef STATIC_LIKELIHOOD_FIELD_GRIDMAP_H
#define STATIC_LIKELIHOOD_FIELD_GRIDMAP_H

#include <muse_mcl_2d_gridmaps/static_maps/gridmap.hpp>
#include <nav_msgs/OccupancyGrid.h>

namespace muse_mcl_2d_gridmaps {
namespace static_maps {
class LikelihoodFieldGridmap : public Gridmap<double>
{
public:
    LikelihoodFieldGridmap(const pose_t &origin,
                           const double resolution,
                           const std::size_t height,
                           const std::size_t width,
                           const double maximum_distance,
                           const double sigma_hit,
                           const std::string &frame_id,
                           const double default_value = 0.0);

    LikelihoodFieldGridmap(const LikelihoodFieldGridmap &other) = default;

    double at(const cslibs_math_2d::Point2d &point) const override;

    double getSigmaHit() const;

private:
    const double sigma_hit_;
    const double maximum_distance_;
};
}
}

#endif // STATIC_LIKELIHOOD_FIELD_GRIDMAP_H
