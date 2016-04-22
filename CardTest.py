#! /usr/bin/env python

import unittest

import Card

class TestCardMethods(unittest.TestCase):

  def checkSuitAndRanks(self, c, suit, numericRank):
    self.assertEqual(c.suit(), suit)
    self.assertEqual(c.numericRank(), numericRank)
    self.assertEqual(c.symbolicRank(), c.numericRankToStringRank(numericRank))

  def testHeartDeuce(self):
    c = Card.Card(1)
    self.checkSuitAndRanks(c, c.HEARTS, 2)

  def testHearts(self):
    for i in range(0, 13):
        c = Card.Card(i)
        self.checkSuitAndRanks(c, c.HEARTS, i+1)

  def testDiamonds(self):
    for i in range(0, 13):
        c = Card.Card(13+i)
        self.checkSuitAndRanks(c, c.DIAMONDS, i+1)



  def testAllSuits(self):
    for i in range(0, 13):
        c = Card.Card(0*13+i)
        self.checkSuitAndRanks(c, c.HEARTS, i+1)
    for i in range(0, 13):
        c = Card.Card(1*13+i)
        self.checkSuitAndRanks(c, c.DIAMONDS, i+1)
    for i in range(0, 13):
        c = Card.Card(2*13+i)
        self.checkSuitAndRanks(c, c.SPADES, i+1)
    for i in range(0, 13):
        c = Card.Card(3*13+i)
        self.checkSuitAndRanks(c, c.CLUBS, i+1)


if __name__ == '__main__':
  unittest.main()


