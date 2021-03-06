/**
 * @author Aleksandar Dragojevic aleksandar.dragojevic@epfl.ch
 */

//Copyright (c) 2010, Aleksandar Dragojevic aleksandar.dragojevic@epfl.ch
//All rights reserved.
//
//Changes to support Relativistic Programming Copyright (c) Philip W. Howard
//phil.w.howard@gmail.com
//All rights reserved.
//
//This software is release under the terms of the BSD License as follows:
//
//Redistribution and use in source and binary forms, with or without 
//modification, are permitted provided that the following conditions are 
//met:
//
//Redistributions of source code must retain the above copyright notice, 
//this list of conditions and the following disclaimer.
//
//Redistributions in binary form must reproduce the above copyright notice, 
//this list of conditions and the following disclaimer in the documentation 
//and/or other materials provided with the distribution.
//
//Neither the name of the <ORGANIZATION> nor the names of its contributors 
//may be used to endorse or promote products derived from this software 
//without specific prior written permission.
//
//THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" 
//AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE 
//IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE 
//ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE 
//LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR 
//CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF 
//SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS 
//INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN 
//CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) 
//ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE 
//POSSIBILITY OF SUCH DAMAGE.
//
#ifndef WLPDSTM_WLPDSTM_H_
#define WLPDSTM_WLPDSTM_H_

#include <stdlib.h>
#include <stdint.h>

#include "common/word.h"
#include "common/jmp.h"

//namespace wlpdstm {

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

	///////////////////////////
	// basic interface start //
	///////////////////////////	
	
	typedef void *tx_desc;

	// initialization
	void wlpdstm_global_init();

	void wlpdstm_thread_init();

	// start/end tx
	void wlpdstm_start_tx() __attribute__ ((noinline));
	void wlpdstm_start_tx_id(int lexical_tx_id) __attribute__ ((noinline));

	LONG_JMP_BUF *wlpdstm_get_long_jmp_buf();

	void wlpdstm_commit_tx();

	void wlpdstm_abort_tx();

	void wlpdstm_restart_tx();

	// read/write word
	Word wlpdstm_read_word(Word *address);

	void wlpdstm_write_word(Word *address, Word value);

    char *wlpdstm_version();

#ifdef RP_STM
	void wlpdstm_write_word_mb(Word *address, Word value);
    void wlpdstm_free(void *address);
    void wlpdstm_rp_free(void *rp_context, void *address);
    void wlpdstm_grace_period(void *rp_contect);
#endif

#ifdef SUPPORT_LOCAL_WRITES
	void wlpdstm_write_word_local(Word *address, Word value);
#endif /* SUPPORT_LOCAL_WRITES */

	// memory management
	void *wlpdstm_tx_malloc(size_t size);

	void wlpdstm_tx_free(void *ptr, size_t size);

	///////////////////////////////////////////////////////
	// a separate set of methods if current tx is cached //
	///////////////////////////////////////////////////////

	tx_desc *wlpdstm_get_tx_desc();

	// start/end tx
	void wlpdstm_start_tx_desc(tx_desc *tx);
	void wlpdstm_start_tx_id_desc(tx_desc *tx, int lexical_tx_id);

	LONG_JMP_BUF *wlpdstm_get_long_jmp_buf_desc(tx_desc *tx);

	void wlpdstm_commit_tx_desc(tx_desc *tx);

	void wlpdstm_abort_tx_desc(tx_desc *tx);

	void wlpdstm_restart_tx_desc(tx_desc *tx);

	// read/write word
	Word wlpdstm_read_word_desc(tx_desc *tx, Word *address);

	void wlpdstm_write_word_desc(tx_desc *tx, Word *address, Word value);

#ifdef SUPPORT_LOCAL_WRITES
	void wlpdstm_write_word_local_desc(tx_desc *tx, Word *address, Word value);
#endif /* SUPPORT_LOCAL_WRITES */

	// memory management
	void *wlpdstm_tx_malloc_desc(tx_desc *tx, size_t size);

	void wlpdstm_tx_free_desc(tx_desc *tx, void *ptr, size_t size);

	void wlpdstm_print_stats();

	// use for non-tx code to be able to simply switch
	// the whole memory management scheme
	void *wlpdstm_s_malloc(size_t size);
	void wlpdstm_s_free(void *ptr);

	/////////////////////////
	// basic interface end //
	/////////////////////////	

	//////////////////////////////
	// extended interface start //
	//////////////////////////////

	uint32_t wlpdstm_read_32(uint32_t *address);
	uint32_t wlpdstm_read_32_desc(tx_desc *tx, uint32_t *address);
	float wlpdstm_read_float(float *address);
	float wlpdstm_read_float_desc(tx_desc *tx, float *address);
	uint64_t wlpdstm_read_64(uint64_t *address);
	uint64_t wlpdstm_read_64_desc(tx_desc *tx, uint64_t *address);
	double wlpdstm_read_double(double *address);
	double wlpdstm_read_double_desc(tx_desc *tx, double *address);
	
	void wlpdstm_write_32(uint32_t *address, uint32_t value);
	void wlpdstm_write_32_desc(tx_desc *tx, uint32_t *address, uint32_t value);
	void wlpdstm_write_float(float *address, float value);
	void wlpdstm_write_float_desc(tx_desc *tx, float *address, float value);
	void wlpdstm_write_64(uint64_t *address, uint64_t value);
	void wlpdstm_write_64_desc(tx_desc *tx, uint64_t *address, uint64_t value);
	void wlpdstm_write_double(double *address, double value);
	void wlpdstm_write_double_desc(tx_desc *tx, double *address, double value);
	
	////////////////////////////
	// extended interface end //
	////////////////////////////	
#ifdef __cplusplus
}
#endif /* __cplusplus */
		

#endif // WLPDSTM_WLPDSTM_H_

