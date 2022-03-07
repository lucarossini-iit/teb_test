#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <visualization_msgs/Marker.h>

namespace XBot { namespace HyperGraph {

struct obstacle {
    Eigen::Vector3d position;
    Eigen::Quaternion<double> orientation;
    Eigen::Affine3d T;
    Eigen::Vector3d size;
    std::string frame_id;
    visualization_msgs::Marker::_type_type type;
    int id;
};
} }

#endif // OBSTACLE_H
