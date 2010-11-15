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

#include "privatization_tree.h"

// this is const, but should be aligned and occupy whole cache lines
CACHE_LINE_ALIGNED unsigned wlpdstm::PrivatizationTree::map_count_to_root_idx[MAX_THREADS];

CACHE_LINE_ALIGNED wlpdstm::PaddedWord wlpdstm::PrivatizationTree::tree_nodes[PRIVATIZATION_TREE_NODE_COUNT];

CACHE_LINE_ALIGNED wlpdstm::PaddedWord wlpdstm::PrivatizationTree::proxy_nodes[PRIVATIZATION_TREE_PROXY_COUNT];

// for debug
CACHE_LINE_ALIGNED wlpdstm::PaddedSpinTryLock wlpdstm::PrivatizationTree::tree_node_locks[PRIVATIZATION_TREE_NODE_COUNT];
CACHE_LINE_ALIGNED wlpdstm::PaddedSpinTryLock wlpdstm::PrivatizationTree::proxy_node_locks[PRIVATIZATION_TREE_PROXY_COUNT];

Word wlpdstm::PrivatizationTree::last_sibling_ts[MAX_THREADS];
Word wlpdstm::PrivatizationTree::last_my_ts[MAX_THREADS];
Word wlpdstm::PrivatizationTree::last_parent_ts[MAX_THREADS];
