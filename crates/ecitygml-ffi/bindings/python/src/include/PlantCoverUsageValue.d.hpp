#ifndef ECITYGML_PlantCoverUsageValue_D_HPP
#define ECITYGML_PlantCoverUsageValue_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct PlantCoverUsageValue;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * The `usage` property of a PlantCover.
 */
class PlantCoverUsageValue {
public:

  inline const ecitygml::Code& code() const DIPLOMAT_LIFETIME_BOUND;

  inline std::string_view value() const DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::PlantCoverUsageValue* AsFFI() const;
    inline ecitygml::capi::PlantCoverUsageValue* AsFFI();
    inline static const ecitygml::PlantCoverUsageValue* FromFFI(const ecitygml::capi::PlantCoverUsageValue* ptr);
    inline static ecitygml::PlantCoverUsageValue* FromFFI(ecitygml::capi::PlantCoverUsageValue* ptr);
    inline static void operator delete(void* ptr);
private:
    PlantCoverUsageValue() = delete;
    PlantCoverUsageValue(const ecitygml::PlantCoverUsageValue&) = delete;
    PlantCoverUsageValue(ecitygml::PlantCoverUsageValue&&) noexcept = delete;
    PlantCoverUsageValue operator=(const ecitygml::PlantCoverUsageValue&) = delete;
    PlantCoverUsageValue operator=(ecitygml::PlantCoverUsageValue&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_PlantCoverUsageValue_D_HPP
