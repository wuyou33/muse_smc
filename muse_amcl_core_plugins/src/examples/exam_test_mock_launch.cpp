#include <muse_amcl/plugins/plugin_factory.hpp>
#include <muse_amcl/data_sources/map_provider.hpp>
#include <muse_amcl/data_sources/data_provider.hpp>
#include <muse_amcl/data_sources/tf_provider.hpp>

#include <muse_amcl/particle_filter/update_forwarder.hpp>
#include <muse_amcl/particle_filter/prediction_forwarder.hpp>
#include <muse_amcl/particle_filter/resampling.hpp>
#include <muse_amcl/particle_filter/sampling_uniform.hpp>
#include <muse_amcl/particle_filter/sampling_normal.hpp>


#include "../mock/mock_update.h"
#include "../mock/mock_propagation.h"
#include "../mock/mock_data.hpp"

#include <muse_amcl/plugins/plugin_loader.hpp>

#include <ros/ros.h>
#include <regex>
#include <boost/regex.hpp>

int main(int argc, char *argv[])
{
    ros::init(argc, argv, "muse_amcl_exam_test_mock_launch");
    ros::NodeHandle nh("~");

    /// direct access
    std::string update_class;
    std::string update_class_base;
    nh.getParam("update0/class", update_class);
    nh.getParam("update0/base_class", update_class_base);


    std::string propagation_class;
    std::string propagation_class_base;
    nh.getParam("propagation0/class", propagation_class);
    nh.getParam("propagation0/base_class", propagation_class_base);

    std::cout << "update " << std::endl;
    std::cout << update_class_base << " :: " << update_class << std::endl;

    std::cout << "propagation " << std::endl;
    std::cout << propagation_class_base << " :: " << propagation_class << std::endl;

    muse_amcl::TFProvider::Ptr tf(new muse_amcl::TFProvider);

    /// iteration
    std::map<std::string, muse_amcl::UpdateModel::Ptr> updates;
    muse_amcl::PredictionModel::Ptr prediction;
    muse_amcl::UniformSampling::Ptr uniform_pose_generation;
    muse_amcl::NormalSampling::Ptr  normal_pose_generation;
    muse_amcl::Resampling::Ptr            resampling;
    std::map<std::string, muse_amcl::MapProvider::Ptr> maps;
    std::map<std::string, muse_amcl::DataProvider::Ptr> datas;

    muse_amcl::PluginLoader loader(nh);

    loader.load<muse_amcl::UpdateModel, muse_amcl::TFProvider::Ptr, ros::NodeHandle&>(updates, tf, nh);
    loader.load<muse_amcl::PredictionModel, muse_amcl::TFProvider::Ptr, ros::NodeHandle&>(prediction, tf, nh);
    loader.load<muse_amcl::MapProvider, ros::NodeHandle&>(maps, nh);
    loader.load<muse_amcl::DataProvider, ros::NodeHandle&>(datas, nh);

    using MapProviders = std::map<std::string, muse_amcl::MapProvider::Ptr>;
    using TFProvider = muse_amcl::TFProvider::Ptr;

    loader.load<muse_amcl::UniformSampling, MapProviders, TFProvider, ros::NodeHandle&>(uniform_pose_generation, maps, tf, nh);
    loader.load<muse_amcl::NormalSampling, MapProviders, TFProvider, ros::NodeHandle&>(normal_pose_generation, maps, tf, nh);
    loader.load<muse_amcl::Resampling, muse_amcl::UniformSampling::Ptr, ros::NodeHandle&>(resampling, uniform_pose_generation, nh);

    std::cout << "updates      " << updates.size() << std::endl;
    std::cout << "propagations " << (prediction ? 1 : 0) << std::endl;
    std::cout << "maps         " << maps.size() << std::endl;
    std::cout << "datas        " << datas.size() << std::endl;
    std::cout << "uniform pose " << (uniform_pose_generation ? 1 : 0) << std::endl;
    std::cout << "normal pose  " << (normal_pose_generation ? 1 : 0) << std::endl;
    std::cout << "resampling   " << (resampling ? 1 : 0) << std::endl;

    muse_amcl::Data::ConstPtr data;
    muse_amcl::Map::ConstPtr map;
    muse_amcl::Indexation index({0.1, 0.1, 1./18. * M_PI});
    muse_amcl::ParticleSet set("frame", 1, index);
    std::cout << "updates first" << std::endl;
//    for(auto &u : updates) {
//        u.second->update(data, map, set.getWeights());

//    }
//    std::cout << "propagations second" << std::endl;
//    prediction->predict(data, set.getPoses());

//    muse_amcl::UpdateQueue   uq;
//    muse_amcl::UpdateManager um(updates, uq);
//    um.bind(datas,
//            maps,
//            nh);



//    muse_amcl::PropagationQueue   pq;
//    muse_amcl::PropagationManager pm(prediction, pq);
//    pm.bind(datas, nh);

//    for(auto &d : datas) {
//        d.second->enable();
//    }

//    while(uq.size() < 10 || pq.size() < 10) {
//        std::cout << " ++ " << uq.size() << " " << pq.size() << std::endl;

//        ros::spinOnce();
//        ros::Rate(3).sleep();
//    }

//    ros::shutdown();

    return 0;
}
