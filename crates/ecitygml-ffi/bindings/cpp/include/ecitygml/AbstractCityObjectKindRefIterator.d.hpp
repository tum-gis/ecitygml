#ifndef ecitygml_AbstractCityObjectKindRefIterator_D_HPP
#define ecitygml_AbstractCityObjectKindRefIterator_D_HPP

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
namespace capi { struct AbstractCityObjectKindRef; }
class AbstractCityObjectKindRef;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct AbstractCityObjectKindRefIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over city objects of a city model, which it borrows.
 */
class AbstractCityObjectKindRefIterator {
public:

  inline std::unique_ptr<ecitygml::AbstractCityObjectKindRef> next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::AbstractCityObjectKindRefIterator* AsFFI() const;
    inline ecitygml::capi::AbstractCityObjectKindRefIterator* AsFFI();
    inline static const ecitygml::AbstractCityObjectKindRefIterator* FromFFI(const ecitygml::capi::AbstractCityObjectKindRefIterator* ptr);
    inline static ecitygml::AbstractCityObjectKindRefIterator* FromFFI(ecitygml::capi::AbstractCityObjectKindRefIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    AbstractCityObjectKindRefIterator() = delete;
    AbstractCityObjectKindRefIterator(const ecitygml::AbstractCityObjectKindRefIterator&) = delete;
    AbstractCityObjectKindRefIterator(ecitygml::AbstractCityObjectKindRefIterator&&) noexcept = delete;
    AbstractCityObjectKindRefIterator operator=(const ecitygml::AbstractCityObjectKindRefIterator&) = delete;
    AbstractCityObjectKindRefIterator operator=(ecitygml::AbstractCityObjectKindRefIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_AbstractCityObjectKindRefIterator_D_HPP
