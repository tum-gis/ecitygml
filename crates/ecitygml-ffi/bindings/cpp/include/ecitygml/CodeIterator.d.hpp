#ifndef ecitygml_CodeIterator_D_HPP
#define ecitygml_CodeIterator_D_HPP

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
namespace capi { struct Code; }
class Code;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct CodeIterator;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Iterates over a list of codes (e.g. `gml:name`s), borrowed from a city model.
 */
class CodeIterator {
public:

  inline const ecitygml::Code* next() DIPLOMAT_LIFETIME_BOUND;

    inline const ecitygml::capi::CodeIterator* AsFFI() const;
    inline ecitygml::capi::CodeIterator* AsFFI();
    inline static const ecitygml::CodeIterator* FromFFI(const ecitygml::capi::CodeIterator* ptr);
    inline static ecitygml::CodeIterator* FromFFI(ecitygml::capi::CodeIterator* ptr);
    inline static void operator delete(void* ptr);
private:
    CodeIterator() = delete;
    CodeIterator(const ecitygml::CodeIterator&) = delete;
    CodeIterator(ecitygml::CodeIterator&&) noexcept = delete;
    CodeIterator operator=(const ecitygml::CodeIterator&) = delete;
    CodeIterator operator=(ecitygml::CodeIterator&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_CodeIterator_D_HPP
