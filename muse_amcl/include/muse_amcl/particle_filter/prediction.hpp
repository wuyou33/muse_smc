#ifndef PREDICTION_HPP
#define PREDICTION_HPP

#include <muse_amcl/data_types/data.hpp>
#include <muse_amcl/data_sources/data_provider.hpp>
#include <muse_amcl/particle_filter/particle_set.hpp>
#include <muse_amcl/particle_filter/prediction_model.hpp>

namespace muse_amcl {
class Prediction {
public:
    using Ptr = std::shared_ptr<Prediction>;
    struct Less {
        bool operator()( const Prediction& lhs,
                         const Prediction& rhs ) const
        {
            return lhs.getStamp() < rhs.getStamp();
        }
        bool operator()( const Prediction::Ptr& lhs,
                         const Prediction::Ptr& rhs ) const
        {
            return lhs->getStamp() < rhs->getStamp();
        }
    };

    struct Greater {
        bool operator()( const Prediction& lhs,
                         const Prediction& rhs ) const
        {
            return lhs.getStamp() > rhs.getStamp();
        }
        bool operator()( const Prediction::Ptr& lhs,
                         const Prediction::Ptr& rhs ) const
        {
            return lhs->getStamp() > rhs->getStamp();
        }
    };


    Prediction(const Data::ConstPtr       &data,
               const PredictionModel::Ptr &model) :
        data_(data),
        model_(model)
    {
    }

    inline PredictionModel::Result operator ()
        (const ros::Time &until, ParticleSet::Poses poses)
    {
        return model_->predict(data_, until, poses);
    }

    inline PredictionModel::Result apply(const ros::Time &until,
                                         ParticleSet::Poses poses)
    {
        return model_->predict(data_, until, poses);
    }

    inline const ros::Time & getStamp() const
    {
        return data_->getTimeFrame().start;
    }

    inline PredictionModel::Ptr getPredictionModel() const
    {
        return model_;
    }

private:
    Data::ConstPtr          data_;
    PredictionModel::Ptr    model_;
};
}


#endif // PREDICTION_HPP
