// Copyright (c) 2009-2012 The Bitcoin developers
// Copyright (c) 2011-2012 Litecoin Developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.

#include <boost/assign/list_of.hpp> // for 'map_list_of()'
#include <boost/foreach.hpp>

#include "checkpoints.h"

#include "main.h"
#include "uint256.h"

namespace Checkpoints
{
    typedef std::map<int, uint256> MapCheckpoints;

    //
    // What makes a good checkpoint block?
    // + Is surrounded by blocks with reasonable timestamps
    //   (no blocks before with a timestamp after, none after with
    //    timestamp before)
    // + Contains no strange transactions
    //
    static MapCheckpoints mapCheckpoints =
        boost::assign::map_list_of
        (     1, uint256("0x006e800301bbd850d7ba67ad9295c3a940f5fc8f5581e3484967bd33c4c8b965"))
        (  1500, uint256("0x4bdb2c6c8f7919c4d1234fd2c207975d76c4fbcb9a5d8180f2dff7d99cb76a55"))
        (  3000, uint256("0xcb87d608786c7452b95ff50349171ed7f502e218ca95a6708740ae8ab68b3631"))
        (  8000, uint256("0xa512b03a7006ce3a0f0dc485f1a3b424769e5665169124e2947a51e3842d9dce"))
        ( 20000, uint256("0x2f6c3ff7712dabfe1ed98ed6da35086755f951836da673a0b090c07fdb6c2282"))
        ( 35000, uint256("0xf4e91cee78c2d25b23bbd8468ddba2dffaeb1a911d4cae742a826985571e07dc"))
        ( 45000, uint256("0x01a1a7077a8bd30244e96bdc512ee6674dcf57a21b0986fbedbc29b0a3b37d79"))
        ( 46000, uint256("0x802c4c7acc550c7472f897a24b2a3e4972dec025a14ef99b03df91f240c58456"))
        ( 50000, uint256("0xbed952276c06a11f55db9f4103b4440b8c6b3e4243816b5b090a76a05f45fc55"))
        ( 55000, uint256("0x08f177321e21bf04ec5b9ca1bcb5ffecef78c3cb837104bf3f0d4d3432110835"))
        ( 60000, uint256("0x223df4a828502907b369467905c3df80ab3fc13b3c9fce41438e7501d3049e72"))
        ( 65000, uint256("0x5e09416a9f7f3f7f3c0d70109906f7ff4f957c2a75e637885d8841a026238721"))
        ( 69000, uint256("0x06c33bdf2516f52dd76ee806cbdacd573b87282d300e57efc4df1b77d84fad98"))
        ;

    bool CheckBlock(int nHeight, const uint256& hash)
    {
        if (fTestNet) return true; // Testnet has no checkpoints
        
        MapCheckpoints::const_iterator i = mapCheckpoints.find(nHeight);
        if (i == mapCheckpoints.end()) return true;
        return hash == i->second;
    }

    int GetTotalBlocksEstimate()
    {
        if (fTestNet) return 0;
        return mapCheckpoints.rbegin()->first;
    }

    CBlockIndex* GetLastCheckpoint(const std::map<uint256, CBlockIndex*>& mapBlockIndex)
    {
        if (fTestNet) return NULL;
        BOOST_REVERSE_FOREACH(const MapCheckpoints::value_type& i, mapCheckpoints)
        {
            const uint256& hash = i.second;
            std::map<uint256, CBlockIndex*>::const_iterator t = mapBlockIndex.find(hash);
            if (t != mapBlockIndex.end())
                return t->second;
        }
        return NULL;
    }
}
