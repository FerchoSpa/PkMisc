#! /usr/bin/env python

import Card
import Hand

if __name__ == '__main__':

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
  c1 = 0
  c2 = 1
  for i in range(0, nc):
    if i == c1 or i == c2: continue
    print i
    for j in range(i+1, nc):
      if j == c1 or j == c2: continue
      for k in range(j+1, nc):
        if k == c1 or k == c2: continue
        for l in range(k+1, nc):
          if l == c1 or l == c2: continue
          for m in range(l+1, nc):
            if m == c1 or m == c2: continue
            #print i, j, k, l, m, " : ",
            count += 1

            h = Hand.Hand()

            c = Card.Card(c1); h.accept(c)
            c = Card.Card(c2); h.accept(c)
            c = Card.Card(i); h.accept(c)
            c = Card.Card(j); h.accept(c)
            c = Card.Card(k); h.accept(c)
            c = Card.Card(l); h.accept(c)
            c = Card.Card(m); h.accept(c)

            a, b = h.evaluate()
            #print a, b
            counters[a] += 1
  print "Unique hands  :", count
  print "Royal Flush   :", counters[Hand.Hand().VAL_ROYAL_FLUSH], " : ", (100.0*counters[Hand.Hand().VAL_ROYAL_FLUSH])/count
  print "Straight Flush:", counters[Hand.Hand().VAL_STRAIGHT_FLUSH], " : ", (100.0*counters[Hand.Hand().VAL_STRAIGHT_FLUSH])/count
  print "4 of a Kind   :", counters[Hand.Hand().VAL_FOUR_OF_A_KIND], " : ", (100.0*counters[Hand.Hand().VAL_FOUR_OF_A_KIND])/count
  print "Full House    :", counters[Hand.Hand().VAL_FULL_HOUSE],  " : ", (100.0*counters[Hand.Hand().VAL_FULL_HOUSE])/count
  print "Flush         :", counters[Hand.Hand().VAL_FLUSH],  " : ", (100.0*counters[Hand.Hand().VAL_FLUSH])/count
  print "Straight      :", counters[Hand.Hand().VAL_STRAIGHT],  " : ", (100.0*counters[Hand.Hand().VAL_STRAIGHT])/count
  print "3 of a kind   :", counters[Hand.Hand().VAL_THREE_OF_A_KIND],  " : ", (100.0*counters[Hand.Hand().VAL_THREE_OF_A_KIND])/count
  print "Two pairs     :", counters[Hand.Hand().VAL_TWO_PAIR],  " : ", (100.0*counters[Hand.Hand().VAL_TWO_PAIR])/count
  print "Pair          :", counters[Hand.Hand().VAL_PAIR],  " : ", (100.0*counters[Hand.Hand().VAL_PAIR])/count
  print "High Card     :", counters[Hand.Hand().VAL_HIGH_CARD],  " : ", (100.0*counters[Hand.Hand().VAL_HIGH_CARD])/count
  return counters

