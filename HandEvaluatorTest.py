#! /usr/bin/env python

import unittest

import Hand
import HandEvaluator

class TestHandEvaluatorMethods(unittest.TestCase):

  def testHandOnePlayerAgainstDeck(self):
    he = HandEvaluator.HandEvaluator()
    c, count = he.evaluateSingleHand(0, 1)

    self.assertEqual(count, 2118760)
    self.assertEqual(c[Hand.Hand().VAL_ROYAL_FLUSH], 49)
    self.assertEqual(c[Hand.Hand().VAL_STRAIGHT_FLUSH], 1113)
    self.assertEqual(c[Hand.Hand().VAL_FOUR_OF_A_KIND], 2668)
    self.assertEqual(c[Hand.Hand().VAL_FULL_HOUSE], 47124)
    self.assertEqual(c[Hand.Hand().VAL_FLUSH], 138296)
    self.assertEqual(c[Hand.Hand().VAL_STRAIGHT], 65508)
    self.assertEqual(c[Hand.Hand().VAL_THREE_OF_A_KIND], 92004)
    self.assertEqual(c[Hand.Hand().VAL_TWO_PAIR], 469092)
    self.assertEqual(c[Hand.Hand().VAL_PAIR], 916776)
    self.assertEqual(c[Hand.Hand().VAL_HIGH_CARD], 386130)

    """
Unique hands  : 2118760
Royal Flush   : 49  :  0.00231267345051
Straight Flush: 1113  :  0.0525307255187
4 of a Kind   : 2668  :  0.125922709509
Full House    : 47124  :  2.22413109555
Flush         : 138296  :  6.52721403085
Straight      : 65508  :  3.09180841624
3 of a kind   : 92004  :  4.34235118654
Two pairs     : 469092  :  22.139930903
Pair          : 916776  :  43.2694594952
High Card     : 386130  :  18.2243387642
    """


if __name__ == '__main__':
  unittest.main()


