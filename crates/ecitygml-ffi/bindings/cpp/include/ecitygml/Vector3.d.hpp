#ifndef ecitygml_Vector3_D_HPP
#define ecitygml_Vector3_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "../diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    struct Vector3 {
      double x;
      double y;
      double z;
    };

    typedef struct Vector3_option {union { Vector3 ok; }; bool is_ok; } Vector3_option;
} // namespace capi
} // namespace


namespace ecitygml {
/**
 * A 3D vector, passed by value (e.g. the translation of `CityModel::apply_translation`).
 */
struct Vector3 {
    double x;
    double y;
    double z;

    inline ecitygml::capi::Vector3 AsFFI() const;
    inline static ecitygml::Vector3 FromFFI(ecitygml::capi::Vector3 c_struct);
};

} // namespace
#endif // ecitygml_Vector3_D_HPP
