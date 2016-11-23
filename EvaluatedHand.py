#! /usr/bin/env python

class EvaluatedHand:
  """ A Poker hand that has been evaluated"""

  def __init__(self, handId, evaluation):
    self.handId = handId
    self.evaluation = evaluation

  def __eq__(self, other):
    return self.numericValue == other.numericValue

  def __repr__(self):
    return str(self.handId)+":"+self.strSuits[self.evaluation]

if __name__ == '__main__':
  c = EvaluatedHand(14)
  print c.suit()

