#ifndef NEROLL_WEBCPP_LOG_LOG_HPP
#define NEROLL_WEBCPP_LOG_LOG_HPP

#include <chrono>
#include <format>
#include <print>
#include <utility>

#include <webcpp/error.hpp>

namespace webcpp::log {

/// Level of log information.
enum class level {
    trace,
    debug,
    info,
    warn,
    error,
};

/// Logs a formatted informatted information wth given level.
template <typename... Args>
void log(level log_level, std::format_string<Args...> fmt, Args &&...args) {
    auto tag = [log_level] {
        switch (log_level) {
            case level::trace:
                return "\033[34mtrace\033[0m";
            case level::debug:
                return "\033[36mdebug\033[0m";
            case level::info:
                return "\033[32minfo\033[0m";
            case level::warn:
                return "\033[33mwarn\033[0m";
            case level::error:
                return "\033[31merror\033[0m";
            default:
                throw_exception<log_error>("invalid log level: {}", std::to_underlying(log_level));
        }
    }();
    auto now = std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());
    std::println("[{:%Y-%m-%d %H:%M:%S}] [{}] {}", now, tag,
                 std::format(fmt, std::forward<Args>(args)...));
}

/// Logs a formatted information with level `trace`.
template <typename... Args>
void trace(std::format_string<Args...> fmt, Args &&...args) {
    log(level::trace, fmt, std::forward<Args>(args)...);
}

/// Logs a formatted information with level `debug`.
template <typename... Args>
void debug(std::format_string<Args...> fmt, Args &&...args) {
    log(level::debug, fmt, std::forward<Args>(args)...);
}

/// Logs a formatted information with level `info`.
template <typename... Args>
void info(std::format_string<Args...> fmt, Args &&...args) {
    log(level::info, fmt, std::forward<Args>(args)...);
}

/// Logs a formatted information with level `warn`.
template <typename... Args>
void warn(std::format_string<Args...> fmt, Args &&...args) {
    log(level::warn, fmt, std::forward<Args>(args)...);
}

/// Logs a formatted information with level `error`.
template <typename... Args>
void error(std::format_string<Args...> fmt, Args &&...args) {
    log(level::error, fmt, std::forward<Args>(args)...);
}

} // namespace webcpp::log

#endif