#ifndef ecitygml_TriangleIterator_D_HPP
#define ecitygml_TriangleIterator_D_HPP

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
namespace capi { struct Triangle; }
class Triangle;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TriangleIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over triangles (e.g. of a triangulated surface), borrowed from a city model.
 */
class TriangleIterator {
public:

  inline const ecitygml::Triangle* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::TriangleIterator* AsFFI() const;
    inline ecitygml::capi::TriangleIterator* AsFFI();
    inline static const ecitygml::TriangleIterator* FromFFI(const ecitygml::capi::TriangleIterator* ptr);
    inline static ecitygml::TriangleIterator* FromFFI(ecitygml::capi::TriangleIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TriangleIterator() = delete;
    TriangleIterator(const ecitygml::TriangleIterator&) = delete;
    TriangleIterator(ecitygml::TriangleIterator&&) noexcept = delete;
    TriangleIterator operator=(const ecitygml::TriangleIterator&) = delete;
    TriangleIterator operator=(ecitygml::TriangleIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TriangleIterator_D_HPP
