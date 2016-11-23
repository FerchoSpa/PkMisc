#! /usr/bin/env python

import Card
import Hand
import HandEvaluation as he
import BoardsBuilder as bb

class HandEvaluator:
  """ Evaluates a hand of Poker cards """

  def __init__(self):
    self.cards = []

  def evaluateSingleHand(self, c1, c2):
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

  def evaluateOneHand(self, wholeCards):
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

    boardBuilder = bb.BoardsBuilder()
    print "About to start"
    hands = boardBuilder.buildBoardsWithWholeCards(wholeCards)
    for hnd in hands:
      h = Hand.Hand(0)
      for card in hnd:
        h.accept(card)
      a, b = h.evaluate()
      count += 1
      counters[a] += 1

    return counters, count

  def evaluateOneHand2(self, wholeCards):
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

    wholeCardsAndBoard = [0]*52
    for i, x in enumerate(wholeCardsAndBoard):
      if wholeCards[i]:
        wholeCardsAndBoard[i] = 1
    print wholeCardsAndBoard

    for i in range(0, nc):
      print i
      if wholeCards[i]: continue
      wholeCardsAndBoard[i] = 1
      for j in range(i+1, nc):
        if wholeCards[j]: continue
        wholeCardsAndBoard[j] = 1
        for k in range(j+1, nc):
          if wholeCards[k]: continue
          wholeCardsAndBoard[k] = 1
          for l in range(k+1, nc):
            if wholeCards[l]: continue
            wholeCardsAndBoard[l] = 1
            for m in range(l+1, nc):
              if wholeCards[m]: continue
              wholeCardsAndBoard[m] = 1
              if sum(wholeCardsAndBoard) == 7:
                h = Hand.Hand(0)
                for p in range(52):
                  if wholeCardsAndBoard[p]:
                    h.accept(p)
                a, b = h.evaluate()
                counters[a] += 1
                count += 1
              wholeCardsAndBoard[m] = 0
            wholeCardsAndBoard[l] = 0
          wholeCardsAndBoard[k] = 0
        wholeCardsAndBoard[j] = 0
      wholeCardsAndBoard[i] = 0
    print

    return counters, count

if __name__ == '__main__':
  hev = HandEvaluator()
  c, count = hev.evaluateSingleHand(0, 1)
  fullWholeCards = [0]*52
  fullWholeCards[0] = 1
  fullWholeCards[1] = 1
  #c, count = hev.evaluateOneHand(fullWholeCards)
  #c, count = hev.evaluateOneHand2(fullWholeCards)
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
