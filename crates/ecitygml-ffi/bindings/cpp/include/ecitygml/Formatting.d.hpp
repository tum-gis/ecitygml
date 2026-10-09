#ifndef ecitygml_Formatting_D_HPP
#define ecitygml_Formatting_D_HPP

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
namespace capi { struct Formatting; }
class Formatting;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct Formatting;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * How written GML is laid out. Rust's enum variant `Indent` carries data, which Diplomat enums
 * can't, so each variant is a named constructor.
 */
class Formatting {
public:

  /**
   * All elements on a single line, without whitespace between them.
   */
  inline static std::unique_ptr<ecitygml::Formatting> compact();

  /**
   * Each element on its own line, without indentation (the default).
   */
  inline static std::unique_ptr<ecitygml::Formatting> new_line();

  /**
   * Each element on its own line, indented by `size` repetitions of the byte `char`, e.g.
   * `b' '` and 2.
   */
  inline static std::unique_ptr<ecitygml::Formatting> indent(uint8_t char_, size_t size);

    inline const ecitygml::capi::Formatting* AsFFI() const;
    inline ecitygml::capi::Formatting* AsFFI();
    inline static const ecitygml::Formatting* FromFFI(const ecitygml::capi::Formatting* ptr);
    inline static ecitygml::Formatting* FromFFI(ecitygml::capi::Formatting* ptr);
    inline static void operator delete(void* ptr);
private:
    Formatting() = delete;
    Formatting(const ecitygml::Formatting&) = delete;
    Formatting(ecitygml::Formatting&&) noexcept = delete;
    Formatting operator=(const ecitygml::Formatting&) = delete;
    Formatting operator=(ecitygml::Formatting&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_Formatting_D_HPP
