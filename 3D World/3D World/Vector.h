#ifndef VECTOR_H_
#define VECTOR_H_

#include "Basic.h"

namespace mathtool
{
  class Vector3d 
  {
    public:
    //Constructors
    Vector3d(const double& _x = double(), const double& _y = double(), const double& _z = double()) 
    {
	    m_v[0] = _x; m_v[1] = _y; m_v[2] = _z;
    }

    Vector3d(const Vector3d& _v) 
    {
	    m_v[0] = _v[0]; m_v[1] = _v[1]; m_v[2] = _v[2];
    }

    Vector3d(const double (&_t)[3]) 
    {
	    m_v[0] = _t[0]; m_v[1] = _t[1]; m_v[2] = _t[2];
    }

    template <class Generator> Vector3d(const Generator& g)
    {
	    m_v[0] = g(); m_v[1] = g(); m_v[2] = g();
    }

    //Operator Overloading

    //Initialize Vector
    Vector3d& operator()(const double& _x, const double& _y, const double& _z)
    {
	    m_v[0] = _x; m_v[1] = _y; m_v[2] = _z;
	    return *this;
    }

    //Set Vector to another Vector
    Vector3d& operator=(const Vector3d& _v) 
    {
	    m_v[0] = _v[0]; m_v[1] = _v[1]; m_v[2] = _v[2];
	    return *this;
    }

    Vector3d& operator=(const double _v[3]) 
    {
        m_v[0] = _v[0]; m_v[1] = _v[1]; m_v[2] = _v[2];
	   return *this;
    }

    //Declare Constant Array
    typedef const double(&carr)[3];

    //Delcare Array
    typedef double (&arr)[3];
     
    //Get Contents of Array
    operator arr() 
    {
        return m_v;
    }

    //Get Contents of Constant Array
    operator carr() const 
    {
        return m_v;
    }

    //Get the Constant First Element of Vector
    const double* begin() const 
    {
        return m_v;
    }

      
    //Get the Constant Last Element of Vector
    const double* end() const 
    {
        return begin()+3;
    }

    //Get the First Element of Vector
    double* begin() 
    {
        return m_v;
    }

    //Get the Last Element of Vector
    double* end() 
    {
        return begin()+3;
    }

    //Determine if this vector is equal to another vector (EQUALS)
    bool operator==(const Vector3d& _v) const 
    {
	    return m_v[0] == _v[0] && m_v[1] == _v[1] && m_v[2] == _v[2];
    }

    //Determine if this vector is NOT equal to another vector (DOES NOT EQUAL)
    bool operator!=(const Vector3d& _v) const 
    {
	    return !(*this == _v);
    }

    //Perform self addition with another Vector
    Vector3d& operator+=(const Vector3d& _v) 
    {
        m_v[0] += _v[0]; m_v[1] += _v[1]; m_v[2] += _v[2];
	    return *this;
     }

    //Perform self subtraction with another Vector
    Vector3d& operator-=(const Vector3d& _v) 
    {
	    m_v[0] -= _v[0]; m_v[1] -= _v[1]; m_v[2] -= _v[2];
	    return *this;
    }

    //Perform Self-Scalar Multiplication with a double number
    Vector3d& operator*=(const double& _d) 
    {
	    m_v[0] *= _d; m_v[1] *= _d; m_v[2] *= _d;
	    return *this;
    }
      
    //Perform Self-Scalar Division with a double number
    Vector3d& operator/=(const double& _d) 
    {
	    m_v[0] /= _d; m_v[1] /= _d; m_v[2] /= _d;
	    return *this;
    }
      
    //Perform Self-Scalar Power with another Vector
    Vector3d& operator^=(const Vector3d& _v) 
    {
	    m_v[0] *= _v[0]; m_v[1] *= _v[1]; m_v[2] *= _v[2];
	    return *this;
    }

    //Perform Self-CrossProduct with another Vector
    Vector3d& operator%=(const Vector3d& _v) 
    {
	    double v0 = m_v[0], v1 = m_v[1], v2 = m_v[2];
	    m_v[0] = v1 * _v[2] - v2 * _v[1];
	    m_v[1] = v2 * _v[0] - v0 * _v[2];
	    m_v[2] = v0 * _v[1] - v1 * _v[0];
	    return *this;
    }

    //Negate the Values of the Vector
    Vector3d operator-() const 
    {
	    return Vector3d(-m_v[0], -m_v[1], -m_v[2]);
    }

    //Add the Values of the Current Vector to another Vector
    Vector3d operator+(const Vector3d& _v) const 
    {
        return Vector3d(m_v[0] + _v[0], m_v[1] + _v[1], m_v[2] + _v[2]);
    }

    //Subtract the Values fo the Current Vector to another Vector
    Vector3d operator-(const Vector3d& _v) const 
    {
	    return Vector3d(m_v[0] - _v[0], m_v[1] - _v[1], m_v[2] - _v[2]);
    }

    //Perform Scalar Multiplaction with double number
    Vector3d operator*(const double& _d) const 
    {
	    return Vector3d(m_v[0] * _d, m_v[1] * _d, m_v[2] * _d);
    }

    //Perform Scalar Division with double number
    Vector3d operator/(const double& _d) const 
    {
	    return Vector3d(m_v[0] / _d, m_v[1] / _d, m_v[2] / _d);
    }

    //Perform Power with another vector
    Vector3d operator^(const Vector3d& _v) const 
    {
	    return Vector3d(m_v[0] * _v[0], m_v[1] * _v[1], m_v[2] * _v[2]);
    }

    //Perform CrossProduct with another vector
    Vector3d operator%(const Vector3d& _v) const 
    {
	    Vector3d v(*this);
	    return v %= _v;
    }

    //Perform Dot Product with double number
    double operator*(const Vector3d& _v) const 
    {
	    return m_v[0]*_v[0] + m_v[1]*_v[1] + m_v[2]*_v[2];
    }

    //Get the Squared Root of the Vector
    double norm() const 
    {
	    return std::sqrt(normsqr());
    }

    //Get the Squared Version of the Vector
    double normsqr() const 
    {
	    return (*this)*(*this);
    }

    //Get the self Normalization of a Vector
    Vector3d& selfNormalize() 
    {
        double n = norm();
        if (n < std::numeric_limits<double>::epsilon())
        {
            return *this = Vector3d();
        } 
	    return *this /= n;
    }

    //Get the Normalization of a Vector
    Vector3d normalize() const 
    {
	    double n = norm();
        if (n < std::numeric_limits<double>::epsilon())
        {
            return Vector3d();
        }
	    return *this / n;
    }

    //Projections
    //find |component| of this along _v's direction
    double comp(Vector3d& _v) 
    {
	    return (*this) * _v.normalize();
    }

    //Self-Scale the Vector to the a certain Size
    Vector3d& selfScale(const double& _l) 
    {
	    double n = norm();
        if (n < std::numeric_limits<double>::epsilon())
        {
            return *this = Vector3d();
        }
	    return *this *= (_l/n);
    }

    //Scale the Vector to the a certain Size
    Vector3d scale(const double& _l) const 
    {
        double n = norm();
        if (n < std::numeric_limits<double>::epsilon())
        {
            return Vector3d();
        }
	    return *this * (_l/n);
      }

    //rotate vector

    //Rotate Vector About X-Axis for a given Radian-Value
    Vector3d& rotateX(double _rad) 
    {
	    double c = cos(_rad), s = sin(_rad);
	    return operator()(m_v[0], m_v[1]*c - m_v[2]*s, m_v[1]*s + m_v[2]*c);
    }

    //Rotate Vector About Y-Axis for a given Radian-Value
    Vector3d& rotateY(double _rad)
    {
        double c = cos(_rad), s = sin(_rad);
        return operator()(m_v[0] * c + m_v[2] * s, m_v[1], -m_v[0] * s + m_v[2] * c);
    }

    //Rotate Vector About Z-Axis for a given Radian-Value
    Vector3d& rotateZ(double _rad)
    {
        double c = cos(_rad), s = sin(_rad);
        return operator()(m_v[0] * c - m_v[1] * s, m_v[0] * s + m_v[1] * c, m_v[2]);
    }

    //Rotate Vector About X-Axis for a given Degree-Value
    Vector3d& rotateXd(double _deg) 
    {
        return rotateX(degToRad(_deg));
    }

    //Rotate Vector About Y-Axis for a given Degree-Value
    Vector3d& rotateYd(double _deg) 
    {
        return rotateY(degToRad(_deg));
    }

    //Rotate Vector About Z-Axis for a given Degree-Value
    Vector3d& rotateZd(double _deg) 
    {
        return rotateZ(degToRad(_deg));
    }

    //Set the Values of the Vector to Zero
    void reset() 
    {
	    m_v[0]=0; m_v[1]=0; m_v[2]=0;
    }

    //Get the X Value of the Vector
    double GetX() 
    { 
        return m_v[0]; 
    }

    //Get the Y Value of the Vector
    double GetY() 
    { 
        return m_v[1]; 
    }

    //Get the Z Value of the Vector
    double GetZ() 
    { 
        return m_v[2]; 
    }

    //Set the X Value of the Vector
    void SetX(double d) 
    { 
        m_v[0] = d; 
    }

    //Set the Y Value of the Vector
    void SetY(double d) 
    { 
        m_v[1] = d; 
    }

    //Set the Z Value of the Vector
    void SetZ(double d) 
    { 
        m_v[2] = d; 
    }

    private:
      //Variable that will store the Vector's Values in
      double m_v[3];
  };

  //////////////////////////////////////////////////////////////////////////////
  // Useful functions. Input/Output and commutativity on multiply
  //////////////////////////////////////////////////////////////////////////////
  //for commutativity of scalar multiply

  //Allow for User input for Vector
  inline std::istream& operator>>(std::istream& _is, Vector3d& _v) 
  {
	    double data[3];

        for (size_t i = 0; i < 3; ++i)
        {
            _is >> data[i];
            _v.SetX(data[0]);
            _v.SetY(data[1]);
            _v.SetZ(data[2]);
        }

      return _is;
  }

  //Allow for a const double to perform scalr multiplication for a vector
  inline Vector3d operator*(const double& _d, const Vector3d& _v) 
  {
        return _v*_d;
  }

  //Allow for Vector to be Outputted
  inline std::ostream& operator<<(std::ostream& _os, const Vector3d& _v) 
  {
      for (size_t i = 0; i < 3; ++i)
      {
          _os << _v[i] << " ";
      }

      return _os;
  }
}
#endif