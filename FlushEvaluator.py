#! /usr/bin/env python

import Card
import Hand

if __name__ == '__main__':

  """
  fl = 0
  for i in range(2,nc):
    for j in range(i+1, nc):
      for k in range(j+1, nc):
        for l in range(k+1, nc):
          for m in range(l+1, nc):
            #print i, j, k
            count += 1
            if isf(i, j, k, l, m): fl += 1
  """


  h = Hand.Hand()

  c = Card.Card(1); h.accept(c)
  c = Card.Card(7); h.accept(c)
  c = Card.Card(3); h.accept(c)
  c = Card.Card(13+3); h.accept(c)
  c = Card.Card(5); h.accept(c)
  c = Card.Card(4); h.accept(c)
  c = Card.Card(13*1+4); h.accept(c)

  a, b = h.evaluate()
  print a
  print b
  if a == Hand.Hand().VAL_FLUSH:
    print "Is FLUSH"

