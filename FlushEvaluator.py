#! /usr/bin/env python

import Card
import Hand

if __name__ == '__main__':

  fl = 0
  fh = 0
  sfl = 0
  rfl= 0
  fok= 0
  st= 0
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
            if a == Hand.Hand().VAL_FLUSH:
              fl += 1
            if a == Hand.Hand().VAL_ROYAL_FLUSH:
              rfl += 1
            if a == Hand.Hand().VAL_STRAIGHT_FLUSH:
              sfl += 1
            if a == Hand.Hand().VAL_FOUR_OF_A_KIND:
              fok += 1
            if a == Hand.Hand().VAL_FULL_HOUSE:
              fh += 1
            if a == Hand.Hand().VAL_STRAIGHT:
              st += 1
  print "Unique hands  :", count
  print "Royal Flush   :", rfl, " : ", (100.0*rfl)/count
  print "Straight Flush:", sfl, " : ", (100.0*sfl)/count
  print "4 of a Kind   :", fok, " : ", (100.0*fok)/count
  print "Full House    :", fh,  " : ", (100.0*fh)/count
  print "Flush         :", fl,  " : ", (100.0*fl)/count
  print "Straight      :", st,  " : ", (100.0*st)/count

  print rfl+sfl+fl+fok

