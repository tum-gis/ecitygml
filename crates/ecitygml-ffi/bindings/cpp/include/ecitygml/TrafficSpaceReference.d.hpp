#ifndef ecitygml_TrafficSpaceReference_D_HPP
#define ecitygml_TrafficSpaceReference_D_HPP

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
    struct TrafficSpaceReference;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * A reference to a traffic space by `xlink:href`, borrowed from a city model. Like in Rust, it
 * has no accessors of its own: convert it with `Reference::from_traffic_space_reference`.
 */
class TrafficSpaceReference {
public:

    inline const ecitygml::capi::TrafficSpaceReference* AsFFI() const;
    inline ecitygml::capi::TrafficSpaceReference* AsFFI();
    inline static const ecitygml::TrafficSpaceReference* FromFFI(const ecitygml::capi::TrafficSpaceReference* ptr);
    inline static ecitygml::TrafficSpaceReference* FromFFI(ecitygml::capi::TrafficSpaceReference* ptr);
    inline static void operator delete(void* ptr);
private:
    TrafficSpaceReference() = delete;
    TrafficSpaceReference(const ecitygml::TrafficSpaceReference&) = delete;
    TrafficSpaceReference(ecitygml::TrafficSpaceReference&&) noexcept = delete;
    TrafficSpaceReference operator=(const ecitygml::TrafficSpaceReference&) = delete;
    TrafficSpaceReference operator=(ecitygml::TrafficSpaceReference&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TrafficSpaceReference_D_HPP
