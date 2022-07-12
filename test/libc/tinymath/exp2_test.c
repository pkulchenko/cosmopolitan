/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2021 Justine Alexandra Roberts Tunney                              │
│                                                                              │
│ Permission to use, copy, modify, and/or distribute this software for         │
│ any purpose with or without fee is hereby granted, provided that the         │
│ above copyright notice and this permission notice appear in all copies.      │
│                                                                              │
│ THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL                │
│ WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED                │
│ WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE             │
│ AUTHOR BE LIABLE FOR ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL         │
│ DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR        │
│ PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE OR OTHER               │
│ TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR             │
│ PERFORMANCE OF THIS SOFTWARE.                                                │
╚─────────────────────────────────────────────────────────────────────────────*/
#include "libc/math.h"
#include "libc/runtime/gc.internal.h"
#include "libc/testlib/ezbench.h"
#include "libc/testlib/testlib.h"
#include "libc/x/x.h"

#define exp2l(x) exp2l(VEIL("t", (long double)(x)))
#define exp2(x)  exp2(VEIL("x", (double)(x)))
#define exp2f(x) exp2f(VEIL("x", (float)(x)))

TEST(exp2l, test) {
  EXPECT_STREQ("1", gc(xdtoal(exp2l(0))));
  EXPECT_STREQ("1", gc(xdtoal(exp2l(-0.))));
  EXPECT_STREQ("INFINITY", gc(xdtoal(exp2l(INFINITY))));
  EXPECT_STREQ("0", gc(xdtoal(exp2l(-INFINITY))));
  EXPECT_STREQ("NAN", gc(xdtoal(exp2l(NAN))));
  EXPECT_STREQ("0", gc(xdtoal(exp2l(-132098844872390))));
  EXPECT_STREQ("INFINITY", gc(xdtoal(exp2l(132098844872390))));
}

TEST(exp2, test) {
  EXPECT_STREQ("1", gc(xdtoa(exp2(0))));
  EXPECT_STREQ("1", gc(xdtoa(exp2(-0.))));
  EXPECT_STREQ("INFINITY", gc(xdtoa(exp2(INFINITY))));
  EXPECT_STREQ("0", gc(xdtoa(exp2(-INFINITY))));
  EXPECT_STREQ("NAN", gc(xdtoa(exp2(NAN))));
  EXPECT_STREQ("0", gc(xdtoa(exp2(-132098844872390))));
  EXPECT_STREQ("INFINITY", gc(xdtoa(exp2(132098844872390))));
}

TEST(exp2f, test) {
  EXPECT_STREQ("1", gc(xdtoaf(exp2f(0))));
  EXPECT_STREQ("1", gc(xdtoaf(exp2f(-0.))));
  EXPECT_STREQ("INFINITY", gc(xdtoaf(exp2f(INFINITY))));
  EXPECT_STREQ("0", gc(xdtoaf(exp2f(-INFINITY))));
  EXPECT_STREQ("NAN", gc(xdtoaf(exp2f(NAN))));
  EXPECT_STREQ("0", gc(xdtoaf(exp2f(-132098844872390))));
  EXPECT_STREQ("INFINITY", gc(xdtoaf(exp2f(132098844872390))));
}

BENCH(exp2l, bench) {
  double _exp2(double) asm("exp2");
  float _exp2f(float) asm("exp2f");
  long double _exp2l(long double) asm("exp2l");
  EZBENCH2("exp2", donothing, _exp2(.7));   /*  ~6ns */
  EZBENCH2("exp2f", donothing, _exp2f(.7)); /*  ~5ns */
  EZBENCH2("exp2l", donothing, _exp2l(.7)); /* ~30ns */
}
