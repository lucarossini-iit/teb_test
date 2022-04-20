#ifndef VERTEX_CONTACT_H
#define VERTEX_CONTACT_H

#include <g2o/core/base_vertex.h>

#include <environment/contact/contact.h>

using namespace g2o;

namespace XBot { namespace HyperGraph {

class VertexContact : public BaseVertex<7, Contact> {
public:
    EIGEN_MAKE_ALIGNED_OPERATOR_NEW;
    VertexContact();

    virtual void setToOriginImpl();

    virtual bool read(std::istream& is);
    virtual bool write(std::ostream& os) const;
    void print() const;

    virtual bool setEstimateDataImpl(const double* est);
    virtual bool getEstimateData(double* est) const;
    virtual int estimateDimension() const { return 7; }

    virtual bool setMinimalEstimateDataImpl(const double* est) { return setEstimateDataImpl(est); }
    virtual bool getMinimalEstimateDataImpl(double* est) { return getEstimateData(est); }
    virtual int minimalEstimateDimension() const { return estimateDimension(); }

    virtual void oplusImpl(const double* update);

};

namespace Utils {
void vectorToContact(const double* v, Contact& c);
void contactToVector(const Contact c, double* v);
}
} }
#endif // VERTEX_CONTACT_H
