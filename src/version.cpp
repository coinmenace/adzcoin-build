// Copyright (c) 2012 The Bitcoin developers
// Copyright (c) 2017 The Swipp developers
// Distributed under the MIT/X11 software license, see the accompanying
// file COPYING or http://www.opensource.org/licenses/mit-license.php.
#include <map>
#include <string>
#include "main.h"
#include "version.h"

// Name of client reported in the 'version' message. Report the same name
// for both bitcoind and bitcoin-qt, to make it harder for attackers to
// target servers or GUI users specifically.
const std::string CLIENT_NAME("adzcoincore");

// Client version number
#define CLIENT_VERSION_SUFFIX   ""


// The following part of the code determines the CLIENT_BUILD variable.
// Several mechanisms are used for this:
// * first, if HAVE_BUILD_INFO is defined, include build.h, a file that is
//   generated by the build environment, possibly containing the output
//   of git-describe in a macro called BUILD_DESC
// * secondly, if this is an exported version of the code, GIT_ARCHIVE will
//   be defined (automatically using the export-subst git attribute), and
//   GIT_COMMIT will contain the commit id.
// * then, three options exist for determining CLIENT_BUILD:
//   * if BUILD_DESC is defined, use that literally (output of git-describe)
//   * if not, but GIT_COMMIT is defined, use v[maj].[min].[rev].[build]-g[commit]
//   * otherwise, use v[maj].[min].[rev].[build]-unk
// finally CLIENT_VERSION_SUFFIX is added

// First, include build.h if requested
#ifdef HAVE_BUILD_INFO
#    include "build.h"
#endif

// git will put "#define GIT_ARCHIVE 1" on the next line inside archives. 
#define GIT_ARCHIVE 1
#ifdef GIT_ARCHIVE
#    define GIT_COMMIT_ID ": Yggdrasil"
//#    define GIT_COMMIT_DATE "$Format:%cD"
#endif

#define BUILD_DESC_FROM_COMMIT(maj,min,rev,build,commit) \
    "v" DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) "" commit

#define BUILD_DESC_FROM_UNKNOWN(maj,min,rev,build) \
    "v" DO_STRINGIZE(maj) "." DO_STRINGIZE(min) "." DO_STRINGIZE(rev) "." DO_STRINGIZE(build) ""

#ifndef BUILD_DESC
#    ifdef GIT_COMMIT_ID
#        define BUILD_DESC BUILD_DESC_FROM_COMMIT(CLIENT_VERSION_MAJOR, CLIENT_VERSION_MINOR, CLIENT_VERSION_REVISION, CLIENT_VERSION_BUILD, GIT_COMMIT_ID)
#    else
#        define BUILD_DESC BUILD_DESC_FROM_UNKNOWN(CLIENT_VERSION_MAJOR, CLIENT_VERSION_MINOR, CLIENT_VERSION_REVISION, CLIENT_VERSION_BUILD)
#    endif
#endif

#ifndef BUILD_DATE
#    ifdef GIT_COMMIT_DATE
#        define BUILD_DATE GIT_COMMIT_DATE
#    else
#        define BUILD_DATE __DATE__ ", " __TIME__
#    endif
#endif

const std::string CLIENT_BUILD(BUILD_DESC CLIENT_VERSION_SUFFIX);
const std::string CLIENT_DATE(BUILD_DATE);

// Check if the specific version is valid for the given block height.
// The idea here is to allow for smooth transitions between new protocol versions.
// NEEDS TO BE MODIFIED IF A NEW BLOCK BREAK OCCURS IN THE FUTURE!
/**
bool isVersionCompatible(BlockBreakVersionType fbVersionType, int version, int nHeight)
{
    int b0To93000[]   = {0, 93000 - 1};
    int b93000ToLbb[] = {93000, LAST_BLOCK_BREAK - 1};
    int lbbToMax[]    = {LAST_BLOCK_BREAK, MAX_BLOCK_SIZE};

    std::map<int, int *> instantXForkBlocks   = {{69110, b0To93000}, {69200, b93000ToLbb}, {MIN_INSTANTX_PROTO_VERSION, lbbToMax}};
    std::map<int, int *> masternodeForkBlocks = {{69110, b0To93000}, {69200, b93000ToLbb}, {MIN_MN_PROTO_VERSION, lbbToMax}};
    std::map<int, int *> peerForkBlocks       = {{69110, b0To93000}, {69200, b93000ToLbb}, {MIN_PEER_PROTO_VERSION, lbbToMax}};

    std::map<BlockBreakVersionType, std::map<int, int *>> fbt = {
        {INSTANTX, instantXForkBlocks},
        {MASTERNODE, masternodeForkBlocks},
        {PEER, peerForkBlocks}
    };

    try
    {
        auto versionMap = fbt.at(fbVersionType);
        auto forkBlock = versionMap.at(version);

        return nHeight >= forkBlock[0] && nHeight <= forkBlock[1];
    }
    catch(const std::out_of_range& oor)
    {
        LogPrintf("non-existing protocol version %d received.\n", version);
    }

    return false;
}

// NEEDS TO BE MODIFIED IF A NEW BLOCK BREAK OCCURS IN THE FUTURE!

int getBlockVersion(BlockBreakVersionType fbVersionType, int nHeight)
{
    if (isVersionCompatible(fbVersionType, 69200, nHeight))
        return 69200;
    else if (isVersionCompatible(fbVersionType, 69210, nHeight))
        return 69210;

    return 69110;
}
*/