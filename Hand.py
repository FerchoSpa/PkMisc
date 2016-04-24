#! /usr/bin/env python

import Card

class Hand:
  """ A Hand of Poker cards """

  VAL_NONE = -1
  VAL_ROYAL_FLUSH = 0

  def __init__(self):
    self.cards = []

  def accept(self, card):
    self.cards.append(card)

  def __suitCount(self):
    card = self.cards[0]
    suitCountDict = {card.HEARTS : 0, card.DIAMONDS : 0, card.SPADES : 0, card.CLUBS : 0}
    for card in self.cards:
      suitCountDict[card.suit()] += 1
    print suitCountDict


  def evaluate(self):
    if len(self.cards) != 7:
      return None
    self.__suitCount();
    return VAL_NONE, self.hand

if __name__ == '__main__':
  h = Hand()

  c = Card.Card(1); h.accept(c)
  c = Card.Card(2); h.accept(c)
  c = Card.Card(3); h.accept(c)
  c = Card.Card(4); h.accept(c)
  c = Card.Card(5); h.accept(c)
  c = Card.Card(6); h.accept(c)
  c = Card.Card(7); h.accept(c)

  h.evaluate()

