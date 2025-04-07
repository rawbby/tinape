#pragma once
#include <cstdio>
#include <csignal>
// clang-format off
#define STRINGIFY(X)#X
#define TOSTRING(X)STRINGIFY(X)
#define VOID ((void)0)
#define ABORT() raise(SIGABRT)
#define RANGE_1 0
#define RANGE_2 0,1
#define RANGE_3 0,1,2
#define RANGE_4 0,1,2,3
#define RANGE_5 0,1,2,3,4
#define RANGE_6 0,1,2,3,4,5
#define RANGE_7 0,1,2,3,4,5,6
#define RANGE_8 0,1,2,3,4,5,6,7
#define RANGE_9 0,1,2,3,4,5,6,7,8
#define RANGE_10 0,1,2,3,4,5,6,7,8,9
#define RANGE_11 0,1,2,3,4,5,6,7,8,9,10
#define RANGE_12 0,1,2,3,4,5,6,7,8,9,10,11
#define RANGE_13 0,1,2,3,4,5,6,7,8,9,10,11,12
#define RANGE_14 0,1,2,3,4,5,6,7,8,9,10,11,12,13
#define RANGE_15 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14
#define RANGE_16 0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15
#define MACRO_MAP16(_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15,_16,VALUE,...)VALUE
#define PACK(...)(__VA_ARGS__)
#define UNPACK_IMPL_(...)__VA_ARGS__
#define UNPACK(PACKED_ARG)UNPACK_IMPL_ PACKED_ARG
#define JOIN_UNPACK(PACKED_ARG)JOIN(,UNPACK(PACKED_ARG))
#define FOR_EACH_0(F,...)
#define FOR_EACH_1(F,x0,...)F(x0)
#define FOR_EACH_2(F,x0,x1,...)F(x0),F(x1)
#define FOR_EACH_3(F,x0,x1,x2,...)F(x0),F(x1),F(x2)
#define FOR_EACH_4(F,x0,x1,x2,x3,...)F(x0),F(x1),F(x2),F(x3)
#define FOR_EACH_5(F,x0,x1,x2,x3,x4,...)F(x0),F(x1),F(x2),F(x3),F(x4)
#define FOR_EACH_6(F,x0,x1,x2,x3,x4,x5,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5)
#define FOR_EACH_7(F,x0,x1,x2,x3,x4,x5,x6,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6)
#define FOR_EACH_8(F,x0,x1,x2,x3,x4,x5,x6,x7,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7)
#define FOR_EACH_9(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8)
#define FOR_EACH_10(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9)
#define FOR_EACH_11(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9),F(x10)
#define FOR_EACH_12(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9),F(x10),F(x11)
#define FOR_EACH_13(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9),F(x10),F(x11),F(x12)
#define FOR_EACH_14(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9),F(x10),F(x11),F(x12),F(x13)
#define FOR_EACH_15(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9),F(x10),F(x11),F(x12),F(x13),F(x14)
#define FOR_EACH_16(F,x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15,...)F(x0),F(x1),F(x2),F(x3),F(x4),F(x5),F(x6),F(x7),F(x8),F(x9),F(x10),F(x11),F(x12),F(x13),F(x14),F(x15)
#define FOR_EACH(F,...)MACRO_MAP16(__VA_ARGS__,FOR_EACH_16,FOR_EACH_15,FOR_EACH_14,FOR_EACH_13,FOR_EACH_12,FOR_EACH_11,FOR_EACH_10,FOR_EACH_9,FOR_EACH_8,FOR_EACH_7,FOR_EACH_6,FOR_EACH_5,FOR_EACH_4,FOR_EACH_3,FOR_EACH_2,FOR_EACH_1,FOR_EACH_0)(F,__VA_ARGS__)
#define POP_0()
#define POP_1(_0)
#define POP_2(_0,_1)_0
#define POP_3(_0,_1,_2)_0,_1
#define POP_4(_0,_1,_2,_3)_0,_1,_2
#define POP_5(_0,_1,_2,_3,_4)_0,_1,_2,_3
#define POP_6(_0,_1,_2,_3,_4,_5)_0,_1,_2,_3,_4
#define POP_7(_0,_1,_2,_3,_4,_5,_6)_0,_1,_2,_3,_4,_5
#define POP_8(_0,_1,_2,_3,_4,_5,_6,_7)_0,_1,_2,_3,_4,_5,_6
#define POP_9(_0,_1,_2,_3,_4,_5,_6,_7,_8)_0,_1,_2,_3,_4,_5,_6,_7
#define POP_10(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)_0,_1,_2,_3,_4,_5,_6,_7,_8
#define POP_11(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)_0,_1,_2,_3,_4,_5,_6,_7,_8,_9
#define POP_12(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10
#define POP_13(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11
#define POP_14(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12
#define POP_15(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13
#define POP_16(_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14
#define POP(...)MACRO_MAP16(__VA_ARGS__,POP_16,POP_15,POP_14,POP_13,POP_12,POP_11,POP_10,POP_9,POP_8,POP_7,POP_6,POP_5,POP_4,POP_3,POP_2,POP_1,POP_0)(__VA_ARGS__)
#define ENUMERATE_0(F)
#define ENUMERATE_1(F,_0)F(0,_0)
#define ENUMERATE_2(F,_0,_1)F(0,_0),F(1,_1)
#define ENUMERATE_3(F,_0,_1,_2)F(0,_0),F(1,_1),F(2,_2)
#define ENUMERATE_4(F,_0,_1,_2,_3)F(0,_0),F(1,_1),F(2,_2),F(3,_3)
#define ENUMERATE_5(F,_0,_1,_2,_3,_4)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4)
#define ENUMERATE_6(F,_0,_1,_2,_3,_4,_5)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5)
#define ENUMERATE_7(F,_0,_1,_2,_3,_4,_5,_6)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6)
#define ENUMERATE_8(F,_0,_1,_2,_3,_4,_5,_6,_7)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7)
#define ENUMERATE_9(F,_0,_1,_2,_3,_4,_5,_6,_7,_8)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8)
#define ENUMERATE_10(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9)
#define ENUMERATE_11(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9),F(10,_10)
#define ENUMERATE_12(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9),F(10,_10),F(11,_11)
#define ENUMERATE_13(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9),F(10,_10),F(11,_11),F(12,_12)
#define ENUMERATE_14(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9),F(10,_10),F(11,_11),F(12,_12),F(13,_13)
#define ENUMERATE_15(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9),F(10,_10),F(11,_11),F(12,_12),F(13,_13),F(14,_14)
#define ENUMERATE_16(F,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)F(0,_0),F(1,_1),F(2,_2),F(3,_3),F(4,_4),F(5,_5),F(6,_6),F(7,_7),F(8,_8),F(9,_9),F(10,_10),F(11,_11),F(12,_12),F(13,_13),F(14,_14),F(15,_15)
#define ENUMERATE(F,...)MACRO_MAP16(__VA_ARGS__,ENUMERATE_16,ENUMERATE_15,ENUMERATE_14,ENUMERATE_13,ENUMERATE_12,ENUMERATE_11,ENUMERATE_10,ENUMERATE_9,ENUMERATE_8,ENUMERATE_7,ENUMERATE_6,ENUMERATE_5,ENUMERATE_4,ENUMERATE_3,ENUMERATE_2,ENUMERATE_1,ENUMERATE_0)(F,__VA_ARGS__)
#define ARGC(...)MACRO_MAP16(__VA_ARGS__,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0)
#define HEAD_IMPL_(HEAD,...)HEAD
#define HEAD(...)HEAD_IMPL_(__VA_ARGS__)
#define TAIL_IMPL_(HEAD,...)__VA_ARGS__
#define TAIL(...)TAIL_IMPL_(__VA_ARGS__)
#define REVERSE_0(...)
#define REVERSE_1(x0)x0
#define REVERSE_2(x0,x1)x1,x0
#define REVERSE_3(x0,x1,x2)x2,x1,x0
#define REVERSE_4(x0,x1,x2,x3)x3,x2,x1,x0
#define REVERSE_5(x0,x1,x2,x3,x4)x4,x3,x2,x1,x0
#define REVERSE_6(x0,x1,x2,x3,x4,x5)x5,x4,x3,x2,x1,x0
#define REVERSE_7(x0,x1,x2,x3,x4,x5,x6)x6,x5,x4,x3,x2,x1,x0
#define REVERSE_8(x0,x1,x2,x3,x4,x5,x6,x7)x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_9(x0,x1,x2,x3,x4,x5,x6,x7,x8)x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_10(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9)x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_11(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10)x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_12(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11)x11,x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_13(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12)x12,x11,x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_14(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13)x13,x12,x11,x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_15(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14)x14,x13,x12,x11,x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE_16(x0,x1,x2,x3,x4,x5,x6,x7,x8,x9,x10,x11,x12,x13,x14,x15)x15,x14,x13,x12,x11,x10,x9,x8,x7,x6,x5,x4,x3,x2,x1,x0
#define REVERSE(...)MACRO_MAP16(__VA_ARGS__,REVERSE_16,REVERSE_15,REVERSE_14,REVERSE_13,REVERSE_12,REVERSE_11,REVERSE_10,REVERSE_9,REVERSE_8,REVERSE_7,REVERSE_6,REVERSE_5,REVERSE_4,REVERSE_3,REVERSE_2,REVERSE_1)(__VA_ARGS__)
#define JOIN_0()
#define JOIN_1(S,_0)_0
#define JOIN_2(S,_0,_1)_0 S _1
#define JOIN_3(S,_0,_1,_2)_0 S _1 S _2
#define JOIN_4(S,_0,_1,_2,_3)_0 S _1 S _2 S _3
#define JOIN_5(S,_0,_1,_2,_3,_4)_0 S _1 S _2 S _3 S _4
#define JOIN_6(S,_0,_1,_2,_3,_4,_5)_0 S _1 S _2 S _3 S _4 S _5
#define JOIN_7(S,_0,_1,_2,_3,_4,_5,_6)_0 S _1 S _2 S _3 S _4 S _5 S _6
#define JOIN_8(S,_0,_1,_2,_3,_4,_5,_6,_7)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7
#define JOIN_9(S,_0,_1,_2,_3,_4,_5,_6,_7,_8)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8
#define JOIN_10(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9
#define JOIN_11(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9 S _10
#define JOIN_12(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9 S _10 S _11
#define JOIN_13(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9 S _10 S _11 S _12
#define JOIN_14(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9 S _10 S _11 S _12 S _13
#define JOIN_15(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9 S _10 S _11 S _12 S _13 S _14
#define JOIN_16(S,_0,_1,_2,_3,_4,_5,_6,_7,_8,_9,_10,_11,_12,_13,_14,_15)_0 S _1 S _2 S _3 S _4 S _5 S _6 S _7 S _8 S _9 S _10 S _11 S _12 S _13 S _14 S _15
#define JOIN(S,...)MACRO_MAP16(__VA_ARGS__,JOIN_16,JOIN_15,JOIN_14,JOIN_13,JOIN_12,JOIN_11,JOIN_10,JOIN_9,JOIN_8,JOIN_7,JOIN_6,JOIN_5,JOIN_4,JOIN_3,JOIN_2,JOIN_1)(S,__VA_ARGS__)
// clang-format on
