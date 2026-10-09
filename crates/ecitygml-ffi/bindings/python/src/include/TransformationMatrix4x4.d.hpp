#ifndef ECITYGML_TransformationMatrix4x4_D_HPP
#define ECITYGML_TransformationMatrix4x4_D_HPP

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
namespace capi { struct Error; }
class Error;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct TransformationMatrix4x4;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A 4x4 transformation matrix, borrowed from a city model.
 */
class TransformationMatrix4x4 {
public:

  /**
   * The entry at `row` and `column` (0 to 3), as nalgebra's `matrix()[(row, column)]`; fails
   * with `InvalidArgument` instead of panicking above 3. Rust's `to_row_major()` returns a
   * `Vec`, which the Python backend can only return through NumPy.
   */
  inline ecitygml::diplomat::result<double, std::unique_ptr<ecitygml::Error>> get(size_t row, size_t column) const;

    inline const ecitygml::capi::TransformationMatrix4x4* AsFFI() const;
    inline ecitygml::capi::TransformationMatrix4x4* AsFFI();
    inline static const ecitygml::TransformationMatrix4x4* FromFFI(const ecitygml::capi::TransformationMatrix4x4* ptr);
    inline static ecitygml::TransformationMatrix4x4* FromFFI(ecitygml::capi::TransformationMatrix4x4* ptr);
    inline static void operator delete(void* ptr);
private:
    TransformationMatrix4x4() = delete;
    TransformationMatrix4x4(const ecitygml::TransformationMatrix4x4&) = delete;
    TransformationMatrix4x4(ecitygml::TransformationMatrix4x4&&) noexcept = delete;
    TransformationMatrix4x4 operator=(const ecitygml::TransformationMatrix4x4&) = delete;
    TransformationMatrix4x4 operator=(ecitygml::TransformationMatrix4x4&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_TransformationMatrix4x4_D_HPP
