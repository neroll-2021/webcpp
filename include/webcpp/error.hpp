#ifndef NEROLL_WEBCPP_ERROR_HPP
#define NEROLL_WEBCPP_ERROR_HPP

#include <format>
#include <stdexcept>
#include <utility>

#include <webcpp/config/exception.hpp>

namespace webcpp {

class log_error : public std::runtime_error {
 public:
    explicit log_error(const std::string &message) : std::runtime_error(message) {}
};

/**
 * Throws an exception or terminates the program depending on the configuration.
 *
 * Throws an exception if exceptions are enabled.
 * Prints the message and stack trace, then calls std::abort if exceptions are disabled.
 */
template <typename Exception, typename... Args>
[[noreturn]]
void throw_exception(std::format_string<Args...> fmt, Args &&...args) {
    WEBCPP_THROW(Exception(std::format(fmt, std::forward<Args>(args)...)));
}

} // namespace webcpp

#endif