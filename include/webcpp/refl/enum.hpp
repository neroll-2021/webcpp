#ifndef NEROLL_WEBCPP_REFL_ENUM_HPP
#define NEROLL_WEBCPP_REFL_ENUM_HPP

#include <array>
#include <cassert>
#include <cstddef>
#include <string_view>
#include <type_traits>
#include <utility>

namespace webcpp::refl {

/** 
 * Gets the name of enum value.
 * 
 * @tparam Value Enum value.
 * @return The name of enum value
 */
template <auto Value>
    requires std::is_enum_v<decltype(Value)>
consteval auto enum_name() {
    std::string_view name;
#if __GNUC__ || __clang__
    name = __PRETTY_FUNCTION__;
    std::size_t start = name.find('=') + 2;
    std::size_t end = name.size() - 1;
    name = std::string_view{name.data() + start, end - start};
    start = name.rfind("::");
#elif _MSC_VER
    name = __FUNCSIG__;
    std::size_t start = name.find('<') + 1;
    std::size_t end = name.rfind(">(");
    name = std::string_view{name.data() + start, end - start};
    start = name.rfind("::");
#endif
    return start == std::string_view::npos
               ? name
               : std::string_view{name.data() + start + 2, name.size() - start - 2};
}

/**
 * Gets the number of enum values in enum.
 *
 * @tparam T Type of enum.
 * @return The number of enum values in enum.
 *
 * @note This function only works on enum that has continuous enum values.
 */
template <typename T, std::size_t N = 0>
    requires std::is_enum_v<T>
consteval auto enum_max() {
    constexpr auto value = static_cast<T>(N);
    if constexpr (enum_name<value>().find(")") == std::string_view::npos)
        return enum_max<T, N + 1>();
    else
        return N;
}

/**
 * Gets the names of all enum values in enum.
 *
 * @tparam E Type of enum.
 * @return Name of all enum values in enum.
 *
 * @note This function only works on enum that has continuous enum values.
 */
template <typename E>
    requires std::is_enum_v<E>
consteval auto enum_names() {
    auto names = []<std::size_t... Is>(std::index_sequence<Is...>) {
        return std::array{enum_name<static_cast<E>(Is)>()...};
    }(std::make_index_sequence<enum_max<E>()>{});
    return names;
}

/**
 * Gets the name of given enum value.
 *
 * @tparam E Type of enum.
 * @param value Enum value.
 * @return The name of enum value.
 */
template <typename E>
    requires std::is_enum_v<E>
constexpr auto enum_name(E value) {
    static constexpr auto names = enum_names<E>();
    assert(static_cast<std::size_t>(value) < names.size() && "invalid enum value");
    return names[static_cast<std::size_t>(value)];
}

} // namespace webcpp::refl

#endif