#
# Copyright 2004,2005,2006 Free Software Foundation, Inc.
# 
# This file is part of GNU Radio
# 
# GNU Radio is free software; you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 2, or (at your option)
# any later version.
# 
# GNU Radio is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
# 
# You should have received a copy of the GNU General Public License
# along with GNU Radio; see the file COPYING.  If not, write to
# the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
# Boston, MA 02111-1307, USA.
# 

include $(top_srcdir)/Makefile.common

# Install this stuff so that it ends up as the gnuradio.op25_imbe module
# This usually ends up at:
#   ${prefix}/lib/python${python_version}/site-packages/gnuradio

ourpythondir = $(grpythondir)
ourlibdir    = $(grpyexecdir)

INCLUDES = $(STD_DEFINES_AND_INCLUDES) $(PYTHON_CPPFLAGS)

SWIGPYTHONARGS = $(SWIGPYTHONFLAGS) $(SWIGGRFLAGS)

ALL_IFILES = 				\
	$(LOCAL_IFILES)			\
	$(NON_LOCAL_IFILES)		

NON_LOCAL_IFILES =			\
	$(GNURADIO_CORE_INCLUDEDIR)/swig/gnuradio.i


LOCAL_IFILES = 				\
	op25_imbe.i				

# These files are built by SWIG.  The first is the C++ glue.
# The second is the python wrapper that loads the _op25_imbe shared library
# and knows how to call our extensions.

BUILT_SOURCES = 			\
	op25_imbe.cc			\
	op25_imbe.py				

# This gets op25_imbe.py installed in the right place
ourpython_PYTHON =			\
	op25_imbe.py

ourlib_LTLIBRARIES = _op25_imbe.la

# These are the source files that go into the shared library
_op25_imbe_la_SOURCES = 			\
	op25_imbe.cc \
	aux_sub.cc \
	basicop2.cc \
	ch_decode.cc \
	ch_encode.cc \
	dc_rmv.cc \
	decode.cc \
	dsp_sub.cc \
	encode.cc \
	math_sub.cc \
	op25_imbe_vocoder.cc \
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

# magic flags
_op25_imbe_la_LDFLAGS = $(NO_UNDEFINED) -module -avoid-version

# link the library against some comon swig runtime code and the 
# c++ standard library
_op25_imbe_la_LIBADD = 			\
	$(PYTHON_LDFLAGS)		\
	-lstdc++			

op25_imbe.cc op25_imbe.py: op25_imbe.i $(ALL_IFILES)
	$(SWIG) $(SWIGPYTHONARGS) -module op25_imbe -o op25_imbe.cc $<

# These headers get installed in ${prefix}/include/gnuradio
grinclude_HEADERS =			\
	op25_imbe_vocoder.h


# These swig headers get installed in ${prefix}/include/gnuradio/swig
swiginclude_HEADERS = 			\
	$(LOCAL_IFILES)


MOSTLYCLEANFILES = $(BUILT_SOURCES) *.pyc

# Don't distribute output of swig
dist-hook:
	@for file in $(BUILT_SOURCES); do echo $(RM) $(distdir)/$$file; done
	@for file in $(BUILT_SOURCES); do $(RM) $(distdir)/$$file; done
