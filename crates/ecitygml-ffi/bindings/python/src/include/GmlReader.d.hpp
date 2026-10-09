#ifndef ECITYGML_GmlReader_D_HPP
#define ECITYGML_GmlReader_D_HPP

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
namespace capi { struct GmlReader; }
class GmlReader;
class CitygmlFormat;
} // namespace ecitygml



namespace ecitygml {
namespace capi {
    struct GmlReader;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * Reads CityGML from a file or from memory. Rust's builder methods take the reader by value,
 * which Diplomat can't express: here they modify it in place, and `finish` can be called only once.
 */
class GmlReader {
public:

  /**
   * Reads CityGML content of the given `format` from memory, e.g. in WebAssembly, where there is
   * no file system. The data is copied.
   */
  inline static std::unique_ptr<ecitygml::GmlReader> new_(ecitygml::diplomat::span<const uint8_t> data, ecitygml::CitygmlFormat format);

  /**
   * Opens the CityGML file at `path` (`.gml`, `.gml.gz` or `.gml.zst`).
   */
  inline static ecitygml::diplomat::result<std::unique_ptr<ecitygml::GmlReader>, std::unique_ptr<ecitygml::Error>> from_path(std::string_view path);

  /**
   * Whether envelopes of child objects are recomputed from their geometry (default: true).
   * Has no effect after `finish`.
   */
  inline void with_rebuild_object_bounds(bool rebuild_object_bounds);

  /**
   * Reads the city model; fails with `InvalidArgument` if called a second time.
   */
  inline ecitygml::diplomat::result<std::unique_ptr<ecitygml::CityModel>, std::unique_ptr<ecitygml::Error>> finish();

    inline const ecitygml::capi::GmlReader* AsFFI() const;
    inline ecitygml::capi::GmlReader* AsFFI();
    inline static const ecitygml::GmlReader* FromFFI(const ecitygml::capi::GmlReader* ptr);
    inline static ecitygml::GmlReader* FromFFI(ecitygml::capi::GmlReader* ptr);
    inline static void operator delete(void* ptr);
private:
    GmlReader() = delete;
    GmlReader(const ecitygml::GmlReader&) = delete;
    GmlReader(ecitygml::GmlReader&&) noexcept = delete;
    GmlReader operator=(const ecitygml::GmlReader&) = delete;
    GmlReader operator=(ecitygml::GmlReader&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ECITYGML_GmlReader_D_HPP
