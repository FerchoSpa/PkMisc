#! /usr/bin/env python

import Card
import Hand

import pickle

class HandsBuilder:
  """ Builds all possible 5-card hands """

  def __init__(self):
    self.cards = []

  def buildHands(self):
    hands = []

    st= 0
  
    counters = {}
    counters[0] = 0
  
    nc = 52
    count = 0
    cards = {}
    for i in range(0, nc):
      cards[i] = Card.Card(i)

    for i in range(0, nc):
      print i
      c1 = cards[i]
      for j in range(i+1, nc):
        c2 = cards[j]
        #"""
        for k in range(j+1, nc):
          c3 = cards[k]
          for l in range(k+1, nc):
            c4 = cards[l]
            for m in range(l+1, nc):
              count += 1
              c5 = cards[m]
              h = Hand.Hand()
              h.accept(c1)
              h.accept(c2)
              h.accept(c3)
              h.accept(c4)
              h.accept(c5)
              counters[0] += 1
              hands.append(h)
        #"""
    return hands

if __name__ == '__main__':
   
  output = open('hands.db', 'wb')

  he = HandsBuilder()
  hands = he.buildHands()
  print "Unique hands  :", len(hands)

  pickle.dump(hands, output)

  output.close()

