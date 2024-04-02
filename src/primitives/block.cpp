// Copyright (c) 2009-2010 Satoshi Nakamoto
// Copyright (c) 2009-2015 The Bitcoin Core developers
// Distributed under the MIT software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <primitives/block.h>
#include <logging.h>
#include <crypto/common.h>
#include <hash.h>
#include <streams.h>
#include <tinyformat.h>
#include <utilstrencodings.h>

static const uint32_t MAINNET_X11 = 1710107402;
static const uint32_t MAINNET_ALGOCHANGEX10 = 1710107302;

//TODO figure out whats best for activating X10
uint256 CBlockHeader::GetHash() const
{
    if (nTime < MAINNET_X11) {
        std::vector<unsigned char> vch(80);
        CVectorWriter ss(SER_GETHASH, PROTOCOL_VERSION, vch, 0);
        ss << *this;
        LogPrintf("Using x11 algo \n");
        return HashX11((const char*)vch.data(), (const char*)vch.data() + vch.size());
    } else if (nTime >= MAINNET_ALGOCHANGEX10) {
        std::vector<unsigned char> vch(80);
        CVectorWriter ss(SER_GETHASH, PROTOCOL_VERSION, vch, 0);
        ss << *this;
        LogPrintf("Using x10 algo \n");
        return HashX10((const char*)vch.data(), (const char*)vch.data() + vch.size());
    } else {
        std::vector<unsigned char> vch(80);
        CVectorWriter ss(SER_GETHASH, PROTOCOL_VERSION, vch, 0);
        ss << *this;
        LogPrintf("Using x11 algo \n");
        return HashX11((const char*)vch.data(), (const char*)vch.data() + vch.size());
    }
}



// uint256 CBlockHeader::GetHash() const
// {
//     if (nTime < MAINNET_ALGOCHANGEX10) {
//         uint32_t nTimeToUse = MAINNET_X11;
//         if (nTime >= nTimeToUse) {
//             std::vector<unsigned char> vch(80);
//             CVectorWriter ss(SER_GETHASH, PROTOCOL_VERSION, vch, 0);
//             ss << *this;
//             LogPrintf("Starting x10 \n");
//             return HashX10((const char*)vch.data(), (const char*)vch.data() + vch.size());
//         }

//         std::vector<unsigned char> vch(80);
//         CVectorWriter ss(SER_GETHASH, PROTOCOL_VERSION, vch, 0);
//         ss << *this;
//         LogPrintf("Starting x11 \n");
//         return HashX11((const char*)vch.data(), (const char*)vch.data() + vch.size());
//     }

// }



std::string CBlock::ToString() const
{
    std::stringstream s;
    s << strprintf("CBlock(hash=%s, ver=0x%08x, hashPrevBlock=%s, hashMerkleRoot=%s, nTime=%u, nBits=%08x, nNonce=%u, vtx=%u)\n",
        GetHash().ToString(),
        nVersion,
        hashPrevBlock.ToString(),
        hashMerkleRoot.ToString(),
        nTime, nBits, nNonce,
        vtx.size());
    for (const auto& tx : vtx) {
        s << "  " << tx->ToString() << "\n";
    }
    return s.str();
}
