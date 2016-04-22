#! /usr/bin/env python

import random

import Card

class Deck:
  """ A Deck of Poker cards"""

  _DECK = range(0, 52)

  def __init__(self, size):
    #self.numericCardValues = range(0, 52)
    #random.shuffle(self.numericCardValues)
    self.numericCardValues = random.sample(self._DECK, size)
    self.nCardsDealt = 0

  def dealCard(self):
    numericCardValue = self.numericCardValues[self.nCardsDealt]
    c = Card.Card(numericCardValue)
    self.nCardsDealt += 1;
    return c
    

if __name__ == '__main__':
  d  = Deck()
  c = d.dealCard()
  print c.symbolicRank(), c.suit()


