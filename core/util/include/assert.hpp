#pragma once

#include <cstdio>
#include <string>

#ifndef NDEBUG
#define DEBUG
#ifdef _MSC_VER
#define DEBUG_BREAK() __debugbreak()
#else
#include <csignal>
#define DEBUG_BREAK() raise(SIGTRAP)
#endif
#else
#define DEBUG_BREAK() ((void)0)
#endif

namespace internal::assert {
template<typename T>
std::string
safe_to_string(const T& value)
{
  if constexpr (requires { std::to_string(value); })
    return std::to_string(value);
  else
    return std::string{ "?" };
}
}

#define ASSERT(cond, ...)                                                                         \
  do {                                                                                            \
    if (!(cond)) {                                                                                \
      std::fprintf(stderr,                                                                        \
                   "[ASSERTION FAILED]\n"                                                         \
                   "  Condition  : " #cond "\n"                                                   \
                   "  Location   : " __FILE__ ":" TOSTRING(__LINE__) "\n");                       \
      __VA_OPT__(std::fprintf(stderr, "  Details   : " __VA_ARGS__); std::fprintf(stderr, "\n");) \
      DEBUG_BREAK();                                                                              \
      std::abort();                                                                               \
    }                                                                                             \
  } while (false)

#define OPERATOR_ASSERT_FAIL_(op, lhs, rhs, ...)                                                \
  do {                                                                                          \
    const auto lhs_str = ::internal::assert::safe_to_string(lhs);                               \
    const auto rhs_str = ::internal::assert::safe_to_string(rhs);                               \
    std::fprintf(stderr,                                                                        \
                 "[ASSERTION FAILED]\n"                                                         \
                 "  Condition  : " #lhs " " op " " #rhs "\n"                                    \
                 "  Evaluation : %s " op " %s\n"                                                \
                 "  Location   : " __FILE__ ":" TOSTRING(__LINE__) "\n",                        \
                 lhs_str.c_str(),                                                               \
                 rhs_str.c_str());                                                              \
    __VA_OPT__(std::fprintf(stderr, "  Details   : " __VA_ARGS__); std::fprintf(stderr, "\n");) \
    DEBUG_BREAK();                                                                              \
    std::abort();                                                                               \
  } while (false)

#define ASSERT_EQ(lhs, rhs, ...)                          \
  do {                                                    \
    if (!((lhs) == (rhs))) {                              \
      OPERATOR_ASSERT_FAIL_("==", lhs, rhs, __VA_ARGS__); \
    }                                                     \
  } while (false)

#define ASSERT_NE(lhs, rhs, ...)                          \
  do {                                                    \
    if (!((lhs) != (rhs))) {                              \
      OPERATOR_ASSERT_FAIL_("!=", lhs, rhs, __VA_ARGS__); \
    }                                                     \
  } while (false)

#define ASSERT_LT(lhs, rhs, ...)                         \
  do {                                                   \
    if (!((lhs) < (rhs))) {                              \
      OPERATOR_ASSERT_FAIL_("<", lhs, rhs, __VA_ARGS__); \
    }                                                    \
  } while (false)

#define ASSERT_LE(lhs, rhs, ...)                          \
  do {                                                    \
    if (!((lhs) <= (rhs))) {                              \
      OPERATOR_ASSERT_FAIL_("<=", lhs, rhs, __VA_ARGS__); \
    }                                                     \
  } while (false)

#define ASSERT_GT(lhs, rhs, ...)                         \
  do {                                                   \
    if (!((lhs) > (rhs))) {                              \
      OPERATOR_ASSERT_FAIL_(">", lhs, rhs, __VA_ARGS__); \
    }                                                    \
  } while (false)

#define ASSERT_GE(lhs, rhs, ...)                          \
  do {                                                    \
    if (!((lhs) >= (rhs))) {                              \
      OPERATOR_ASSERT_FAIL_(">=", lhs, rhs, __VA_ARGS__); \
    }                                                     \
  } while (false)

#define ASSERT_BETWEEN(val, lo, hi, ...) \
  do {                                   \
    ASSERT_GE((val), (lo), __VA_ARGS__); \
    ASSERT_LE((val), (hi), __VA_ARGS__); \
  } while (false)

#define ASSERT_NEAR(lhs, rhs, tolerance, ...)                             \
  do {                                                                    \
    ASSERT_LE((lhs), (rhs) + std::abs((rhs) * (tolerance)), __VA_ARGS__); \
    ASSERT_GE((lhs) + std::abs((lhs) * (tolerance)), (rhs), __VA_ARGS__); \
  } while (false)

#ifdef DEBUG
#define DEBUG_ASSERT(cond, ...) ASSERT(cond, __VA_ARGS__)
#define DEBUG_ASSERT_EQ(lhs, rhs, ...) ASSERT_EQ(lhs, rhs, __VA_ARGS__)
#define DEBUG_ASSERT_NE(lhs, rhs, ...) ASSERT_NE(lhs, rhs, __VA_ARGS__)
#define DEBUG_ASSERT_LT(lhs, rhs, ...) ASSERT_LT(lhs, rhs, __VA_ARGS__)
#define DEBUG_ASSERT_LE(lhs, rhs, ...) ASSERT_LE(lhs, rhs, __VA_ARGS__)
#define DEBUG_ASSERT_GT(lhs, rhs, ...) ASSERT_GT(lhs, rhs, __VA_ARGS__)
#define DEBUG_ASSERT_GE(lhs, rhs, ...) ASSERT_GE(lhs, rhs, __VA_ARGS__)
#define DEBUG_ASSERT_BETWEEN(val, lo, hi, ...) ASSERT_BETWEEN(val, lo, hi, __VA_ARGS__)
#define DEBUG_ASSERT_NEAR(lhs, rhs, tolerance, ...) ASSERT_NEAR(lhs, rhs, tolerance, __VA_ARGS__)
#else
#define DEBUG_ASSERT(cond, ...) ((void)0)
#define DEBUG_ASSERT_EQ(lhs, rhs, ...) ((void)0)
#define DEBUG_ASSERT_NE(lhs, rhs, ...) ((void)0)
#define DEBUG_ASSERT_LT(lhs, rhs, ...) ((void)0)
#define DEBUG_ASSERT_LE(lhs, rhs, ...) ((void)0)
#define DEBUG_ASSERT_GT(lhs, rhs, ...) ((void)0)
#define DEBUG_ASSERT_GE(lhs, rhs, ...) ((void)0)
#define DEBUG_ASSERT_BETWEEN(val, lo, hi, ...) ((void)0)
#define DEBUG_ASSERT_NEAR(lhs, rhs, tolerance, ...) ((void)0)
#endif
