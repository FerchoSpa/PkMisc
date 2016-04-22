#! /usr/bin/env python

import random

import Deck
    

def pairsSim(nIter):
  nPairs = 0
  nAcePairs = 0
  for i in range (nIter):
    d = Deck.Deck(2)
    c1 = d.dealCard()
    c2 = d.dealCard()
    if c1.symbolicRank() == c2.symbolicRank():
      nPairs += 1
      if c1.symbolicRank() == c1.ACE:
        nAcePairs += 1
  return nPairs, nAcePairs


if __name__ == '__main__':
  nPairs = 0
  nAcePairs = 0
  nIter = 1000
  nInnerIter = 1000
  for i in range (nIter):
    np, na = pairsSim(nInnerIter)
    nPairs += np
    nAcePairs += na
  avgNumberOfPairs = nPairs/float(nInnerIter)
  avgNumberOfPocketAces = nAcePairs/float(nInnerIter)
  print (avgNumberOfPairs*100.0)/float(nIter), ', 1 in', int(float(nIter)/avgNumberOfPairs)
  print (avgNumberOfPocketAces*100.0)/float(nIter), ', 1 in', int(float(nIter)/avgNumberOfPocketAces)



