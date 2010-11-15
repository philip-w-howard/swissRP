#ifndef WLPDSTM_CONSTANTS_H_
#define WLPDSTM_CONSTANTS_H_
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

#ifdef WLPDSTM_X86
#define CACHE_LINE_SIZE_BYTES 64
#elif defined WLPDSTM_SPARC
#define CACHE_LINE_SIZE_BYTES 64
#endif /* arch */

#define CACHE_LINE_ALIGNED __attribute__((aligned(CACHE_LINE_SIZE_BYTES)))

#include "common/word.h"

namespace wlpdstm {

#ifdef WLPDSTM_32
	const unsigned ADDRESS_SPACE_SIZE = 32;
	const unsigned LOG_BYTES_IN_WORD = 2;
#elif defined WLPDSTM_64
	const unsigned ADDRESS_SPACE_SIZE = 64;
	const unsigned LOG_BYTES_IN_WORD = 3;
#endif /* X86_64 */
	
	// this constant is useful for defining various data structures, but it should be possible
	// to replace it with a higher number with no problems
	const unsigned MAX_THREADS = 64;

	// the smallest timestamp used
	const unsigned MINIMUM_TS = 0;

	const unsigned WORD_LOG_SIZE = 22;

	const unsigned LOCK_RESERVED_BITS = 2;

	// -1 to get the maximum number
	const Word MAXIMUM_TS = (1l << (ADDRESS_SPACE_SIZE - LOCK_RESERVED_BITS)) - 1 - MAX_THREADS;

	// top level transaction
	const int TX_TOP_LEVEL = 0;
	const int TX_NO_LEVEL = (TX_TOP_LEVEL - 1);

	enum OperationType {
		NO_OP = 0,
		READ_OP = 1,
		WRITE_OP = 2,
		DELETE_OP = 3
	};

	inline const char *getOperationName(OperationType optype) {
		const char *names[] = {
			"noop",
			"read",
			"write",
			"delete"
		};

		return names[optype];
	}
}

#define LSB 1u

#define MINIMUM_VERSION ((Word *)0)

#define WRITE_LOCK_CLEAR ((Word)0)

#define READ_LOCK_SET ((Word)LSB)

#define NO_LEXICAL_TX -1

#endif
