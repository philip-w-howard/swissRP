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
/**
 * @author Aleksandar Dragojevic aleksandar.dragojevic@epfl.ch
 */

#ifndef WLPDSTM_TRANSACTION_H_
#define WLPDSTM_TRANSACTION_H_

#include "memory.h"
#include "common/tls.h"
#include "aborted_exc.h"
#include "common/word.h"

///////////////////////////////////////////
// different transaction implementations //
///////////////////////////////////////////

#include "transaction_mixinv.h"

///////////////////////////////////////
// select transaction implementation //
///////////////////////////////////////

namespace wlpdstm {

	typedef TxMixinv Transaction;
}

/////////////////////////////////////
// thread local transaction object //
/////////////////////////////////////

namespace wlpdstm {

	// A shortcut used for accessing transaction in progress.
	class CurrentTransaction : public Tls<Transaction, true, true> {
		public:
			static void TxStart(int lexical_tx_id = NO_LEXICAL_TX) {
				Tls<Transaction, true, true>::Get()->TxStart(lexical_tx_id);
			}

			static LONG_JMP_BUF *GetLongJmpBuf() {
				return &Tls<Transaction, true, true>::Get()->start_buf;
			}

			static void TxCommit() {
				Tls<Transaction, true, true>::Get()->TxCommit();
			}

			static void TxRestart() {
				Tls<Transaction, true, true>::Get()->TxRestart();
			}

			static void TxAbort() {
				Tls<Transaction, true, true>::Get()->TxAbort();
			}

#ifdef RP_STM
			static void WriteWord_mb(Word *address, Word value) {
				Tls<Transaction, true, true>::Get()->WriteWord_mb(address, value);
			}

            static void GracePeriod(void *rp_context) {
                Tls<Transaction, true, true>::Get()->GracePeriod(rp_context);
            }

            static void RPFree(void *rp_context, void *address) {
                Tls<Transaction, true, true>::Get()->RPFree(rp_context, address);
            }

            static void Free(void *address) {
                Tls<Transaction, true, true>::Get()->Free(address);
            }
#endif
			static void WriteWord(Word *address, Word value) {
				Tls<Transaction, true, true>::Get()->WriteWord(address, value);
			}

#ifdef SUPPORT_LOCAL_WRITES
			static void WriteWordLocal(Word *address, Word value) {
				Tls<Transaction, true, true>::Get()->WriteWordLocal(address, value);
			}
#endif /* SUPPORT_LOCAL_WRITES */

			static Word ReadWord(Word *address) {
				return Tls<Transaction, true, true>::Get()->ReadWord(address);
			}

			static void *TxMalloc(size_t size) {
				return Tls<Transaction, true, true>::Get()->TxMalloc(size);
			}

			static void TxFree(void *address, size_t size) {
				return Tls<Transaction, true, true>::Get()->TxFree(address, size);
			}
	};
}

#endif // WLPDSTM_TRANSACTION_H_
