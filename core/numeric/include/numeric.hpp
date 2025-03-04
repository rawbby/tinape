#pragma once

#include "numeric/base.hpp"
#include "numeric/bits.hpp"
#include "numeric/repr.hpp"
#include "numeric/sign.hpp"

#include "numeric/int.hpp"
#include "numeric/int/comperator.hpp"
#include "numeric/int/literal.hpp"
#include "numeric/int/operator.hpp"

#include "numeric/fixed.hpp"
#include "numeric/fixed/comperator.hpp"
#include "numeric/fixed/literal.hpp"
#include "numeric/fixed/operator.hpp"

using numeric::i16;
using numeric::i32;
using numeric::i64;
using numeric::i8;

using numeric::u16;
using numeric::u32;
using numeric::u64;
using numeric::u8;

using numeric::Bits;
using numeric::Sign;

using numeric::as_fixed;
using numeric::Fixed;

using numeric::as_int;
using numeric::Int;

using numeric::operator+;
using numeric::operator-;
using numeric::operator*;
using numeric::operator/;
