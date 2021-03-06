// Copyright (c) 2009-2016 Satoshi Nakamoto
// Copyright (c) 2009-2016 The Bitcoin Developers
// Copyright (c) 2015-2016 Silk Network
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef DRKSLK_MINER_H
#define DRKSLK_MINER_H

#include "wallet/wallet.h"

//! Generate new block using proof-of-work or proof-of-stake
CBlock* CreateNewBlock(CReserveKey& reservekey, bool fProofOfStake=false, CAmount* pFees = 0);

/** Modify the extranonce in a block */
void IncrementExtraNonce(CBlock* pblock, CBlockIndex* pindexPrev, unsigned int& nExtraNonce);

/** Do mining precalculation */
void FormatHashBuffers(CBlock* pblock, char* pmidstate, char* pdata, char* phash1);

/** Check mined proof-of-work block */
bool CheckWork(CBlock* pblock, CWallet& wallet, CReserveKey& reservekey);

/** Check mined proof-of-stake block */
bool CheckStake(CBlock* pblock, CWallet& wallet);

/** Base sha256 mining transform */
void SHA256Transform(void* pstate, void* pinput, const void* pinit);

//! Run the wallet PoW miner threads
void GeneratePoWCoins(bool fGenerate, CWallet* pwallet, int nThreads);

#endif // DRKSLK_MINER_H
