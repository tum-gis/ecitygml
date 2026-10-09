#ifndef ecitygml_Error_D_HPP
#define ecitygml_Error_D_HPP

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
class ErrorKind;
} // namespace ecitygml




namespace ecitygml {
namespace capi {
    struct Error;
} // namespace capi
} // namespace

namespace ecitygml {
/**
 * An error with its kind and a human-readable message.
 */
class Error {
public:

  inline ecitygml::ErrorKind kind() const;

  inline std::string message() const;
  template<typename W>
  inline void message_write(W& writeable_output) const;

    inline const ecitygml::capi::Error* AsFFI() const;
    inline ecitygml::capi::Error* AsFFI();
    inline static const ecitygml::Error* FromFFI(const ecitygml::capi::Error* ptr);
    inline static ecitygml::Error* FromFFI(ecitygml::capi::Error* ptr);
    inline static void operator delete(void* ptr);
private:
    Error() = delete;
    Error(const ecitygml::Error&) = delete;
    Error(ecitygml::Error&&) noexcept = delete;
    Error operator=(const ecitygml::Error&) = delete;
    Error operator=(ecitygml::Error&&) noexcept = delete;
    static void operator delete[](void*, size_t) = delete;
};

} // namespace
#endif // ecitygml_Error_D_HPP
