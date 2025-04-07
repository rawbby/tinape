#pragma once

#include "./macro.hpp"

#include <string>

#ifndef NDEBUG
#define DEBUG
#include <csignal>
#define DBREAK() raise(SIGTRAP)
#else
#define DBREAK() VOID
#endif

#define ASSERT(c, ...)                                                     \
  do {                                                                     \
    if (c)                                                                 \
      break;                                                               \
                                                                           \
    fputs("[ASSERTION FAILED]\n", stderr);                                 \
    fputs("  Condition  : " #c "\n", stderr);                              \
    fputs("  Location   : " __FILE__ ":" TOSTRING(__LINE__) "\n", stderr); \
                                                                           \
    __VA_OPT__(                                                            \
      fputs("  Details   : ", stderr);                                     \
      fprintf(stderr, __VA_ARGS__);                                        \
      fputc('\n', stderr);)                                                \
                                                                           \
    DBREAK();                                                              \
    ABORT();                                                               \
                                                                           \
  } while (false)

#define ASSERT_OP(op, l, r, ...)                                           \
  do {                                                                     \
    if ((l)op(r))                                                          \
      break;                                                               \
                                                                           \
    const auto fputa = [](auto v, auto file) {                             \
      if constexpr (requires { std::to_string(v); }) {                     \
        const auto f = std::to_string(v);                                  \
        fputs(f.c_str(), file);                                            \
      } else {                                                             \
        fputc('?', file);                                                  \
      }                                                                    \
    };                                                                     \
                                                                           \
    fputs("[ASSERTION FAILED]\n", stderr);                                 \
    fputs("  Condition  : " #l " " #op " " #r "\n", stderr);               \
    fputs("  Location   : " __FILE__ ":" TOSTRING(__LINE__) "\n", stderr); \
    fputs("  Evaluation : ", stderr);                                      \
    fputa(l, stderr);                                                      \
    fputs(" " #op " ", stderr);                                            \
    fputa(r, stderr);                                                      \
    fputc('\n', stderr);                                                   \
                                                                           \
    __VA_OPT__(                                                            \
      fputs("  Details   : ", stderr);                                     \
      fprintf(stderr, __VA_ARGS__);                                        \
      fputc('\n', stderr);)                                                \
                                                                           \
    DBREAK();                                                              \
    ABORT();                                                               \
                                                                           \
  } while (false)

#define ASSERT_EQ(l, r, ...) ASSERT_OP(==, l, r, __VA_ARGS__)
#define ASSERT_NE(l, r, ...) ASSERT_OP(!=, l, r, __VA_ARGS__)
#define ASSERT_LE(l, r, ...) ASSERT_OP(<=, l, r, __VA_ARGS__)
#define ASSERT_GE(l, r, ...) ASSERT_OP(>=, l, r, __VA_ARGS__)
#define ASSERT_LT(l, r, ...) ASSERT_OP(<, l, r, __VA_ARGS__)
#define ASSERT_GT(l, r, ...) ASSERT_OP(>, l, r, __VA_ARGS__)

#define ASSERT_BETWEEN(v, l, h, ...) \
  ASSERT_GE(v, l, __VA_ARGS__);      \
  ASSERT_LE(v, h, __VA_ARGS__)

#define ASSERT_EQ_TOLERANCE(v, r, t, ...) \
  ASSERT_LE(v, (r) + (t), __VA_ARGS__);   \
  ASSERT_LE((r) - (t), v, __VA_ARGS__)

#ifdef DEBUG
#define DASSERT(...) ASSERT(__VA_ARGS__)
#define DASSERT_EQ(...) ASSERT_EQ(__VA_ARGS__)
#define DASSERT_NE(...) ASSERT_NE(__VA_ARGS__)
#define DASSERT_LT(...) ASSERT_LT(__VA_ARGS__)
#define DASSERT_LE(...) ASSERT_LE(__VA_ARGS__)
#define DASSERT_GT(...) ASSERT_GT(__VA_ARGS__)
#define DASSERT_GE(...) ASSERT_GE(__VA_ARGS__)
#define DASSERT_BETWEEN(...) ASSERT_BETWEEN(__VA_ARGS__)
#else
#define DASSERT(...) VOID
#define DASSERT_EQ(...) VOID
#define DASSERT_NE(...) VOID
#define DASSERT_LT(...) VOID
#define DASSERT_LE(...) VOID
#define DASSERT_GT(...) VOID
#define DASSERT_GE(...) VOID
#define DASSERT_BETWEEN(...) VOID
#endif
