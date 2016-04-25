#! /usr/bin/env python

import unittest

import Hand
import Card

class TestHandMethods(unittest.TestCase):

  def testAllHeart(self):
    h = Hand.Hand()

    c = Card.Card(1); h.accept(c)
    c = Card.Card(2); h.accept(c)
    c = Card.Card(3); h.accept(c)
    c = Card.Card(4); h.accept(c)
    c = Card.Card(5); h.accept(c)
    c = Card.Card(6); h.accept(c)
    c = Card.Card(7); h.accept(c)

    rank, hv = h.evaluate()
    print "fer:", hv
    self.assertEqual(len(hv), 4)

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
    print "fer:", hv
    self.assertEqual(len(hv), 4)
    suit, count = hv[0]
    self.assertEqual(suit, c.DIAMONDS)
    self.assertEqual(count, 5)
    self.assertEqual(rank, h.VAL_ROYAL_FLUSH)



if __name__ == '__main__':
  unittest.main()


