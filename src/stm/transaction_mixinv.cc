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

#include "transaction_mixinv.h"

wlpdstm::VersionLock wlpdstm::TxMixinv::version_lock_table[FULL_VERSION_LOCK_TABLE_SIZE];

CACHE_LINE_ALIGNED wlpdstm::GlobalTimestamp wlpdstm::TxMixinv::commit_ts;

CACHE_LINE_ALIGNED wlpdstm::GlobalTimestamp wlpdstm::TxMixinv::cm_ts;

CACHE_LINE_ALIGNED wlpdstm::PaddedWord wlpdstm::TxMixinv::minimum_observed_ts;

CACHE_LINE_ALIGNED wlpdstm::PaddedSpinTryLock wlpdstm::TxMixinv::minimum_observed_ts_lock;

wlpdstm::TxMixinv *wlpdstm::TxMixinv::transactions[MAX_THREADS];

Word wlpdstm::TxMixinv::thread_count;

CACHE_LINE_ALIGNED wlpdstm::PaddedBool wlpdstm::TxMixinv::synchronization_in_progress;

#ifdef PRIVATIZATION_QUIESCENCE
CACHE_LINE_ALIGNED volatile Word wlpdstm::TxMixinv::quiescence_timestamp_array[MAX_THREADS];
#endif /* PRIVATIZATION_QUIESCENCE */

#ifdef SIGNALING
CACHE_LINE_ALIGNED volatile wlpdstm::PaddedWord wlpdstm::TxMixinv::signaling_array[MAX_THREADS];
#endif /* SIGNALING */		

#ifdef ADAPTIVE_LOCKING
CACHE_LINE_ALIGNED wlpdstm::PaddedUnsigned wlpdstm::TxMixinv::lock_extent;

unsigned wlpdstm::TxMixinv::false_sharing_history[FALSE_SHARING_HISTORY_SIZE];
#endif /* ADAPTIVE_LOCKING */
