// Light (abstract class) declarations

#include "Light.hpp"
#include "RGB_Color.hpp"

namespace RT {
    
    Light::Light() : color(1.0, 1.0, 1.0) {}
    Light::Light(const RGB_Color& color) : r(color.r), g(color.g), b(color.b) {}
    Light::~Light() {}
}