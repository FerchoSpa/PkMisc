#! /usr/bin/env python

import Card
import Hand
import HandEvaluator

class HandEvaluator:
  """ Evaluates a hand of Poker cards """

  def __init__(self):
    self.cards = []

  def evaluateSingleHand(self, c1, c2):

    st= 0
  
    counters = {}
    counters[Hand.Hand().VAL_NONE] = 0
    counters[Hand.Hand().VAL_ROYAL_FLUSH] = 0
    counters[Hand.Hand().VAL_STRAIGHT_FLUSH] = 0
    counters[Hand.Hand().VAL_FOUR_OF_A_KIND] = 0
    counters[Hand.Hand().VAL_FULL_HOUSE] = 0
    counters[Hand.Hand().VAL_FLUSH] = 0
    counters[Hand.Hand().VAL_STRAIGHT] = 0
    counters[Hand.Hand().VAL_THREE_OF_A_KIND] = 0
    counters[Hand.Hand().VAL_TWO_PAIR] = 0
    counters[Hand.Hand().VAL_PAIR] = 0
    counters[Hand.Hand().VAL_HIGH_CARD] = 0
  
    nc = 52
    count = 0
    cards = {}
    for i in range(0, nc):
      cards[i] = Card.Card(i)

    for i in range(0, nc):
      if i == c1 or i == c2: continue
      print i
      h = Hand.Hand()
      c = cards[c1]; h.accept(c)
      c = cards[c2]; h.accept(c)
      c = cards[i];  h.accept(c)
      for j in range(i+1, nc):
        if j == c1 or j == c2: continue
        c = cards[j];  h.accept(c)
        for k in range(j+1, nc):
          if k == c1 or k == c2: continue
          c = cards[k];  h.accept(c)
          for l in range(k+1, nc):
            if l == c1 or l == c2: continue
            c = cards[l];  h.accept(c)
            for m in range(l+1, nc):
              if m == c1 or m == c2: continue
              #print i, j, k, l, m, " : ",
              count += 1
  
              c = cards[m];  h.accept(c)
  
              a, b = h.evaluate()
              #print a, b
              counters[a] += 1

              h.removeLast()
            h.removeLast()
          h.removeLast()
        h.removeLast()
    return counters, count

if __name__ == '__main__':
  he = HandEvaluator()
  c, count = he.evaluateSingleHand(0, 1)
  print "Unique hands  :", count
  print "Royal Flush   :", c[Hand.Hand().VAL_ROYAL_FLUSH], " : ", (100.0*c[Hand.Hand().VAL_ROYAL_FLUSH])/count
  print "Straight Flush:", c[Hand.Hand().VAL_STRAIGHT_FLUSH], " : ", (100.0*c[Hand.Hand().VAL_STRAIGHT_FLUSH])/count
  print "4 of a Kind   :", c[Hand.Hand().VAL_FOUR_OF_A_KIND], " : ", (100.0*c[Hand.Hand().VAL_FOUR_OF_A_KIND])/count
  print "Full House    :", c[Hand.Hand().VAL_FULL_HOUSE],  " : ", (100.0*c[Hand.Hand().VAL_FULL_HOUSE])/count
  print "Flush         :", c[Hand.Hand().VAL_FLUSH],  " : ", (100.0*c[Hand.Hand().VAL_FLUSH])/count
  print "Straight      :", c[Hand.Hand().VAL_STRAIGHT],  " : ", (100.0*c[Hand.Hand().VAL_STRAIGHT])/count
  print "3 of a kind   :", c[Hand.Hand().VAL_THREE_OF_A_KIND],  " : ", (100.0*c[Hand.Hand().VAL_THREE_OF_A_KIND])/count
  print "Two pairs     :", c[Hand.Hand().VAL_TWO_PAIR],  " : ", (100.0*c[Hand.Hand().VAL_TWO_PAIR])/count
  print "Pair          :", c[Hand.Hand().VAL_PAIR],  " : ", (100.0*c[Hand.Hand().VAL_PAIR])/count
  print "High Card     :", c[Hand.Hand().VAL_HIGH_CARD],  " : ", (100.0*c[Hand.Hand().VAL_HIGH_CARD])/count
