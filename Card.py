#! /usr/bin/env python

class Card:
  """ A Poker card"""

  HEARTS   = 0
  DIAMONDS = 1
  SPADES   = 2
  CLUBS    = 3

  suits = [HEARTS, DIAMONDS, SPADES, CLUBS]

  ACE   = 'A'
  ONE   = '1'
  DEUCE = '2'
  THREE = '3'
  FOUR  = '4'
  FIVE  = '5'
  SIX   = '6'
  SEVEN = '7'
  EIGHT = '8'
  NINE  = '9'
  TEN   = 'T'
  JACK  = 'J'
  QUEEN = 'Q'
  KING  = 'K'

  nvalToSuit = [HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
                HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, \
                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS]

  nvalToNumericRank = [1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
                       1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
                       1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
                       1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, \
                       ]

  numericRankToSymbolicRank = [None, ACE, DEUCE, THREE, FOUR, FIVE, SIX, SEVEN, \
                              EIGHT, NINE, TEN, JACK, QUEEN, KING]                       

  def __init__(self, nvalue):
    self.numericValue = nvalue

  def suit(self):
    return self.nvalToSuit[self.numericValue]

  def numericRank(self):
    return self.nvalToNumericRank[self.numericValue]

  def symbolicRank(self):
    n = self.numericRank()
    return self.numericRankToSymbolicRank[n]

  def numericRankToStringRank(self, n):
    return self.numericRankToSymbolicRank[n]

if __name__ == '__main__':
  c = Card(14)
  print c.suit()

