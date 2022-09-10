#ifndef RGB_TPP
#define RGB_TPP

template<typename T>
class RGB_t {
  private:
public:
  T r, g, b;
  RGB_t() : r(0), g(0), b(0) {}
  RGB_t(T r, T g, T b) : r(r), g(g), b(b) {}
  
  RGB_t(const RGB_t& other) = default;
  RGB_t& operator=(const RGB_t& other) =  default;

  RGB_t& operator+=(const RGB_t& other) {
    r += other.r;
    g += other.g;
    b += other.b;
    return *this;
  }
  RGB_t& operator-=(const RGB_t& other) {
    r -= other.r;
    g -= other.g;
    b -= other.b;
    return *this;
  }
  RGB_t& operator*=(const RGB_t& other) {
    r *= other.r;
    g *= other.g;
    b *= other.b;
    return *this;
  }
  RGB_t& operator/=(const RGB_t& other) {
    r /= other.r;
    g /= other.g;
    b /= other.b;
    return *this;
  }
  RGB_t& operator*=(T scalar) {
    r *= scalar;
    g *= scalar;
    b *= scalar;
    return *this;
  }
  RGB_t& operator/=(T scalar) {
    r /= scalar;
    g /= scalar;
    b /= scalar;
    return *this;
  }
};

#endif // RGB_TPP
