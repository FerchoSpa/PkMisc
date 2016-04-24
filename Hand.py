#! /usr/bin/env python

import Card

class Hand:
  """ A Hand of Poker cards """

  VAL_NONE = -1
  VAL_ROYAL_FLUSH = 0
  VAL_FLUSH = 4

  def __init__(self):
    self.cards = []

  def accept(self, card):
    self.cards.append(card)

  def __sortCards(self):
    self.sortedCards = sorted(self.cards)

  # Returns a list of tuples(Card.SUIT, n)
  def __suitCount(self):
    card = self.cards[0]
    self.suitCountDict = {card.HEARTS : 0, card.DIAMONDS : 0, card.SPADES : 0, card.CLUBS : 0}
    for card in self.cards:
      self.suitCountDict[card.suit()] += 1
    # Sort the suits in descending order of counts(the most counts first)
    sortedKeys = sorted(self.suitCountDict, key=self.suitCountDict.__getitem__, reverse=True)
    self.suitCountOrdered = [(k, self.suitCountDict[k]) for k in sortedKeys]

    return self.suitCountOrdered


  def evaluate(self):
    if len(self.cards) != 7:
      return None
    self.__sortCards()
    self.__suitCount()

    suit, count = self.suitCountOrdered[0]
    print suit, count
    return self.VAL_FLUSH, self.suitCountOrdered

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

