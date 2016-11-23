#! /usr/bin/env python

class HandEvaluation:
  """ A Poker hand evaluation, one of RoyalFlush, 4 of kind, ..., high card """

  NONE            = -1
  ROYAL_FLUSH     = 0
  STRAIGHT_FLUSH  = 1
  FOUR_OF_A_KIND  = 2
  FULL_HOUSE      = 3
  FLUSH           = 4
  STRAIGHT        = 5
  THREE_OF_A_KIND = 6
  TWO_PAIR        = 7
  PAIR            = 8
  HIGH_CARD       = 9

if __name__ == '__main__':
  print "NONE:"+str(HandEvaluation.NONE)
  print "ROYAL_FLUSH:"+str(HandEvaluation.ROYAL_FLUSH)

