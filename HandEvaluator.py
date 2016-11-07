#! /usr/bin/env python

import Card
import Hand
import HandEvaluation as he

class HandEvaluator:
  """ Evaluates a hand of Poker cards """

  def __init__(self):
    self.cards = []

  def evaluateSingleHand(self, c1, c2):

    st= 0
  
    counters = {}
    counters[he.HandEvaluation.NONE]            = 0
    counters[he.HandEvaluation.ROYAL_FLUSH]     = 0
    counters[he.HandEvaluation.STRAIGHT_FLUSH]  = 0
    counters[he.HandEvaluation.FOUR_OF_A_KIND]  = 0
    counters[he.HandEvaluation.FULL_HOUSE]      = 0
    counters[he.HandEvaluation.FLUSH]           = 0
    counters[he.HandEvaluation.STRAIGHT]        = 0
    counters[he.HandEvaluation.THREE_OF_A_KIND] = 0
    counters[he.HandEvaluation.TWO_PAIR]        = 0
    counters[he.HandEvaluation.PAIR]            = 0
    counters[he.HandEvaluation.HIGH_CARD]       = 0
  
    nc = 52
    count = 0

    h = Hand.Hand(0)
    h.accept(c1)
    h.accept(c2)
    for i in range(0, nc):
      if i == c1 or i == c2: continue
      print i
      h.accept(i)
      for j in range(i+1, nc):
        if j == c1 or j == c2: continue
        h.accept(j)
        for k in range(j+1, nc):
          if k == c1 or k == c2: continue
          h.accept(k)
          for l in range(k+1, nc):
            if l == c1 or l == c2: continue
            h.accept(l)
            for m in range(l+1, nc):
              if m == c1 or m == c2: continue
              #print i, j, k, l, m, " : ",
              count += 1
  
              h.accept(m)
  
              a, b = h.evaluate()
              counters[a] += 1

              h.removeLast()
            h.removeLast()
          h.removeLast()
        h.removeLast()
      h.removeLast()
    h.removeLast()

    return counters, count

if __name__ == '__main__':
  hev = HandEvaluator()
  c, count = hev.evaluateSingleHand(0, 1)
  print "Unique hands  :", count
  print "Royal Flush   :", c[he.HandEvaluation.ROYAL_FLUSH], " : ", (100.0*c[he.HandEvaluation.ROYAL_FLUSH])/count
  print "Straight Flush:", c[he.HandEvaluation.STRAIGHT_FLUSH], " : ", (100.0*c[he.HandEvaluation.STRAIGHT_FLUSH])/count
  print "4 of a Kind   :", c[he.HandEvaluation.FOUR_OF_A_KIND], " : ", (100.0*c[he.HandEvaluation.FOUR_OF_A_KIND])/count
  print "Full House    :", c[he.HandEvaluation.FULL_HOUSE],  " : ", (100.0*c[he.HandEvaluation.FULL_HOUSE])/count
  print "Flush         :", c[he.HandEvaluation.FLUSH],  " : ", (100.0*c[he.HandEvaluation.FLUSH])/count
  print "Straight      :", c[he.HandEvaluation.STRAIGHT],  " : ", (100.0*c[he.HandEvaluation.STRAIGHT])/count
  print "3 of a kind   :", c[he.HandEvaluation.THREE_OF_A_KIND],  " : ", (100.0*c[he.HandEvaluation.THREE_OF_A_KIND])/count
  print "Two pairs     :", c[he.HandEvaluation.TWO_PAIR],  " : ", (100.0*c[he.HandEvaluation.TWO_PAIR])/count
  print "Pair          :", c[he.HandEvaluation.PAIR],  " : ", (100.0*c[he.HandEvaluation.PAIR])/count
  print "High Card     :", c[he.HandEvaluation.HIGH_CARD],  " : ", (100.0*c[he.HandEvaluation.HIGH_CARD])/count
