#include <environment/contact/vertex_contact.h>

using namespace XBot::HyperGraph;
using namespace g2o;

VertexContact::VertexContact():
BaseVertex<7, Contact>()
{}

bool VertexContact::read(std::istream& is) {
  return true;
}

bool VertexContact::write(std::ostream& os) const {
  return true;
}

void VertexContact::print() const
{
    std::cout << "VertexContact -- ID: " << _id << std::endl;
    std::cout << "distal link: " << _estimate.getDistalLink() << std::endl;
    std::cout << "pose: \n" << _estimate.state.pose.matrix() << std::endl;
    std::cout << "time: " << _estimate.state.time << std::endl;
}

void VertexContact::setToOriginImpl()
{
    _estimate.state.pose.setIdentity();
}

bool VertexContact::setEstimateDataImpl(const double* est)
{
    Utils::vectorToContact(est, _estimate);
    return true;
}

bool VertexContact::getEstimateData(double* est) const
{
    Utils::contactToVector(_estimate, est);
    return true;
}

void VertexContact::oplusImpl(const double* update)
{
    Contact increment;
//    std::cout << "UPDATE" << std::endl;
//    for (int i = 0; i < 7; i++)
//        std::cout << update[i] << std::endl;
    Utils::vectorToContact(update, increment);
//    std::cout << "-------------------" << std::endl;
//    std::cout << increment.state.pose.matrix() << std::endl;
//    std::cout << "-------------------" << std::endl;
    _estimate.state.pose = _estimate.state.pose * increment.state.pose;
}

void Utils::vectorToContact(const double* v, Contact& c)
{
    c.state.pose.translation() << v[0], v[1], v[2];
    c.state.pose.linear() = Eigen::Quaternion<double>(v[6], v[3], v[4], v[5]).toRotationMatrix();
}

void Utils::contactToVector(const Contact c, double* v)
{
    Eigen::Map<Eigen::Matrix<double, 7, 1>> est(v);
    est.head(3) = c.state.pose.translation();
    Eigen::Quaternion<double> q(c.state.pose.linear());
    est.tail(4) << q.coeffs().x(), q.coeffs().y(), q.coeffs().z(), q.coeffs().w();
}
