// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2014 The Bitcoin developers
// Copyright (c) 2015-2016 Silk Network
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#ifndef DARKSILK_SCRIPT_STANDARD_H
#define DARKSILK_SCRIPT_STANDARD_H

#include "script/interpreter.h"
#include "uint256.h"

#include <boost/variant.hpp>

#include <stdint.h>

//static const bool DEFAULT_ACCEPT_DATACARRIER = true;

class CKeyID;
class CScript;
class CStealthAddress;


/** A reference to a CScript: the Hash160 of its serialization */
/**class CScriptID : public uint160
{
public:
    CScriptID() : uint160(0) { }
    CScriptID(const CScript& in);
    CScriptID(const uint160 &in) : uint160(in) { }
};

static const unsigned int MAX_OP_RETURN_RELAY = 83;      // bytes (+1 for OP_RETURN, +2 for the pushdata opcodes)
extern bool fAcceptDatacarrier;
extern unsigned nMaxDatacarrierBytes;*/

// Mandatory script verification flags that all new blocks must comply with for
// t
// Mandatory script verification flags that all new blocks must comply with for
// them to be valid. (but old blocks may not comply with)
//
// Failing one of these tests may trigger a DoS ban - see ConnectInputs() for
// details.
static const unsigned int MANDATORY_SCRIPT_VERIFY_FLAGS = SCRIPT_VERIFY_NULLDUMMY |
                                                          SCRIPT_VERIFY_STRICTENC |
                                                          SCRIPT_VERIFY_CHECKLOCKTIMEVERIFY;

// Standard script verification flags that standard transactions will comply
// with. However scripts violating these flags may still be present in valid
// blocks and we must accept those blocks.
static const unsigned int STANDARD_SCRIPT_VERIFY_FLAGS = MANDATORY_SCRIPT_VERIFY_FLAGS |
                                                         SCRIPT_VERIFY_DISCOURAGE_UPGRADABLE_NOPS;

// For convenience, standard but not mandatory verify flags.
static const unsigned int STANDARD_NOT_MANDATORY_VERIFY_FLAGS = STANDARD_SCRIPT_VERIFY_FLAGS & ~MANDATORY_SCRIPT_VERIFY_FLAGS;

enum txnouttype
{
    TX_NONSTANDARD,
    // 'standard' transaction types:
    TX_PUBKEY,
    TX_PUBKEYHASH,
    TX_SCRIPTHASH,
    TX_MULTISIG,
    TX_NULL_DATA,
};

class CNoDestination {
public:
    friend bool operator==(const CNoDestination &a, const CNoDestination &b) { return true; }
    friend bool operator<(const CNoDestination &a, const CNoDestination &b) { return true; }
};

/** A txout script template with a specific destination. It is either:
 *  * CNoDestination: no destination set
 *  * CKeyID: TX_PUBKEYHASH destination
 *  * CScriptID: TX_SCRIPTHASH destination
 *  A CTxDestination is the internal data type encoded in a CDarkSilkAddress
 */
typedef boost::variant<CNoDestination, CKeyID, CScriptID, CStealthAddress> CTxDestination;

const char* GetTxnOutputType(txnouttype t);

bool Solver(const CScript& scriptPubKey, txnouttype& typeRet, std::vector<std::vector<unsigned char> >& vSolutionsRet);
int ScriptSigArgsExpected(txnouttype t, const std::vector<std::vector<unsigned char> >& vSolutions);
bool IsStandard(const CScript& scriptPubKey, txnouttype& whichType);
bool ExtractDestination(const CScript& scriptPubKey, CTxDestination& addressRet);
bool ExtractDestinations(const CScript& scriptPubKey, txnouttype& typeRet, std::vector<CTxDestination>& addressRet, int& nRequiredRet);

CScript GetScriptForDestination(const CTxDestination& dest);
CScript GetScriptForMultisig(int nRequired, const std::vector<CPubKey>& keys);

#endif // DARKSILK_SCRIPT_STANDARD_H