// Copyright (c) 2017 The ENIX developers
// Copyright (c) 2009-2012 The Darkcoin developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#ifndef SPORK_H
#define SPORK_H

#include "bignum.h"
#include "sync.h"
#include "net.h"
#include "key.h"

#include "util.h"
#include "script.h"
#include "base58.h"
#include "main.h"

using namespace std;
using namespace boost;

// Don't ever reuse these IDs for other sporks
#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT               10000
#define SPORK_2_INSTANTX                                      10001
#define SPORK_3_INSTANTX_BLOCK_FILTERING                      10002
#define SPORK_4_NOTUSED                                       10003
#define SPORK_5_MAX_VALUE                                     10004
#define SPORK_6_REPLAY_BLOCKS                                 10005
#define SPORK_7_MASTERNODE_SCANNING                           10006
#define SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT                10007
#define SPORK_9_MASTERNODE_BUDGET_ENFORCEMENT                 10008
#define SPORK_10_MASTERNODE_PAY_UPDATED_NODES                 10009
#define SPORK_11_RESET_BUDGET                                 10010
#define SPORK_12_RECONSIDER_BLOCKS                            10011
#define SPORK_13_ENABLE_SUPERBLOCKS                           10012

#define SPORK_1_MASTERNODE_PAYMENTS_ENFORCEMENT_DEFAULT       2428537599  //2017-12-30 23:59:59 GMT // NOT USED
#define SPORK_2_INSTANTX_DEFAULT                              978307200   //2018-1-1 23:59:59 GMT
#define SPORK_3_INSTANTX_BLOCK_FILTERING_DEFAULT              978307200   //2018-1-1 23:59:59 GMT
#define SPORK_4_RECONVERGE_DEFAULT                            1451606400  //2018-01-01 // NOT USED
#define SPORK_5_MAX_VALUE_DEFAULT                             5000         //5000 ENIX
#define SPORK_6_REPLAY_BLOCKS_DEFAULT                         0 		  // NOT USED
#define SPORK_8_MASTERNODE_PAYMENT_ENFORCEMENT_DEFAULT        4070908800   //OFF
#define SPORK_9_MASTERNODE_BUDGET_ENFORCEMENT_DEFAULT         4070908800   //OFF
#define SPORK_10_MASTERNODE_PAY_UPDATED_NODES_DEFAULT         4070908800   //OFF
#define SPORK_11_RESET_BUDGET_DEFAULT                         0
#define SPORK_12_RECONSIDER_BLOCKS_DEFAULT                    0
#define SPORK_13_ENABLE_SUPERBLOCKS_DEFAULT                   4070908800   //OFF

class CSporkMessage;
class CSporkManager;

#include "bignum.h"
#include "net.h"
#include "key.h"
#include "util.h"
#include "protocol.h"
#include "darksend.h"
#include <boost/lexical_cast.hpp>

using namespace std;
using namespace boost;

extern std::map<uint256, CSporkMessage> mapSporks;
extern std::map<int, CSporkMessage> mapSporksActive;
extern CSporkManager sporkManager;

void ProcessSpork(CNode* pfrom, std::string& strCommand, CDataStream& vRecv);
int64_t GetSporkValue(int nSporkID);
bool IsSporkActive(int nSporkID);
void ExecuteSpork(int nSporkID, int nValue);
//void ReprocessBlocks(int nBlocks);

//
// Spork Class
// Keeps track of all of the network spork settings
//

class CSporkMessage
{
public:
    std::vector<unsigned char> vchSig;
    int nSporkID;
    int64_t nValue;
    int64_t nTimeSigned;

    uint256 GetHash(){
        uint256 n = Hash(BEGIN(nSporkID), END(nTimeSigned));
        return n;
    }

    ADD_SERIALIZE_METHODS;

    template <typename Stream, typename Operation>
    inline void SerializationOp(Stream& s, Operation ser_action, int nType, int nVersion) {
	unsigned int nSerSize = 0;
        READWRITE(nSporkID);
        READWRITE(nValue);
        READWRITE(nTimeSigned);
        READWRITE(vchSig);
	}
};


class CSporkManager
{
private:
    std::vector<unsigned char> vchSig;

    std::string strMasterPrivKey;
    std::string strTestPubKey;
    std::string strMainPubKey;

public:

    CSporkManager() {
        strMainPubKey = "0472b0189273f5767fafced1410e56a7611053b9cc24bfcdd7d6669c290aa73bf0dcafe8588b38a3b75c3ecd56201f94f1306ef1353b85ddfa9de07ac951a0c2cb";
        strTestPubKey = "04bef3b18db8e702b507f9f560ae5c2562f694dce0659b9274e533fb8d86fd153a2670256b17380c546735489df35ca3dfa74b6e383424da8db49f8912c3e470c4";
    }

    std::string GetSporkNameByID(int id);
    int GetSporkIDByName(std::string strName);
    bool UpdateSpork(int nSporkID, int64_t nValue);
    bool SetPrivKey(std::string strPrivKey);
    bool CheckSignature(CSporkMessage& spork);
    bool Sign(CSporkMessage& spork);
    void Relay(CSporkMessage& msg);

};

#endif
