#! /usr/bin/env python

import unittest

import Hand
import Card

class TestHandMethods(unittest.TestCase):


  def testRoyalFlushFlop(self):
    h = Hand.Hand()

    c = Card.Card(13); h.accept(c)
    c = Card.Card(22); h.accept(c)
    c = Card.Card(23); h.accept(c)
    c = Card.Card(24); h.accept(c)
    c = Card.Card(25); h.accept(c)
    c = Card.Card(6); h.accept(c)
    c = Card.Card(7); h.accept(c)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, c.DIAMONDS)
    self.assertEqual(count, 5)
    self.assertEqual(rank, h.VAL_ROYAL_FLUSH)


  def testRoyalFlushRiver(self):
    h = Hand.Hand()

    d = 2
    c = Card.Card(13*d+11); h.accept(c)
    c = Card.Card(13*d+0); h.accept(c)
    c = Card.Card(6); h.accept(c)
    c = Card.Card(13*d+12); h.accept(c)
    c = Card.Card(7); h.accept(c)
    c = Card.Card(13*d+10); h.accept(c)
    c = Card.Card(13*d+9); h.accept(c)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, d)
    self.assertEqual(count, 5)
    self.assertEqual(rank, h.VAL_ROYAL_FLUSH)

  def testStraightFlushHeart(self):
    h = Hand.Hand()

    d = 0

    c = Card.Card(13*d+2); h.accept(c)
    c = Card.Card(15); h.accept(c)
    c = Card.Card(13*d+5); h.accept(c)
    c = Card.Card(13*d+4); h.accept(c)
    c = Card.Card(13*d+1); h.accept(c)
    c = Card.Card(32); h.accept(c)
    c = Card.Card(13*d+3); h.accept(c)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, d)
    self.assertEqual(count, 5)
    self.assertEqual(rank, h.VAL_STRAIGHT_FLUSH)

  def testStraightFlushSpades(self):
    h = Hand.Hand()

    d = 3

    c = Card.Card(13*d+2); h.accept(c)
    c = Card.Card(15); h.accept(c)
    c = Card.Card(13*d+1); h.accept(c)
    c = Card.Card(13*d+4); h.accept(c)
    c = Card.Card(22); h.accept(c)
    c = Card.Card(13*d+0); h.accept(c)
    c = Card.Card(13*d+3); h.accept(c)

    rank, hv = h.evaluate()

    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, d)
    self.assertEqual(count, 5)
    self.assertEqual(rank, h.VAL_STRAIGHT_FLUSH)

  def testFourOfKindFlop(self):
    h = Hand.Hand()

    d = 3

    c = Card.Card(13*1+2); h.accept(c)
    c = Card.Card(13*2+2); h.accept(c)
    c = Card.Card(13*0+2); h.accept(c)
    c = Card.Card(51); h.accept(c)
    c = Card.Card(13*3+2); h.accept(c)
    c = Card.Card(16); h.accept(c)
    c = Card.Card(22); h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_FOUR_OF_A_KIND)

  def testFourOfKindTurn(self):
    h = Hand.Hand()

    d = 3

    c = Card.Card(13*1+d); h.accept(c)
    c = Card.Card(13*3+d); h.accept(c)
    c = Card.Card(51); h.accept(c)
    c = Card.Card(13*0+d); h.accept(c)
    c = Card.Card(17); h.accept(c)
    c = Card.Card(13*2+d); h.accept(c)
    c = Card.Card(22); h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_FOUR_OF_A_KIND)

  def testFourOfKindRiver(self):
    h = Hand.Hand()

    d = 0

    c = Card.Card(13*1+d); h.accept(c)
    c = Card.Card(13*3+d); h.accept(c)
    c = Card.Card(51); h.accept(c)
    c = Card.Card(13*0+d); h.accept(c)
    c = Card.Card(17); h.accept(c)
    c = Card.Card(22); h.accept(c)
    c = Card.Card(13*2+d); h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_FOUR_OF_A_KIND)

  def testFourOfKindBoard(self):
    h = Hand.Hand()

    d = 0

    c = Card.Card(51); h.accept(c)
    c = Card.Card(17); h.accept(c)
    c = Card.Card(13*1+d); h.accept(c)
    c = Card.Card(13*3+d); h.accept(c)
    c = Card.Card(13*0+d); h.accept(c)
    c = Card.Card(22); h.accept(c)
    c = Card.Card(13*2+d); h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_FOUR_OF_A_KIND)

  def testFullHouseFlop(self):
    h = Hand.Hand()

    d = 0
    e = 1

    c = Card.Card(13*1+d); h.accept(c)
    c = Card.Card(13*3+d); h.accept(c)
    c = Card.Card(13*0+d); h.accept(c)
    c = Card.Card(13*1+e); h.accept(c)
    c = Card.Card(22); h.accept(c)
    c = Card.Card(13*2+e); h.accept(c)
    c = Card.Card(17); h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_FULL_HOUSE)

  def testFlushFlop(self):
    h = Hand.Hand()

    d = 0

    c = Card.Card(13*d+3); h.accept(c)
    c = Card.Card(13*d+7); h.accept(c)
    c = Card.Card(13*d+2); h.accept(c)
    c = Card.Card(13*d+9); h.accept(c)
    c = Card.Card(13*d+4); h.accept(c)
    c = Card.Card(22); h.accept(c)
    c = Card.Card(17); h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_FLUSH)

  def testStraightFlop(self):
    h = Hand.Hand()

    c = Card.Card(13*1+3); h.accept(c)
    c = Card.Card(13*3+1); h.accept(c)
    c = Card.Card(13*0+2); h.accept(c)
    c = Card.Card(13*2+5); h.accept(c)
    c = Card.Card(13*1+4); h.accept(c)
    c = Card.Card(22);     h.accept(c)
    c = Card.Card(18);     h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_STRAIGHT)

  def testThreeOfKindFlop(self):
    h = Hand.Hand()

    c = Card.Card(13*1+3); h.accept(c)
    c = Card.Card(13*3+3); h.accept(c)
    c = Card.Card(33);     h.accept(c)
    c = Card.Card(13*2+3); h.accept(c)
    c = Card.Card(13*1+1); h.accept(c)
    c = Card.Card(22);     h.accept(c)
    c = Card.Card(18);     h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_THREE_OF_A_KIND)
    

  def testTwoPairsFlop(self):
    h = Hand.Hand()

    c = Card.Card(13*1+3); h.accept(c)
    c = Card.Card(13*3+1); h.accept(c)
    c = Card.Card(13*0+3); h.accept(c)
    c = Card.Card(13*2+5); h.accept(c)
    c = Card.Card(13*1+1); h.accept(c)
    c = Card.Card(22);     h.accept(c)
    c = Card.Card(18);     h.accept(c)

    rank, hv = h.evaluate()

    face, count = hv[0]
    self.assertEqual(rank, h.VAL_TWO_PAIR)
    
if __name__ == '__main__':
  unittest.main()


