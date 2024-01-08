#-*-mode:makefile-gmake;indent-tabs-mode:t;tab-width:8;coding:utf-8-*-┐
#── vi: set noet ft=make ts=8 sw=8 fenc=utf-8 :vi ────────────────────┘

ifeq ($(MODE), )

PKGS += THIRD_PARTY_LIBCXXABI_TEST

THIRD_PARTY_LIBCXXABI_TEST_A = o/$(MODE)/third_party/libcxxabi/test/test.a

THIRD_PARTY_LIBCXXABI_TEST_HDRS =					\
	third_party/libcxxabi/libcxx/test/support/make_test_thread.hh	\
	third_party/libcxxabi/libcxx/test/support/test_macros.hh	\
	third_party/libcxxabi/test/support/timer.hh

THIRD_PARTY_LIBCXXABI_TEST_SRCS =					\
	third_party/libcxxabi/test/catch_array_02.pass.cc		\
	third_party/libcxxabi/test/catch_class_01.pass.cc		\
	third_party/libcxxabi/test/catch_class_02.pass.cc		\
	third_party/libcxxabi/test/catch_class_03.pass.cc		\
	third_party/libcxxabi/test/catch_class_04.pass.cc		\
	third_party/libcxxabi/test/catch_const_pointer_nullptr.pass.cc	\
	third_party/libcxxabi/test/catch_function_02.pass.cc		\
	third_party/libcxxabi/test/catch_function_03.pass.cc		\
	third_party/libcxxabi/test/catch_in_noexcept.pass.cc		\
	third_party/libcxxabi/test/catch_member_data_pointer_01.pass.cc	\
	third_party/libcxxabi/test/catch_member_pointer_nullptr.pass.cc	\
	third_party/libcxxabi/test/catch_pointer_nullptr.pass.cc	\
	third_party/libcxxabi/test/catch_pointer_reference.pass.cc	\
	third_party/libcxxabi/test/catch_ptr.pass.cc			\
	third_party/libcxxabi/test/catch_ptr_02.pass.cc			\
	third_party/libcxxabi/test/catch_reference_nullptr.pass.cc	\
	third_party/libcxxabi/test/cxa_bad_cast.pass.cc			\
	third_party/libcxxabi/test/cxa_bad_typeid.pass.cc		\
	third_party/libcxxabi/test/cxa_thread_atexit_test.pass.cc	\
	third_party/libcxxabi/test/cxa_vec_new_overflow_PR41395.pass.cc	\
	third_party/libcxxabi/test/dynamic_cast.pass.cc			\
	third_party/libcxxabi/test/dynamic_cast3.pass.cc		\
	third_party/libcxxabi/test/dynamic_cast5.pass.cc		\
	third_party/libcxxabi/test/dynamic_cast14.pass.cc		\
	third_party/libcxxabi/test/dynamic_cast_stress.pass.cc		\
	third_party/libcxxabi/test/exception_object_alignment.pass.cc	\
	third_party/libcxxabi/test/exception_object_alignment.2.pass.cc	\
	third_party/libcxxabi/test/guard_test_basic.pass.cc		\
	third_party/libcxxabi/test/guard_threaded_test.pass.cc		\
	third_party/libcxxabi/test/incomplete_type.sh.cc		\
	third_party/libcxxabi/test/inherited_exception.pass.cc		\
	third_party/libcxxabi/test/test_aux_runtime.pass.cc		\
	third_party/libcxxabi/test/test_aux_runtime_op_array_new.pass.cc\
	third_party/libcxxabi/test/test_demangle.pass.cc		\
	third_party/libcxxabi/test/test_exception_address_alignment.pass.cc	\
	third_party/libcxxabi/test/test_exception_storage.pass.cc	\
	third_party/libcxxabi/test/test_fallback_malloc.pass.cc		\
	third_party/libcxxabi/test/test_guard.pass.cc			\
	third_party/libcxxabi/test/test_vector1.pass.cc			\
	third_party/libcxxabi/test/test_vector2.pass.cc			\
	third_party/libcxxabi/test/test_vector3.pass.cc			\
	third_party/libcxxabi/test/uncaught_exception.pass.cc		\
	third_party/libcxxabi/test/uncaught_exceptions.pass.cc		\
	third_party/libcxxabi/test/unittest_demangle.pass.cc		\
	third_party/libcxxabi/test/unwind_01.pass.cc			\
	third_party/libcxxabi/test/unwind_02.pass.cc			\
	third_party/libcxxabi/test/unwind_03.pass.cc			\
	third_party/libcxxabi/test/unwind_04.pass.cc			\
	third_party/libcxxabi/test/unwind_05.pass.cc			\
	third_party/libcxxabi/test/unwind_06.pass.cc

# TODO: Add this test when #1073 is fixed
THIRD_PARTY_LIBCXXABI_TEST_SRCS_FAILING_COSMO =				\
	third_party/libcxxabi/test/thread_local_destruction_order.pass.cc

THIRD_PARTY_LIBCXXABI_TEST_SRCS_FAILING_GCC =				\
	third_party/libcxxabi/test/catch_array_01.pass.cc		\
	third_party/libcxxabi/test/catch_function_01.pass.cc		\
	third_party/libcxxabi/test/catch_member_function_pointer_01.pass.cc	\
	third_party/libcxxabi/test/catch_member_function_pointer_02.pass.cc

# Works if run, but fails to compile on GitHub Actions with an OOM
THIRD_PARTYLIBCXXABI_TEST_SRCS_COMPILE_OOM =				\
	third_party/libcxxabi/test/catch_multi_level_pointer.pass.cc

THIRD_PARTY_LIBCXXABI_TEST_COMS =					\
	$(THIRD_PARTY_LIBCXXABI_TEST_SRCS:%.cc=o/$(MODE)/%.com)

THIRD_PARTY_LIBCXXABI_TEST_TESTS =					\
	$(THIRD_PARTY_LIBCXXABI_TEST_COMS:%=%.ok)

THIRD_PARTY_LIBCXXABI_TEST_OBJS =					\
	$(THIRD_PARTY_LIBCXXABI_TEST_SRCS:%.cc=o/$(MODE)/%.o)		\
	o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.one.o	\
	o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.two.o

THIRD_PARTY_LIBCXXABI_TEST_OBJS_WNO_EXCEPTIONS =			\
	o/$(MODE)/third_party/libcxxabi/test/catch_class_03.pass.o	\
	o/$(MODE)/third_party/libcxxabi/test/catch_class_04.pass.o	\
	o/$(MODE)/third_party/libcxxabi/test/catch_ptr.pass.o		\
	o/$(MODE)/third_party/libcxxabi/test/catch_ptr_02.pass.o	\
	o/$(MODE)/third_party/libcxxabi/test/inherited_exception.pass.o

THIRD_PARTY_LIBCXXABI_TEST_OBJS_CPP14 =					\
	o/$(MODE)/third_party/libcxxabi/test/unwind_02.pass.o		\
	o/$(MODE)/third_party/libcxxabi/test/unwind_03.pass.o		\
	o/$(MODE)/third_party/libcxxabi/test/unwind_04.pass.o		\
	o/$(MODE)/third_party/libcxxabi/test/unwind_05.pass.o

THIRD_PARTY_LIBCXXABI_TEST_BINS =					\
	$(THIRD_PARTY_LIBCXXABI_TEST_COMS)				\
	$(THIRD_PARTY_LIBCXXABI_TEST_COMS:%=%.dbg)

THIRD_PARTY_LIBCXXABI_TEST_CHECKS =					\
	$(THIRD_PARTY_LIBCXXABI_TEST_COMS:%=%.runs)			\
	$(THIRD_PARTY_LIBCXXABI_TEST_HDRS:%=o/$(MODE)/%.ok)

THIRD_PARTY_LIBCXXABI_TEST_DIRECTDEPS =					\
	LIBC_NEXGEN32E							\
	THIRD_PARTY_LIBCXX						\
	THIRD_PARTY_LIBCXXABI

THIRD_PARTY_LIBCXXABI_TEST_DEPS :=					\
	$(call uniq,$(foreach x,$(THIRD_PARTY_LIBCXXABI_TEST_DIRECTDEPS),$($(x))))

$(THIRD_PARTY_LIBCXXABI_TEST_A):					\
		$(THIRD_PARTY_LIBCXXABI_TEST_A).pkg

$(THIRD_PARTY_LIBCXXABI_TEST_A).pkg:					\
		$(foreach x,$(THIRD_PARTY_LIBCXXABI_TEST_DIRECTDEPS),$($(x)_A).pkg)

o/$(MODE)/third_party/libcxxabi/test/%.com.dbg:				\
		$(THIRD_PARTY_LIBCXXABI_TEST_DEPS)			\
		$(THIRD_PARTY_LIBCXXABI_TEST_A)				\
		o/$(MODE)/third_party/libcxxabi/test/%.o		\
		$(THIRD_PARTY_LIBCXXABI_TEST_A).pkg			\
		$(CRT)							\
		$(APE_NO_MODIFY_SELF)
	@$(APELINK)

# TODO: Remove constinit hacks when we have C++20
$(THIRD_PARTY_LIBCXXABI_TEST_OBJS): private				\
		CXXFLAGS +=						\
			-fexceptions					\
			-frtti						\
			-D_LIBCXXABI_BUILDING_LIBRARY			\
			-D_LIBCPP_BUILDING_LIBRARY			\
			-D_LIBCPP_CONSTINIT=__constinit

$(THIRD_PARTY_LIBCXXABI_TEST_OBJS_WNO_EXCEPTIONS): private		\
		CXXFLAGS +=						\
			-Wno-exceptions

$(THIRD_PARTY_LIBCXXABI_TEST_OBJS_CPP14): private			\
		CXXFLAGS +=						\
			-std=gnu++14

o/$(MODE)/third_party/libcxxabi/test/guard_test_basic.pass.o: private	\
		CXXFLAGS +=						\
			-Wno-invalid-memory-model

o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.one.o: private	\
		CXXFLAGS +=						\
			-Wno-unreachable-code
o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.two.o: private	\
		CXXFLAGS +=						\
			-Wno-unreachable-code				\
			-DTU_ONE
o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.com.dbg:	\
		$(THIRD_PARTY_LIBCXXABI_TEST_DEPS)			\
		$(THIRD_PARTY_LIBCXXABI_TEST_A)				\
		o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.one.o	\
		o/$(MODE)/third_party/libcxxabi/test/incomplete_type.sh.two.o	\
		$(THIRD_PARTY_LIBCXXABI_TEST_A).pkg			\
		$(CRT)							\
		$(APE_NO_MODIFY_SELF)
	@$(APELINK)

endif

.PHONY: o/$(MODE)/third_party/libcxxabi/test
o/$(MODE)/third_party/libcxxabi/test:					\
		$(THIRD_PARTY_LIBCXXABI_TEST_BINS)			\
		$(THIRD_PARTY_LIBCXXABI_TEST_CHECKS)
