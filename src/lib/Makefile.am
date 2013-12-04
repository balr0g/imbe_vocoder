
lib_LTLIBRARIES = libimbe_vocoder.la

library_includedir=$(includedir)
library_include_HEADERS = imbe_vocoder.h

LIBIMBE_LIBRARY_VERSION=0:0:0

libimbe_vocoder_la_LDFLAGS = -version-info $(LIBIMBE_LIBRARY_VERSION)

# These are the source files that go into the shared library
libimbe_vocoder_la_SOURCES = 			\
	aux_sub.cc \
	basicop2.cc \
	ch_decode.cc \
	ch_encode.cc \
	dc_rmv.cc \
	decode.cc \
	dsp_sub.cc \
	encode.cc \
	math_sub.cc \
	imbe_vocoder.cc \
	imbe_vocoder_impl.cc \
	pe_lpf.cc \
	pitch_est.cc \
	pitch_ref.cc \
	qnt_sub.cc \
	rand_gen.cc \
	sa_decode.cc \
	sa_encode.cc \
	sa_enh.cc \
	tbls.cc \
	uv_synt.cc \
	v_synt.cc \
	v_uv_det.cc
