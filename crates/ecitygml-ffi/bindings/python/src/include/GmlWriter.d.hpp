#ifndef ECITYGML_GmlWriter_D_HPP
#define ECITYGML_GmlWriter_D_HPP

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
namespace capi { struct CityModel; }
class CityModel;
namespace capi { struct Error; }
class Error;
namespace capi { struct Formatting; }
class Formatting;
namespace capi { struct GmlWriter; }
class GmlWriter;
class CitygmlFormat;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct GmlWriter;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Writes CityGML to a file or to memory. Rust's builder methods take the writer by value and
 * `finish` consumes it, which Diplomat can't express: here they modify it in place, and
 * `finish` can be called only once.
 */
class GmlWriter {
public:

  /**
   * Creates (or truncates) the file at `path`; its extension (`.gml`, `.gml.gz` or
   * `.gml.zst`) sets the format.
   */
  inline static ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>> from_path(std::string_view path);

  /**
   * Creates (or truncates) the file `<base_path>.<extension of format>`.
   */
  inline static ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlWriter>, std::unique_ptr<ecitygml::Error>> from_base_path_with_format(std::string_view base_path, ecitygml::CitygmlFormat format);

  /**
   * How the GML is laid out (default: `Formatting::new_line`). Has no effect after `finish`.
   */
  inline void with_formatting(const ecitygml::Formatting& formatting);

  /**
   * Writes the city model; fails with `InvalidArgument` if called a second time.
   */
  inline ecitygml::diplomat::result<std::monostate, std::unique_ptr<ecitygml::Error>> finish(const ecitygml::CityModel& city_model);

    inline const ecitygml::capi::GmlWriter* AsFFI() const;
    inline ecitygml::capi::GmlWriter* AsFFI();
    inline static const ecitygml::GmlWriter* FromFFI(const ecitygml::capi::GmlWriter* ptr);
    inline static ecitygml::GmlWriter* FromFFI(ecitygml::capi::GmlWriter* ptr);
    inline static void operator delete(void* ptr);
private:
    GmlWriter() = delete;
    GmlWriter(const ecitygml::GmlWriter&) = delete;
    GmlWriter(ecitygml::GmlWriter&&) noexcept = delete;
    GmlWriter operator=(const ecitygml::GmlWriter&) = delete;
    GmlWriter operator=(ecitygml::GmlWriter&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_GmlWriter_D_HPP
