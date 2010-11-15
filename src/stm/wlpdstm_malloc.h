/**
 * Definitions for various memory management functions are here. They can be simply
 * used by different compiler wrappers.
 *
 * @author Aleksandar Dragojevic aleksandar.dragojevic@epfl.ch
 *
 */

// TODO: This is a very ugly file name. Think of something better later.

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
#ifndef WLPDSTM_MALLOC_H_
#define WLPDSTM_MALLOC_H_

#include "transaction.h"

void *wlpdstm_malloc_tx_malloc(size_t size) {
	return wlpdstm::CurrentTransaction::TxMalloc(size);
}

void wlpdstm_malloc_tx_free(void *ptr, size_t size) {
	wlpdstm::CurrentTransaction::TxFree(ptr, size);
}

#endif /* WLPDSTM_MALLOC_H_ */
