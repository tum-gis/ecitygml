#ifndef ECITYGML_DirectPosition_D_HPP
#define ECITYGML_DirectPosition_D_HPP

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
namespace capi { struct DirectPosition; }
class DirectPosition;
namespace capi { struct Error; }
class Error;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct DirectPosition;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A 3D coordinate, created or borrowed from a city model.
 */
class DirectPosition {
public:

  /**
   * Creates a position; fails with `InvalidArgument` if a coordinate is NaN or infinite.
   */
  inline static ecitygml::diplomat::result<std::unique_ptr<ecitygml::DirectPosition>, std::unique_ptr<ecitygml::Error>> new_(double x, double y, double z);

  inline double x() const;

  inline double y() const;

  inline double z() const;

    inline const ecitygml::capi::DirectPosition* AsFFI() const;
    inline ecitygml::capi::DirectPosition* AsFFI();
    inline static const ecitygml::DirectPosition* FromFFI(const ecitygml::capi::DirectPosition* ptr);
    inline static ecitygml::DirectPosition* FromFFI(ecitygml::capi::DirectPosition* ptr);
    inline static void operator delete(void* ptr);
private:
    DirectPosition() = delete;
    DirectPosition(const ecitygml::DirectPosition&) = delete;
    DirectPosition(ecitygml::DirectPosition&&) noexcept = delete;
    DirectPosition operator=(const ecitygml::DirectPosition&) = delete;
    DirectPosition operator=(ecitygml::DirectPosition&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_DirectPosition_D_HPP
