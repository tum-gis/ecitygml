#ifndef ecitygml_ShellIterator_D_HPP
#define ecitygml_ShellIterator_D_HPP

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
namespace capi { struct Shell; }
class Shell;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct ShellIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over shells (e.g. a solid's interior shells), borrowed from a city model.
 */
class ShellIterator {
public:

  inline const ecitygml::Shell* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::ShellIterator* AsFFI() const;
    inline ecitygml::capi::ShellIterator* AsFFI();
    inline static const ecitygml::ShellIterator* FromFFI(const ecitygml::capi::ShellIterator* ptr);
    inline static ecitygml::ShellIterator* FromFFI(ecitygml::capi::ShellIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    ShellIterator() = delete;
    ShellIterator(const ecitygml::ShellIterator&) = delete;
    ShellIterator(ecitygml::ShellIterator&&) noexcept = delete;
    ShellIterator operator=(const ecitygml::ShellIterator&) = delete;
    ShellIterator operator=(ecitygml::ShellIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_ShellIterator_D_HPP
