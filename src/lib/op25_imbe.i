/* -*- c++ -*- */

%feature("autodoc", "1");		// generate python docstrings

%include "exception.i"
%import "gnuradio.i"			// the common stuff

%{
#include "gnuradio_swig_bug_workaround.h"	// mandatory bug fix

#include "typedef.h"
#include "globals.h"
#include "imbe.h"
#include "dsp_sub.h"
#include "basic_op.h"
#include "math_sub.h"
#include "encode.h"
#include "decode.h"
#include "op25_imbe_vocoder.h"

#include <stdexcept>
%}

// ----------------------------------------------------------------

/*
 * First arg is the package prefix.
 * Second arg is the name of the class minus the prefix.
 *
 * This does some behind-the-scenes magic so we can
 * access op25_imbe_vocoder from python as op25_imbe.vocoder
 */
GR_SWIG_BLOCK_MAGIC(op25_imbe,vocoder);

op25_imbe_vocoder_sptr op25_imbe_make_vocoder (bool encode_flag, bool verbose_flag, int stretch_amt, char* udp_host, int udp_port, bool raw_vectors_flag);

class op25_imbe_vocoder : public gr_block
{
private:
  op25_imbe_vocoder (bool encode_flag, bool verbose_flag, int stretch_amt, char* udp_host, int udp_port, bool raw_vectors_flag);
};
