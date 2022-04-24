/*-*- mode:c;indent-tabs-mode:nil;c-basic-offset:2;tab-width:8;coding:utf-8 -*-│
│vi: set net ft=c ts=2 sts=2 sw=2 fenc=utf-8                                :vi│
╞══════════════════════════════════════════════════════════════════════════════╡
│ Copyright 2020 Justine Alexandra Roberts Tunney                              │
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
#include "libc/assert.h"
#include "libc/bits/bits.h"
#include "libc/calls/internal.h"
#include "libc/calls/struct/timeval.h"
#include "libc/nt/winsock.h"
#include "libc/sock/internal.h"
#include "libc/sock/yoink.inc"
#include "libc/str/str.h"
#include "libc/sysv/consts/so.h"
#include "libc/sysv/consts/sol.h"
#include "libc/sysv/errfuns.h"

textwindows int sys_getsockopt_nt(struct Fd *fd, int level, int optname,
                                  void *out_opt_optval,
                                  uint32_t *inout_optlen) {
  uint64_t ms;
  uint32_t in_optlen;
  assert(fd->kind == kFdSocket);

  if (out_opt_optval && inout_optlen) {
    in_optlen = *inout_optlen;
  } else {
    in_optlen = 0;
  }

  // TODO(jart): Use WSAIoctl?
  if (__sys_getsockopt_nt(fd->handle, level, optname, out_opt_optval,
                          inout_optlen) == -1) {
    return __winsockerr();
  }

  if (level == SOL_SOCKET) {
    if ((optname == SO_RCVTIMEO || optname == SO_SNDTIMEO) &&
        in_optlen == sizeof(struct timeval) &&
        *inout_optlen == sizeof(uint32_t)) {
      ms = *(uint32_t *)out_opt_optval;
      ((struct timeval *)out_opt_optval)->tv_sec = ms / 1000;
      ((struct timeval *)out_opt_optval)->tv_usec = ms % 1000 * 1000;
      *inout_optlen = sizeof(struct timeval);
    }
  }

  if (in_optlen == 4 && *inout_optlen == 1) {
    // handle cases like this
    // getsockopt(8, SOL_TCP, TCP_FASTOPEN, [u"☺"], [1]) → 0
    int32_t wut = *(signed char *)out_opt_optval;
    memcpy(out_opt_optval, &wut, 4);
    *inout_optlen = 4;
  }

  return 0;
}
