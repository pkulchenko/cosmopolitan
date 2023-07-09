#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#───vi: set et ft=make ts=8 tw=8 fenc=utf-8 :vi───────────────────────┘
#
# SYNOPSIS
#
#   Cosmopolitan Runtime
#
# DESCRIPTION
#
#   This package exports essential routines for userspace process
#   initialization.

PKGS += LIBC_RUNTIME

LIBC_RUNTIME = $(LIBC_RUNTIME_A_DEPS) $(LIBC_RUNTIME_A)
LIBC_RUNTIME_ARTIFACTS += LIBC_RUNTIME_A
LIBC_RUNTIME_A = o/$(MODE)/libc/runtime/runtime.a
LIBC_RUNTIME_A_FILES := $(wildcard libc/runtime/*)
LIBC_RUNTIME_A_HDRS = $(filter %.h,$(LIBC_RUNTIME_A_FILES))
LIBC_RUNTIME_A_SRCS_S = $(filter %.S,$(LIBC_RUNTIME_A_FILES))
LIBC_RUNTIME_A_SRCS_C = $(filter %.c,$(LIBC_RUNTIME_A_FILES))

LIBC_RUNTIME_A_SRCS =					\
	$(LIBC_RUNTIME_A_SRCS_S)			\
	$(LIBC_RUNTIME_A_SRCS_C)

LIBC_RUNTIME_A_OBJS =					\
	$(LIBC_RUNTIME_A_SRCS_S:%.S=o/$(MODE)/%.o)	\
	$(LIBC_RUNTIME_A_SRCS_C:%.c=o/$(MODE)/%.o)

LIBC_RUNTIME_A_CHECKS =					\
	$(LIBC_RUNTIME_A).pkg				\
	$(LIBC_RUNTIME_A_HDRS:%=o/$(MODE)/%.ok)

LIBC_RUNTIME_A_DIRECTDEPS =				\
	LIBC_CALLS					\
	LIBC_ELF					\
	LIBC_FMT					\
	LIBC_INTRIN					\
	LIBC_NEXGEN32E					\
	LIBC_NT_ADVAPI32				\
	LIBC_NT_KERNEL32				\
	LIBC_NT_SYNCHRONIZATION				\
	LIBC_STR					\
	LIBC_SYSV					\
	LIBC_SYSV_CALLS					\
	THIRD_PARTY_PUFF				\
	THIRD_PARTY_XED

LIBC_RUNTIME_A_DEPS :=					\
	$(call uniq,$(foreach x,$(LIBC_RUNTIME_A_DIRECTDEPS),$($(x))))

$(LIBC_RUNTIME_A):					\
		libc/runtime/				\
		$(LIBC_RUNTIME_A).pkg			\
		$(LIBC_RUNTIME_A_OBJS)

$(LIBC_RUNTIME_A).pkg:					\
		$(LIBC_RUNTIME_A_OBJS)			\
		$(foreach x,$(LIBC_RUNTIME_A_DIRECTDEPS),$($(x)_A).pkg)

# we can't use asan and ubsan because:
#   asan and ubsan can be function traced
# we can't use function tracing because:
#   this is the function tracing runtime
o/$(MODE)/libc/runtime/cosmo2.o: private		\
		CFLAGS += -O0

o/$(MODE)/libc/runtime/ftracer.o: private		\
		CFLAGS +=				\
			-x-no-pg			\
			-ffreestanding			\
			-fno-sanitize=all

o/$(MODE)/libc/runtime/cosmo2.o				\
o/$(MODE)/libc/runtime/fork-nt.o			\
o/$(MODE)/libc/runtime/printmemoryintervals.o		\
o/$(MODE)/libc/runtime/arememoryintervalsok.o		\
o/$(MODE)/libc/runtime/findmemoryinterval.o		\
o/$(MODE)/libc/runtime/sys_mprotect.greg.o		\
o/$(MODE)/libc/runtime/getdosargv.o			\
o/$(MODE)/libc/runtime/getdosenviron.o			\
o/$(MODE)/libc/runtime/hook.greg.o			\
o/$(MODE)/libc/runtime/ismemtracked.greg.o		\
o/$(MODE)/libc/runtime/memtracknt.o			\
o/$(MODE)/libc/runtime/memtrack.greg.o			\
o/$(MODE)/libc/runtime/metalprintf.greg.o		\
o/$(MODE)/libc/runtime/printargs.greg.o			\
o/$(MODE)/libc/runtime/mman.greg.o			\
o/$(MODE)/libc/runtime/print.greg.o			\
o/$(MODE)/libc/runtime/stackchkfail.o			\
o/$(MODE)/libc/runtime/stackchkfaillocal.o		\
o/$(MODE)/libc/runtime/winmain.greg.o			\
o/$(MODE)/libc/runtime/opensymboltable.o: private	\
		CFLAGS +=				\
			-Os				\
			-ffreestanding			\
			$(NO_MAGIC)

# must use alloca()
# can't use asan or any runtime services
o/$(MODE)/libc/runtime/fork-nt.o: private		\
		CPPFLAGS +=				\
			-DSTACK_FRAME_UNLIMITED

o/$(MODE)/libc/runtime/qsort.o: private			\
		CFLAGS +=				\
			-Og

# make always linked runtimes less huge when it's profitable
o//libc/runtime/mmap.o					\
o//libc/runtime/munmap.o				\
o//libc/runtime/memtrack.greg.o				\
o//libc/runtime/opensymboltable.greg.o: private		\
		CFLAGS +=				\
			-Os

ifeq ($(ARCH), aarch64)
o/$(MODE)/libc/runtime/mmap.o				\
o/$(MODE)/libc/runtime/enable_tls.o: private		\
		CFLAGS +=				\
			-mcmodel=large
endif

# privileged functions
o/$(MODE)/libc/runtime/getsymbol.o			\
o/$(MODE)/libc/runtime/enable_threads.o			\
o/$(MODE)/libc/runtime/morph_tls.o: private		\
		CFLAGS +=				\
			-ffreestanding			\
			-fno-sanitize=all

# TODO(jart): We need a way to avoid WinThreadEntry() being hooked.
o/$(MODE)/libc/runtime/clone.o: private			\
		COPTS +=				\
			-fno-sanitize=all		\
			-fpatchable-function-entry=0,0

# these assembly files are safe to build on aarch64
o/$(MODE)/libc/runtime/init.o: libc/runtime/init.S
	@$(COMPILE) -AOBJECTIFY.S $(OBJECTIFY.S) $(OUTPUT_OPTION) -c $<
o/$(MODE)/libc/runtime/wipe.o: libc/runtime/wipe.S
	@$(COMPILE) -AOBJECTIFY.S $(OBJECTIFY.S) $(OUTPUT_OPTION) -c $<
o/$(MODE)/libc/runtime/vfork.o: libc/runtime/vfork.S
	@$(COMPILE) -AOBJECTIFY.S $(OBJECTIFY.S) $(OUTPUT_OPTION) -c $<
o/$(MODE)/libc/runtime/clone-linux.o: libc/runtime/clone-linux.S
	@$(COMPILE) -AOBJECTIFY.S $(OBJECTIFY.S) $(OUTPUT_OPTION) -c $<
o/$(MODE)/libc/runtime/ftrace-hook.o: libc/runtime/ftrace-hook.S
	@$(COMPILE) -AOBJECTIFY.S $(OBJECTIFY.S) $(OUTPUT_OPTION) -c $<
o/$(MODE)/libc/runtime/dsohandle.o: libc/runtime/dsohandle.S
	@$(COMPILE) -AOBJECTIFY.S $(OBJECTIFY.S) $(OUTPUT_OPTION) -c $<

LIBC_RUNTIME_LIBS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)))
LIBC_RUNTIME_SRCS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)_SRCS))
LIBC_RUNTIME_HDRS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)_HDRS))
LIBC_RUNTIME_BINS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)_BINS))
LIBC_RUNTIME_CHECKS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)_CHECKS))
LIBC_RUNTIME_OBJS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)_OBJS))
LIBC_RUNTIME_TESTS = $(foreach x,$(LIBC_RUNTIME_ARTIFACTS),$($(x)_TESTS))
$(LIBC_RUNTIME_OBJS): $(BUILD_FILES) libc/runtime/runtime.mk

.PHONY: o/$(MODE)/libc/runtime
o/$(MODE)/libc/runtime: $(LIBC_RUNTIME_CHECKS)
