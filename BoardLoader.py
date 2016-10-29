#! /usr/bin/env python

import cPickle

class BoardLoader:
  """ Loads all possible 5-card boards """

  def __init__(self):
    return

  def loadHands(self, filename):
    pkl_file = open(filename, 'rb')
    boards = cPickle.load(pkl_file)
    return boards

  def handsForHoleCards(self, boards, c1, c2):
    handsWithAnyHoleCards = []
    for board in boards:
      if c1 in board or c2 in board:
        handsWithAnyHoleCards.append(board)
    return handsWithAnyHoleCards

  def boardsWithNeitherHoleCards(self, boards, c1, c2):
    handsWithNeitherHoleCards = []
    for board in boards:
      if c1 in board or c2 in board:
        continue
      handsWithNeitherHoleCards.append(board)
    return handsWithNeitherHoleCards

if __name__ == '__main__':
   
  he = BoardLoader()
  print "Loading boards..."
  boards = he.loadHands('boards.db')
  print "Unique boards  :", len(boards)
  c1 = 0
  c2 = 1
  handsWithC1C2 = he.handsForHoleCards(boards, c1, c2)
  handsWithNeitherC1C2 = he.boardsWithNeitherHoleCards(boards, c1, c2)
  print "With either  C1, C2:", len(handsWithC1C2)
  print "With neither C1, C2:", len(handsWithNeitherC1C2)

