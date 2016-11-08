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

  def buildBoardsConsideringWholeCards(self, wholeCards):
    hands = []

    st= 0
  
    nc = 52
    count = 0

    for i in range(0, nc):
      print i
      nWholeCardsUsed = 0
      if wholeCards[i]: nWholeCardsUsed += 1
      for j in range(i+1, nc):
        if wholeCards[j]: nWholeCardsUsed += 1
        for k in range(j+1, nc):
          if wholeCards[k]: nWholeCardsUsed += 1
          for l in range(k+1, nc):
            if wholeCards[l]: nWholeCardsUsed += 1
            for m in range(l+1, nc):
              if wholeCards[m]: nWholeCardsUsed += 1
              for n in range(m+1, nc):
                if wholeCards[n]: nWholeCardsUsed += 1
                for o in range(n+1, nc):
                  if wholeCards[o]: nWholeCardsUsed += 1
                  if nWholeCardsUsed == 2:
                    hands.append([i, j, k, l, m, n, o])
                    count += 1
                  if wholeCards[o]: nWholeCardsUsed -= 1
                if wholeCards[n]: nWholeCardsUsed -= 1
              if wholeCards[m]: nWholeCardsUsed -= 1
            if wholeCards[l]: nWholeCardsUsed -= 1
          if wholeCards[k]: nWholeCardsUsed -= 1
        if wholeCards[j]: nWholeCardsUsed -= 1
      if wholeCards[i]: nWholeCardsUsed -= 1
    print
    return hands

  def buildBoards2(self, wholeCards):
    hands = []

    st= 0
  
    nc = 52
    count = 0

    wholeCardsAndBoard = [0]*52
    for i, x in enumerate(wholeCardsAndBoard):
      if wholeCards[i]:
        wholeCardsAndBoard[i] = 1
    print wholeCardsAndBoard

    for i in range(0, nc):
      print i,
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
                hands.append([p for p in range(52) if wholeCardsAndBoard[p]])
                count += 1
              wholeCardsAndBoard[m] = 0
            wholeCardsAndBoard[l] = 0
          wholeCardsAndBoard[k] = 0
        wholeCardsAndBoard[j] = 0
      wholeCardsAndBoard[i] = 0
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

  #handsWithWholeCards = he.buildBoardsConsideringWholeCards(wholeCards)
  handsWithWholeCards = he.buildBoards2(wholeCards)
  print "Unique hands  :", len(handsWithWholeCards)
  #cPickle.dump(hands, output)

  #output.close()

