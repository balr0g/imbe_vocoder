/* -*- c++ -*- */
/*
 * Copyright 2004 Free Software Foundation, Inc.
 * 
 * This file is part of GNU Radio
 * 
 * GNU Radio is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2, or (at your option)
 * any later version.
 * 
 * GNU Radio is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License
 * along with GNU Radio; see the file COPYING.  If not, write to
 * the Free Software Foundation, Inc., 59 Temple Place - Suite 330,
 * Boston, MA 02111-1307, USA.
 */
#ifndef INCLUDED_OP25_IMBE_VOCODER_H
#define INCLUDED_OP25_IMBE_VOCODER_H

#include <gr_block.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <stdint.h>
#include <vector>
#include <deque>
typedef std::vector<bool> bit_vector;

class op25_imbe_vocoder;

/*
 * We use boost::shared_ptr's instead of raw pointers for all access
 * to gr_blocks (and many other data structures).  The shared_ptr gets
 * us transparent reference counting, which greatly simplifies storage
 * management issues.  This is especially helpful in our hybrid
 * C++ / Python system.
 *
 * See http://www.boost.org/libs/smart_ptr/smart_ptr.htm
 *
 * As a convention, the _sptr suffix indicates a boost::shared_ptr
 */
typedef boost::shared_ptr<op25_imbe_vocoder> op25_imbe_vocoder_sptr;

/*!
 * \brief Return a shared_ptr to a new instance of op25_imbe_vocoder.
 *
 * To avoid accidental use of raw pointers, op25_imbe_vocoder's
 * constructor is private.  op25_imbe_make_vocoder is the public
 * interface for creating new instances.
 */
op25_imbe_vocoder_sptr op25_imbe_make_vocoder (bool encode_flag, bool verbose_flag, int stretch_amt, char* udp_host, int udp_port, bool raw_vectors_flag);

/*!
 * \brief 
 * \ingroup block
 *
 */
class op25_imbe_vocoder : public gr_block
{
private:
  // The friend declaration allows op25_imbe_make_vocoder to
  // access the private constructor.

  friend op25_imbe_vocoder_sptr op25_imbe_make_vocoder (bool encode_flag, bool verbose_flag, int stretch_amt, char* udp_host, int udp_port, bool raw_vectors_flag);

  op25_imbe_vocoder (bool encode_flag, bool verbose_flag, int stretch_amt, char* udp_host, int udp_port, bool raw_vectors_flag);  	// private constructor

 public:
  ~op25_imbe_vocoder ();	// public destructor

  void forecast(int nof_output_items, gr_vector_int &nof_input_items_reqd);

  // Where all the action really happens

  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

  private:
	static const int RXBUF_MAX = 80;

	/* data items */
	int frame_cnt ;
	IMBE_PARAM my_imbe_param;
	int write_sock;
	struct sockaddr_in write_sock_addr;
	int write_bufp;
	char write_buf[512];
	struct timeval tv;
	struct timezone tz;
	struct timeval oldtv;
	int peak_amplitude;
	int peak;
	int samp_ct;
	char rxbuf[RXBUF_MAX];
	int rxbufp ;
	unsigned int codeword_ct ;
	Word16 sampbuf[FRAME];
	size_t sampbuf_ct ;
	int stretch_count ;
	uint8_t save_l;
	bit_vector f_body;

	std::deque<UWord8> output_queue;

	bool opt_encode_flag;
	bool opt_dump_raw_vectors;
	bool opt_verbose;
	int opt_stretch_amt;
	int opt_stretch_sign;
	int opt_udp_port;

	/* data items originally static (moved from individual c++ sources) */
	Word16 prev_pitch, prev_prev_pitch, prev_e_p, prev_prev_e_p;
	UWord32 seed ;
	Word16 num_harms_prev1;
	Word32 sa_prev1[NUM_HARMS_MAX + 2];
	Word16 num_harms_prev2;
	Word32 sa_prev2[NUM_HARMS_MAX + 2];
	Word16 uv_mem[105];
	UWord32 ph_mem[NUM_HARMS_MAX];
	Word16 num_harms_prev3;
	Word32 fund_freq_prev;
	Word16 vu_dsn_prev[NUM_HARMS_MAX];
	Word16 sa_prev3[NUM_HARMS_MAX];
	Word32 th_max;
	Word16 v_uv_dsn[NUM_BANDS_MAX];
	Word16 wr_array[FFTLENGTH / 2 + 1];
	Word16 wi_array[FFTLENGTH / 2 + 1];
	Word16 pitch_est_buf[PITCH_EST_BUF_SIZE];
	Word16 pitch_ref_buf[PITCH_EST_BUF_SIZE];
	Word32 dc_rmv_mem;
	Cmplx16 fft_buf[FFTLENGTH];
	Word16 pe_lpf_mem[PE_LPF_ORD];

	/* member functions */
	void idct(Word16 *in, Word16 m_lim, Word16 i_lim, Word16 *out);
	void dct(Word16 *in, Word16 m_lim, Word16 i_lim, Word16 *out);
	void fft_init(void);
	void fft(Word16 *datam1, Word16 nn, Word16 isign);
	void encode(IMBE_PARAM *imbe_param, Word16 *frame_vector, Word16 *snd);
	void parse(int argc, char **argv);
	void pitch_est_init(void);
	Word32 autocorr(Word16 *sigin, Word16 shift, Word16 scale_shift);
	void e_p(Word16 *sigin, Word16 *res_buf);
	void pitch_est(IMBE_PARAM *imbe_param, Word16 *frames_buf);
	void sa_decode_init(void);
	void sa_decode(IMBE_PARAM *imbe_param);
	void sa_encode_init(void);
	void sa_encode(IMBE_PARAM *imbe_param);
	void uv_synt_init(void);
	void uv_synt(IMBE_PARAM *imbe_param, Word16 *snd);
	void v_synt_init(void);
	void v_synt(IMBE_PARAM *imbe_param, Word16 *snd);
	void pitch_ref_init(void);
	Word16 voiced_sa_calc(Word32 num, Word16 den);
	Word16 unvoiced_sa_calc(Word32 num, Word16 den);
	void v_uv_det(IMBE_PARAM *imbe_param, Cmplx16 *fft_buf);
	void append_imbe_codeword(bit_vector& frame_body, Word16 frame_vector[], unsigned int& codeword_ct);
	void rxchar(char c);
	void compress_frame(Word16 snd[]);
	void add_sample(Word16 samp);
	void compress_samp(Word16 samp);
	void init_sock(char* udp_host, int udp_port);
	void decode_init(void);
	void decode(IMBE_PARAM *imbe_param, Word16 *frame_vector, Word16 *snd);
	void encode_init(void);
};

#endif /* INCLUDED_OP25_IMBE_VOCODER_H */
