#! /usr/bin/env python

import unittest

import Hand
import Card
import HandEvaluation as he

class TestHandMethods(unittest.TestCase):


  def testRoyalFlushFlop(self):
    h = Hand.Hand(0)

    h.accept(13)
    h.accept(22)
    h.accept(23)
    h.accept(24)
    h.accept(25)
    h.accept(6)
    h.accept(7)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, Card.Card.DIAMONDS)
    self.assertEqual(count, 5)
    self.assertEqual(rank, he.HandEvaluation.ROYAL_FLUSH)


  def testRoyalFlushRiver(self):
    h = Hand.Hand(0)

    d = 2
    h.accept(13*d+11)
    h.accept(13*d+0)
    h.accept(6)
    h.accept(13*d+12)
    h.accept(7)
    h.accept(13*d+10)
    h.accept(13*d+9)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, d)
    self.assertEqual(count, 5)
    self.assertEqual(rank, he.HandEvaluation.ROYAL_FLUSH)

  def testStraightFlushHeart(self):
    h = Hand.Hand(0)

    d = 0

    h.accept(13*d+2)
    h.accept(15)
    h.accept(13*d+5)
    h.accept(13*d+4)
    h.accept(13*d+1)
    h.accept(32)
    h.accept(13*d+3)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, d)
    self.assertEqual(count, 5)
    self.assertEqual(rank, he.HandEvaluation.STRAIGHT_FLUSH)

  def testStraightFlushSpades(self):
    h = Hand.Hand(0)

    d = 3

    h.accept(13*d+2)
    h.accept(15)
    h.accept(13*d+1)
    h.accept(13*d+4)
    h.accept(22)
    h.accept(13*d+0)
    h.accept(13*d+3)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, d)
    self.assertEqual(count, 5)
    self.assertEqual(rank, he.HandEvaluation.STRAIGHT_FLUSH)

  def testFourOfKindFlop(self):
    h = Hand.Hand(0)

    d = 3

    h.accept(13*1+2)
    h.accept(13*2+2)
    h.accept(13*0+2)
    h.accept(51)
    h.accept(13*3+2)
    h.accept(16)
    h.accept(22)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.FOUR_OF_A_KIND)

  def testFourOfKindTurn(self):
    h = Hand.Hand(0)

    d = 3

    h.accept(13*1+d)
    h.accept(13*3+d)
    h.accept(51)
    h.accept(13*0+d)
    h.accept(17)
    h.accept(13*2+d)
    h.accept(22)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.FOUR_OF_A_KIND)

  def testFourOfKindRiver(self):
    h = Hand.Hand(0)

    d = 0

    h.accept(13*1+d)
    h.accept(13*3+d)
    h.accept(51)
    h.accept(13*0+d)
    h.accept(17)
    h.accept(22)
    h.accept(13*2+d)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.FOUR_OF_A_KIND)

  def testFourOfKindBoard(self):
    h = Hand.Hand(0)

    d = 0

    h.accept(51)
    h.accept(17)
    h.accept(13*1+d)
    h.accept(13*3+d)
    h.accept(13*0+d)
    h.accept(22)
    h.accept(13*2+d)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.FOUR_OF_A_KIND)

  def testFullHouseFlop(self):
    h = Hand.Hand(0)

    d = 0
    e = 1

    h.accept(13*1+d)
    h.accept(13*3+d)
    h.accept(13*0+d)
    h.accept(13*1+e)
    h.accept(22)
    h.accept(13*2+e)
    h.accept(17)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.FULL_HOUSE)

  def testFlushFlop(self):
    h = Hand.Hand(0)

    d = 0

    h.accept(13*d+3)
    h.accept(13*d+7)
    h.accept(13*d+2)
    h.accept(13*d+9)
    h.accept(13*d+4)
    h.accept(22)
    h.accept(17)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.FLUSH)

  def testStraightFlop(self):
    h = Hand.Hand(0)

    h.accept(13*1+3)
    h.accept(13*3+1)
    h.accept(13*0+2)
    h.accept(13*2+5)
    h.accept(13*1+4)
    h.accept(22)
    h.accept(18)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.STRAIGHT)

  def testThreeOfKindFlop(self):
    h = Hand.Hand(0)

    h.accept(13*1+3)
    h.accept(13*3+3)
    h.accept(33)
    h.accept(13*2+3)
    h.accept(13*1+1)
    h.accept(22)
    h.accept(18)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.THREE_OF_A_KIND)
    

  def testTwoPairsFlop(self):
    h = Hand.Hand(0)

    h.accept(13*1+3)
    h.accept(13*3+1)
    h.accept(13*0+3)
    h.accept(13*2+5)
    h.accept(13*1+1)
    h.accept(22)
    h.accept(18)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.TWO_PAIR)

  def testPocketPair(self):
    h = Hand.Hand(0)

    h.accept(13*1+3)
    h.accept(13*3+3)
    h.accept(13*0+1)
    h.accept(13*2+2)
    h.accept(13*1+4)
    h.accept(22)
    h.accept(19)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.PAIR)
    
  def testHighCard(self):
    h = Hand.Hand(0)

    h.accept(13*1+3)
    h.accept(13*3+7)
    h.accept(13*0+1)
    h.accept(13*2+2)
    h.accept(13*1+4)
    h.accept(13*1+9)
    h.accept(13*1+12)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, he.HandEvaluation.HIGH_CARD)

if __name__ == '__main__':
  unittest.main()


