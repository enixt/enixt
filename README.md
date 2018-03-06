ENIXT [ENIX] CORE
================================

Specifications:
--------------

- PoW (proof of work) / PoS (proof of stake)
- Masternode
- Algorithms: Skein
- Blocktime: 60 seconds
- RPC port: 15112
- P2P port: 15111
- Blockreward (PoW):
  - Block 4 to 300 : 1 ENIX
  - 300 to 10,000 : 4 ENIX
  - 10,000 to 80,000: 8 ENIX
  - 80,000 to 120,000: 6 ENIX
  - 120,000 to 160,000: 5 ENIX
  - 160,000 to 240,000: 4 ENIX
  - Total PoW: 240,000 Blocks

  - Blockreward (PoS):
  - Block 100 to 10,000 : 5 ENIX
  - 10,000 to 80,000: 6 ENIX
  - 80,000 to 120,000: 8 ENIX
  - 120,000 to 160,000: 10 ENIX
  - 160,000 to 240,000: 12 ENIX
  - After 240,000: 10 ENIX

- Masternode Collaterial - 5 000 ENIX.
- Masternodes Rewards - 80% of PoS Blocks.
- Diff Retarget: 5 Blocks
- Maturity: 30 Blocks
- Stake Minimum Age: 4 Hours


Enixt includes an Address Index feature, based on the address index API (searchrawtransactions RPC command) implemented in Bitcoin Core but modified implementation to work with the ENIX codebase (PoS coins maintain a txindex by default for instance).

Initialize the Address Index By Running with -reindexaddr Command Line Argument.  It may take 10-15 minutes to build the initial index.


Linux Build Instructions and Notes
==================================

Dependencies
----------------------
1.  Update packages

        sudo apt-get update

2.  Install required packagages

        sudo apt-get install build-essential libtool autotools-dev automake pkg-config libssl-dev libevent-dev bsdmainutils
        sudo apt-get install libboost-all-dev git
        sudo apt-get install libminiupnpc-dev libgmp3-dev

3.  Install Berkeley DB 4.8

        sudo apt-get install software-properties-common
        sudo add-apt-repository ppa:bitcoin/bitcoin
        sudo apt-get update
        sudo apt-get install libdb4.8-dev libdb4.8++-dev


Build
----------------------
1.  Clone the source:

        git clone https://github.com/enixt/enixtcore/

2.  Build enixt:

    Configure and build.

        cd enixt
        cd src/
        make -f makefile.unix   



Masternode configuration is very similiar to other Masternodes coins.
----------------------

edit enixt.conf

      rpcuser=enixtrpc
      rpcpassword=putyourpasswordhere
      rpcallowip=127.0.0.1
      rpcport=15112
      masternode=1
      masternodeaddr=115.168.42.180:15111
      port=15111
      masternodeprivkey=putyourkeyhere
      daemon=1

