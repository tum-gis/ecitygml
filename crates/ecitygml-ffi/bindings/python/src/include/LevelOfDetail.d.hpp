#ifndef ECITYGML_LevelOfDetail_D_HPP
#define ECITYGML_LevelOfDetail_D_HPP

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
class LevelOfDetail;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    enum LevelOfDetail {
      LevelOfDetail_Zero = 0,
      LevelOfDetail_One = 1,
      LevelOfDetail_Two = 2,
      LevelOfDetail_Three = 3,
    };

    typedef struct LevelOfDetail_option {union { LevelOfDetail ok; }; bool is_ok; } LevelOfDetail_option;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A CityGML level of detail (LoD 0 to 3).
 */
class LevelOfDetail {
public:
    enum Value {
        Zero = 0,
        One = 1,
        Two = 2,
        Three = 3,
    };

    LevelOfDetail(): value(Value::Zero) {}

    // Implicit conversions between enum and ::Value
    constexpr LevelOfDetail(Value v) : value(v) {}
    constexpr operator Value() const { return value; }
    // Prevent usage as boolean value
    explicit operator bool() const = delete;

  /**
   * The level as a number, e.g. 2 for `Two`.
   */
  inline size_t as_index() const;

  /**
   * The level with that number; fails with `InvalidArgument` above 3 (Rust: `TryFrom<u8>`).
   */
  inline static ecitygml::diplomat::result<ecitygml::LevelOfDetail, std::unique_ptr<ecitygml::Error>> try_from(uint8_t value);

    inline ecitygml::capi::LevelOfDetail AsFFI() const;
    inline static ecitygml::LevelOfDetail FromFFI(ecitygml::capi::LevelOfDetail c_enum);
private:
    Value value;
};

} // namespace
#endif // ECITYGML_LevelOfDetail_D_HPP
