/*-*- mode:c;indent-tabs-mode:t;c-basic-offset:8;tab-width:8;coding:utf-8   -*-│
│ vi: set noet ft=c ts=8 sw=8 fenc=utf-8                                   :vi │
╚──────────────────────────────────────────────────────────────────────────────╝
│                                                                              │
│  Musl Libc                                                                   │
│  Copyright © 2005-2014 Rich Felker, et al.                                   │
│                                                                              │
│  Permission is hereby granted, free of charge, to any person obtaining       │
│  a copy of this software and associated documentation files (the             │
│  "Software"), to deal in the Software without restriction, including         │
│  without limitation the rights to use, copy, modify, merge, publish,         │
│  distribute, sublicense, and/or sell copies of the Software, and to          │
│  permit persons to whom the Software is furnished to do so, subject to       │
│  the following conditions:                                                   │
│                                                                              │
│  The above copyright notice and this permission notice shall be              │
│  included in all copies or substantial portions of the Software.             │
│                                                                              │
│  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,             │
│  EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF          │
│  MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.      │
│  IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY        │
│  CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,        │
│  TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE           │
│  SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.                      │
│                                                                              │
╚─────────────────────────────────────────────────────────────────────────────*/
#define _BSD_SOURCE
#include <nl_types.h>
#include <string.h>
#include <stdint.h>
#include <endian.h>
#include <errno.h>
#include <langinfo.h>
#include <locale.h>
#include "third_party/musl/mapfile.internal.h"
#include <sys/mman.h>
__static_yoink("musl_libc_notice");

#define V(p) be32toh(*(uint32_t *)(p))

static nl_catd do_catopen(const char *name)
{
	size_t size;
	const unsigned char *map = __map_file(name, &size);
	/* Size recorded in the file must match file size; otherwise
	 * the information needed to unmap the file will be lost. */
	if (!map || V(map) != 0xff88ff89 || 20+V(map+8) != size) {
		if(map) munmap((void *)map, size);
		errno = ENOENT;
		return (nl_catd)-1;
	}
	return (nl_catd)map;
}

nl_catd catopen(const char *name, int oflag)
{
	nl_catd catd;

	if (strchr(name, '/')) return do_catopen(name);

	char buf[PATH_MAX];
	size_t i;
	const char *path, *lang, *p, *z;
	if (issetugid() || !(path = getenv("NLSPATH"))) {
		errno = ENOENT;
		return (nl_catd)-1;
	}
	lang = oflag ? nl_langinfo(_NL_LOCALE_NAME(LC_MESSAGES)) : getenv("LANG");
	if (!lang) lang = "";
	for (p=path; *p; p=z) {
		i = 0;
		z = strchrnul(p, ':');
		for (; p<z; p++) {
			const char *v;
			size_t l;
			if (*p!='%') v=p, l=1;
			else switch (*++p) {
			case 'N': v=name; l=strlen(v); break;
			case 'L': v=lang; l=strlen(v); break;
			case 'l': v=lang; l=strcspn(v,"_.@"); break;
			case 't':
				v=strchrnul(lang,'_');
				if (*v) v++;
				l=strcspn(v,".@");
				break;
			case 'c': v="UTF-8"; l=5; break;
			case '%': v="%"; l=1; break;
			default: v=0;
			}
			if (!v || l >= sizeof buf - i) {
				break;
			}
			memcpy(buf+i, v, l);
			i += l;
		}
		if (!*z && (p<z || !i)) break;
		if (p<z) continue;
		if (*z) z++;
		buf[i] = 0;
		/* Leading : or :: in NLSPATH is same as %N */
		catd = do_catopen(i ? buf : name);
		if (catd != (nl_catd)-1) return catd;
	}
	errno = ENOENT;
	return (nl_catd)-1;
}
