#! /usr/bin/env python

import Card
import Hand

import cPickle

class HandsLoader:
  """ Loads all possible 5-card hands """

  def __init__(self):
    self.hands = []

  def loadHands(self, filename):
    pkl_file = open(filename, 'rb')
    hands = cPickle.load(pkl_file)
    return hands

  def handsForHoleCards(self, hands, c1, c2):
    for hand in hands:
      

if __name__ == '__main__':
   
  he = HandsLoader()
  print "Loading hands..."
  hands = he.loadHands('hands.db')
  print "Unique hands  :", len(hands)

