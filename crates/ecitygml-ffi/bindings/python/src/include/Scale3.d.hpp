#ifndef ECITYGML_Scale3_D_HPP
#define ECITYGML_Scale3_D_HPP

#include <stdio.h>
#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>
#include <memory>
#include <functional>
#include <optional>
#include <cstdlib>
#include "diplomat_runtime.hpp"


namespace ecitygml {
namespace capi {
    struct Scale3 {
      double x;
      double y;
      double z;
    };

    typedef struct Scale3_option {union { Scale3 ok; }; bool is_ok; } Scale3_option;
} // namespace capi
} // namespace


namespace ecitygml {
/**
 * A scale factor per axis, passed by value (the argument of `CityModel::apply_scale`).
 */
struct Scale3 {
    double x;
    double y;
    double z;

    inline ecitygml::capi::Scale3 AsFFI() const;
    inline static ecitygml::Scale3 FromFFI(ecitygml::capi::Scale3 c_struct);
};

} // namespace
#endif // ECITYGML_Scale3_D_HPP
