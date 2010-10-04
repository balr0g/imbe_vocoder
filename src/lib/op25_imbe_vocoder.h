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

#include <imbe_vocoder.h>

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

  int general_work_decode (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
  int general_work_encode (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);
  int general_work (int noutput_items,
		    gr_vector_int &ninput_items,
		    gr_vector_const_void_star &input_items,
		    gr_vector_void_star &output_items);

  private:
	static const int RXBUF_MAX = 80;

	/* data items */
	int frame_cnt ;
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
	int16_t sampbuf[FRAME];
	size_t sampbuf_ct ;
	int stretch_count ;
	uint8_t save_l;
	bit_vector f_body;
	imbe_vocoder vocoder;

	std::deque<uint8_t> output_queue;
	std::deque<uint16_t> output_queue_decode;

	bool opt_encode_flag;
	bool opt_dump_raw_vectors;
	bool opt_verbose;
	int opt_stretch_amt;
	int opt_stretch_sign;
	int opt_udp_port;
	/* local methods */
	void append_imbe_codeword(bit_vector& frame_body, int16_t frame_vector[], unsigned int& codeword_ct);
	void rxchar(char c);
	void compress_frame(int16_t snd[]);
	void add_sample(int16_t samp);
	void compress_samp(int16_t samp);
	void init_sock(char* udp_host, int udp_port);
};

#endif /* INCLUDED_OP25_IMBE_VOCODER_H */
