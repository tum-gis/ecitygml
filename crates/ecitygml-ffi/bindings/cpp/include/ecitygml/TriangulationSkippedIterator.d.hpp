#ifndef ecitygml_TriangulationSkippedIterator_D_HPP
#define ecitygml_TriangulationSkippedIterator_D_HPP

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
namespace capi { struct Error; }
class Error;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct TriangulationSkippedIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over the errors of skipped members, borrowed from a triangulation.
 */
class TriangulationSkippedIterator {
public:

  inline std::unique_ptr<ecitygml::Error> next();

    inline const ecitygml::capi::TriangulationSkippedIterator* AsFFI() const;
    inline ecitygml::capi::TriangulationSkippedIterator* AsFFI();
    inline static const ecitygml::TriangulationSkippedIterator* FromFFI(const ecitygml::capi::TriangulationSkippedIterator* ptr);
    inline static ecitygml::TriangulationSkippedIterator* FromFFI(ecitygml::capi::TriangulationSkippedIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    TriangulationSkippedIterator() = delete;
    TriangulationSkippedIterator(const ecitygml::TriangulationSkippedIterator&) = delete;
    TriangulationSkippedIterator(ecitygml::TriangulationSkippedIterator&&) noexcept = delete;
    TriangulationSkippedIterator operator=(const ecitygml::TriangulationSkippedIterator&) = delete;
    TriangulationSkippedIterator operator=(ecitygml::TriangulationSkippedIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_TriangulationSkippedIterator_D_HPP
