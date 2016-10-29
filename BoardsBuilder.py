#! /usr/bin/env python

import Card
import Hand

import cPickle

class BoardsBuilder:
  """ Builds all possible 5-card hands """

  def __init__(self):
    return

  def buildHands(self):
    hands = []

    st= 0
  
    nc = 52
    count = 0
    cards = {}
    for i in range(0, nc):
      cards[i] = Card.Card(i)

    for i in range(0, nc):
      print i,
      c1 = cards[i]
      for j in range(i+1, nc):
        c2 = cards[j]
        for k in range(j+1, nc):
          c3 = cards[k]
          for l in range(k+1, nc):
            c4 = cards[l]
            for m in range(l+1, nc):
              c5 = cards[m]
              hands.append([i, j, k, l, m])
              count += 1
      print
    return hands

if __name__ == '__main__':
   
  #output = open('boards.db', 'wb')

  he = BoardsBuilder()
  hands = he.buildHands()
  print "Unique hands  :", len(hands)

  #cPickle.dump(hands, output)

  #output.close()

