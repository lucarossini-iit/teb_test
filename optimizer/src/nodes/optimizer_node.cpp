#include <optimizer/optimizer.h>

#include <cartesio_planning/planner/cartesio_ompl_planner.h>
#include <cartesio_planning/validity_checker/validity_checker_context.h>
#include <cartesio_planning/interpolator/cartesian_trajectory_interpolation.h>
#include <cartesio_planning/utils/robot_viz.h>

std::vector<Eigen::VectorXd> readFromFileConfigs(std::string fileName){
    std::string filePrefix = "/home/luca/MultiDoF-superbuild/external/teb_test/config/";
    std::string filePath = filePrefix + fileName + ".txt";
    std::ifstream fileIn(filePath.c_str());
    std::string line;
    std::vector<Eigen::VectorXd> qList;

    int rate_index = 0;

    while(getline(fileIn, line))
    {
        if (rate_index % 10 == 0)
        {
            std::stringstream linestream(line);
            std::string value;
            Eigen::VectorXd q(18);
            int index = 0;

            while(linestream >> value)
            {
                q(index) = boost::lexical_cast<double>(value);
                index++;
            }
            qList.push_back(q);
        }
        rate_index++;
    }
    return qList;
}

int main(int argc, char** argv)
{
    ros::init(argc, argv, "optimizer_node");
    ros::NodeHandle nh(""), nhpr("~");

    auto cfg = XBot::ConfigOptionsFromParamServer();
    auto model = XBot::ModelInterface::getModel(cfg);
    XBot::Cartesian::Utils::RobotStatePublisher rspub(model);

    std::vector<Eigen::VectorXd> qList = readFromFileConfigs("joint_position");
    std::cout << "loaded " << qList.size() << " configurations" << std::endl;

    ros::Rate r(100);

    for (auto q : qList)
    {
        model->setJointPosition(q);
        model->update();
        rspub.publishTransforms(ros::Time::now(), "");
        r.sleep();
    }

    return true;
}
