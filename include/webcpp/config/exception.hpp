#ifndef NEROLL_WEBCPP_CONFIG_EXCEPTION_HPP
#define NEROLL_WEBCPP_CONFIG_EXCEPTION_HPP

/// Define `WEBCPP_NO_EXCEPTION` when exceptions are disabled.
#ifdef WEBCPP_NO_EXCEPTION
    #include <print>
    #include <stacktrace>

    #define WEBCPP_TRY
    #define WEBCPP_THROW(ex)                                                                       \
        do {                                                                                       \
            auto stack = std::stacktrace::current();                                               \
            std::println(stderr, "{}", (ex).what());                                               \
            std::println(stderr, "{}", stack);                                                     \
            std::abort();                                                                          \
        } while (false);
#else
    #define WEBCPP_TRY       try
    #define WEBCPP_THROW(ex) throw(ex)
#endif

#endif