#include "Vector2D.hpp"

Vector2D::Vector2D() {
  x = 0.0f;
  y = 0.0f;
}

Vector2D::Vector2D(float x, float y) {
  this->x = x;
  this->y = y;
}

Vector2D& Vector2D::Add(const Vector2D& vec) {
  this->x += vec.x;
  this->y += vec.y;

  return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec) {
  this->x -= vec.x;
  this->y -= vec.y;

  return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec) {
  this->x *= vec.x;
  this->y *= vec.y;

  return *this;
}

Vector2D& Vector2D::Divide(const Vector2D& vec) {
  this->x += vec.x;
  this->y += vec.y;

  return *this;
}

Vector2D& operator+(Vector2D& v1, const Vector2D& v2) { return v1.Add(v2); }

Vector2D& operator-(Vector2D& v1, const Vector2D& v2) {
  return v1.Subtract(v2);
}

Vector2D& operator*(Vector2D& v1, const Vector2D& v2) {
  return v1.Multiply(v2);
}

Vector2D& operator/(Vector2D& v1, const Vector2D& v2) { return v1.Divide(v2); }

Vector2D& Vector2D::operator+=(const Vector2D& vec) { return this->Add(vec); }

Vector2D& Vector2D::operator-=(const Vector2D& vec) {
  return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec) {
  return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec) {
  return this->Divide(vec);
}

Vector2D& Vector2D::operator*(const int& i) {
  this->x *= i;
  this->y *= i;

  return *this;
}

Vector2D& Vector2D::Zero() {
  this->x = 0;
  this->y = 0;

  return *this;
}

Vector2D Vector2D::Normalize() {
  float mag = Magnitude();
  // printf("Magnitude %f\n", mag );
  return Vector2D(x / mag, y / mag);
}

float Vector2D::Magnitude() {
  // printf("x = %f, y = %f \n",this->x,this->y );
  return (float)sqrt((x * x) + (y * y));
}

/*double Vector2D::Angle(){
        if (x == 0) // special cases
        return (y > 0)? 90
            : (y == 0)? 0
            : 270;
    else if (y == 0) // special cases
        return (x >= 0)? 0
            : 180;
    int ret = radToDeg(atanf((float)y/x));
    if (x < 0 && y < 0) // quadrant Ⅲ
        ret = 180 + ret;
    else if (x < 0) // quadrant Ⅱ
        ret = 180 + ret; // it actually substracts
    else if (y < 0) // quadrant Ⅳ
        ret = 270 + (90 + ret); // it actually substracts
    return ret;
}*/

std::ostream& operator<<(std::ostream& stream, const Vector2D& vec) {
  stream << "(" << vec.x << "," << vec.y << ")";
  return stream;
}