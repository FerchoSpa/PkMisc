#! /usr/bin/env python

import Card

class Hand:
  """ A Hand of Poker cards """

  VAL_NONE = -1
  VAL_ROYAL_FLUSH = 0

  def __init__(self):
    self.hand = []

  def accept(self, card):
    self.hand.append(card)

  def __suitCount(self):
    card = cards[0]
    suitCountDict = {card.HEARTS : 0, card.DIAMONDS : 0, card.SPADES : 0, card.CLUBS : 0}
    for card in cards:

  def evaluate(self):
    if len(self.hand) != 7:
      return None
    return VAL_NONE, self.hand

  def symbolicRank(self):
    n = self.numericRank()
    return self.numericRankToSymbolicRank[n]

  def numericRankToStringRank(self, n):
    return self.numericRankToSymbolicRank[n]

if __name__ == '__main__':
  c = Card(14)
  print c.suit()

