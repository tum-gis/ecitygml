#ifndef ecitygml_AbstractFeatureKindRefIterator_D_HPP
#define ecitygml_AbstractFeatureKindRefIterator_D_HPP

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
namespace capi { struct AbstractFeatureKindRef; }
class AbstractFeatureKindRef;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractFeatureKindRefIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over features of a city model, which it borrows.
 */
class AbstractFeatureKindRefIterator {
public:

  inline std::unique_ptr<ecitygml::AbstractFeatureKindRef> next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractFeatureKindRefIterator* AsFFI() const;
    inline ecitygml::capi::AbstractFeatureKindRefIterator* AsFFI();
    inline static const ecitygml::AbstractFeatureKindRefIterator* FromFFI(const ecitygml::capi::AbstractFeatureKindRefIterator* ptr);
    inline static ecitygml::AbstractFeatureKindRefIterator* FromFFI(ecitygml::capi::AbstractFeatureKindRefIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractFeatureKindRefIterator() = delete;
    AbstractFeatureKindRefIterator(const ecitygml::AbstractFeatureKindRefIterator&) = delete;
    AbstractFeatureKindRefIterator(ecitygml::AbstractFeatureKindRefIterator&&) noexcept = delete;
    AbstractFeatureKindRefIterator operator=(const ecitygml::AbstractFeatureKindRefIterator&) = delete;
    AbstractFeatureKindRefIterator operator=(ecitygml::AbstractFeatureKindRefIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractFeatureKindRefIterator_D_HPP
