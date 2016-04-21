#! /usr/bin/env python

class Card:
  """ A Poker card"""

  HEARTS   = 0
  DIAMONDS = 1
  SPADES   = 2
  CLUBS    = 3

  nvalToSuit = [HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
                HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, HEARTS, \
                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
                DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, DIAMONDS, \
                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
                SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, SPADES, \
                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, \
                CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS, CLUBS]

  def __init__(self, nvalue):
    self.numericValue = nvalue

  def suit(self):
    return self.nvalToSuit[self.numericValue]

if __name__ == '__main__':
  c = Card(14)
  print c.suit()

