#! /usr/bin/env python

import Card
import Hand
import array

import cPickle

class BoardsBuilder:
  """ Builds all possible 5-card hands """

  def __init__(self):
    return

  def buildHands(self, wholeCards):
    hands = []

    st= 0
  
    nc = 52
    count = 0
    cards = {}
    for i in range(0, nc):
      cards[i] = Card.Card(i)

    for i in range(0, nc):
      print i,
      if wholeCards[i]: continue
      for j in range(i+1, nc):
        if wholeCards[j]: continue
        for k in range(j+1, nc):
          if wholeCards[k]: continue
          for l in range(k+1, nc):
            if wholeCards[l]: continue
            for m in range(l+1, nc):
              if wholeCards[m]: continue
              hands.append([i, j, k, l, m])
              count += 1
    print
    return hands

if __name__ == '__main__':
   
  #output = open('boards.db', 'wb')

  he = BoardsBuilder()
  wholeCards = array.array('l', [0]*52)
  wholeCards[30] = 1
  wholeCards[31] = 1
  hands = he.buildHands(wholeCards)
  print "Unique hands  :", len(hands)

  #cPickle.dump(hands, output)

  #output.close()

