#ifndef POSE_HPP
#define POSE_HPP

#include <tf/tf.h>
#include <eigen3/Eigen/Core>
#include "angle.hpp"

namespace muse_amcl {
namespace math {
/**
 * @brief The Pose class is a helper class to provide an interface
 *        between Eigen and tf.
 */
class Pose {
public:
    using Vector6d = Eigen::Matrix<double,6,1>;
    using Vector3d = Eigen::Matrix<double,3,1>;


    /**
     * @brief Pose default contstructor.
     */
    Pose() :
        pose_(tf::createQuaternionFromRPY(0,0,0),
              tf::Vector3(0,0,0))
    {
    }

    /**
     * @brief Pose constructor using explicit values.
     * @param x     - the x coordinate
     * @param y     - the y coordinate
     * @param z     - the z coordinate
     * @param roll  - the roll angle
     * @param pitch - the pitch angle
     * @param yaw   - the yaw angle
     */
    Pose(const double x,
         const double y,
         const double z,
         const double roll,
         const double pitch,
         const double yaw) :
        pose_(tf::createQuaternionFromRPY(roll, pitch, yaw),
              tf::Vector3(x,y,z))
    {
    }

    /**
     * @brief Pose constructor using explicit values.
     * @param x     - the x coordinate
     * @param y     - the y coordinate
     * @param z     - the z coordinate
     * @param qx    - the 1st component of the quaternion
     * @param qy    - the 2nd component of the quaternion
     * @param qz    - the 3rd component of the quaternion
     * @param qw    - the 4th component of the quaternion
     */
    Pose(const double x,
         const double y,
         const double z,
         const double qx,
         const double qy,
         const double qz,
         const double qw) :
        pose_(tf::Quaternion(qx,qy,qz,qw),
              tf::Vector3(x,y,z))
    {
    }

    /**
     * @brief Pose constructor for tf datatypes.
     * @param p - a pose
     */
    Pose(const tf::Pose &p) :
        pose_(p)
    {
    }

    /**
     * @brief Pose constructor for tf datatypes.
     * @param q - the rotation quaternion
     * @param p - the position
     */
    Pose(const tf::Quaternion &q,
         const tf::Point      &p) :
        pose_(q, p)
    {
    }

    /**
     * @brief Pose constructor for the 3D Eigen representation.
     * @param p
     */
    Pose(const Vector3d &p) :
        pose_(tf::createQuaternionFromYaw(angle::normalize(p(2))),
              tf::Vector3(p(0),p(1), 0))
    {
    }

    /**
     * @brief Pose constructor for the 6D Eigen representation.
     * @param p
     */
    Pose(const Vector6d &p) :
        pose_(tf::createQuaternionFromRPY(p(3),p(4),p(5)),
              tf::Vector3(p(0),p(1),p(2)))
    {
    }

    /**
     * @brief tf returns the TF pose as reference.
     * @return
     */
    inline tf::Pose & getPose()
    {
        return pose_;
    }

    /**
     * @brief tf returns the TF pose as const reference.
     * @return
     */
    inline const tf::Pose & getPose() const
    {
        return pose_;
    }

    /**
     * @brief Set the rotation of the pose.
     * @param q
     */
    inline void setRotation(const tf::Quaternion &q)
    {
        pose_.setRotation(q);
    }

    /**
     * @brief rotation returns a reference to the rotation quaternion.
     * @return
     */
    inline const tf::Quaternion getRotation() const
    {
        return pose_.getRotation();
    }

    /**
     * @brief rotation returns a reference to the origin.
     * @return
     */
    inline tf::Vector3 & getOrigin()
    {
        return pose_.getOrigin();
    }

    /**
     * @brief rotation returns a const reference to the origin.
     * @return
     */
    inline const tf::Vector3 & getOrigin() const
    {
        return pose_.getOrigin();
    }

    /**
     * @brief eigen3D returns the 2D pose as an Eigen datatype.
     * @return
     */
    inline Vector3d getEigen3D() const
    {
        const tf::Vector3 &position = pose_.getOrigin();
        return Vector3d(position.x(), position.y(), yaw());
    }

    /**
     * @brief eigen3D returns the 3D pose as an Eigen datatype.
     * @return
     */
    inline Vector6d getEigen6D() const
    {
        const tf::Vector3 &position = pose_.getOrigin();
        Vector6d e;
        e[0] = position.x();
        e[1] = position.y();
        e[2] = position.z();
        pose_.getBasis().getRPY(e[3],e[4],e[5]);
        return e;
    }

    inline void setEigen3D(const Vector3d &p)
    {
        pose_.setOrigin(tf::Point(p(0), p(1), 0.0));
        pose_.setRotation(tf::createQuaternionFromYaw(p(2)));
    }

    inline void setEigen6D(const Vector6d &p)
    {
        pose_.setOrigin(tf::Point(p(0), p(1), p(2)));
        pose_.setRotation(tf::createQuaternionFromRPY(p(3),p(4),p(5)));
    }

    /**
     * @brief x returns the x component of the pose by const reference.
     * @return the x component
     */
    inline const double &x() const
    {
        return pose_.getOrigin().x();
    }

    /**
     * @brief y returns the y component of the pose by const reference.
     * @return the y component
     */
    inline const double &y() const
    {
        return pose_.getOrigin().y();
    }

    /**
     * @brief z returns the z component of the pose by const reference.
     * @return the z component
     */
    inline const double &z() const
    {
        return pose_.getOrigin().z();
    }

    /**
     * @brief x returns the x component of the pose by reference.
     * @return the x component
     */
    inline double &x()
    {
        return pose_.getOrigin().m_floats[0];
    }

    /**
     * @brief y returns the y component of the pose by reference.
     * @return the y component
     */
    inline double &y()
    {
        return pose_.getOrigin().m_floats[1];
    }


    /**
     * @brief z returns the z component of the pose by reference.
     * @return the z component
     */
    inline double &z()
    {
        return pose_.getOrigin().m_floats[2];
    }

    /**
     * @brief roll returns the roll angle.
     * @return - the roll angle
     */
    inline double roll() const
    {
        double roll,pitch,yaw;
        rpy(roll, pitch, yaw);
        return roll;
    }

    /**
     * @brief Pitch returns the pitch angle.
     * @return - the pitch angle
     */
    inline double pitch() const
    {
        double roll,pitch,yaw;
        rpy(roll, pitch, yaw);
        return pitch;
    }

    /**
     * @brief yaw returns the yaw angle.
     * @return - the yaw angle
     */
    inline double yaw() const
    {
        return tf::getYaw(pose_.getRotation());
    }

    /**
     * @brief rpy returns roll, pitch and yaw angle by reference.
     * @param roll  - the roll angle
     * @param pitch - the pitch angle
     * @param yaw   - the yaw angle
     */
    inline void rpy(double &roll,
                    double &pitch,
                    double &yaw) const
    {
        tf::Matrix3x3 (pose_.getRotation()).getEulerYPR(yaw, pitch, roll);
    }

    /**
     * @brief transformed returns a copy of a pose to which a transformation was applied.
     * @param transform - the transformation to be applied.
     * @return the transformed pose
     */
    Pose transformed(const tf::Transform &transform) const
    {
        return Pose(transform * pose_);
    }

    /**
     * @brief transformed returns a copy of a pose to which a transformation was applied.
     * @param transform - the transformation to be applied.
     * @return the transformed pose
     */
    Pose transformed(const tf::StampedTransform &transform) const
    {
        return Pose(transform * pose_);
    }

    /**
     * @brief Transforms the current pose imperatively.
     * @param transform - the transformation to be applied.
     */
    void transform(const tf::Transform &transform)
    {
        pose_ = transform * pose_;
    }

    /**
     * @brief Transforms the current pose imperatively.
     * @param transform - the transformation to be applied.
     */
    void transform(const tf::StampedTransform &transform)
    {
        pose_ = transform * pose_;
    }

    inline Pose inverse() const
    {
        return Pose(pose_.inverse());
    }

    /**
     * @brief toString returns a formated string with the point contents.
     * @return  the formatted string with point data
     */
    inline std::string toString() const
    {
        std::stringstream ss;
        ss << "[[" << x() << ", " << y() << ", " << z() << "]," << std::endl;
        ss << "[" <<  yaw() << ", " << pitch() << ", " << roll() << "]]" << std::endl;
        return ss.str();
    }

private:
    tf::Pose pose_;
};
}
}

inline muse_amcl::math::Pose operator * (const muse_amcl::math::Pose &pose_a,
                                         const muse_amcl::math::Pose &pose_b)
{
    return pose_b.transformed(pose_a.getPose());
}

inline muse_amcl::math::Pose operator * (const muse_amcl::math::Pose &pose_a,
                                         const tf::Pose &pose_b)
{
    return muse_amcl::math::Pose(pose_a.getPose() * pose_b);
}

inline muse_amcl::math::Pose operator * (const tf::Transform &transform,
                                         const muse_amcl::math::Pose &pose)
{
    return pose.transformed(transform);
}

inline muse_amcl::math::Pose operator * (const tf::StampedTransform &transform,
                                         const muse_amcl::math::Pose &pose)
{
    return pose.transformed(transform);
}

#endif /* POSE_HPP */
