#! /usr/bin/env python

import Card

class Hand:
  """ A Hand of Poker cards """

  VAL_NONE            = -1
  VAL_ROYAL_FLUSH     = 0
  VAL_STRAIGHT_FLUSH  = 1
  VAL_FOUR_OF_A_KIND  = 2
  VAL_FULL_HOUSE      = 3
  VAL_FLUSH           = 4
  VAL_STRAIGHT        = 5
  VAL_THREE_OF_A_KIND = 6
  VAL_TWO_PAIR        = 7
  VAL_PAIR            = 8
  VAL_HIGH_CARD       = 9

  def __init__(self):
    self.cards = []

  def accept(self, card):
    self.cards.append(card)

  def __repr__(self):
    return str(self.cards)

  def __sortCards(self):
    self.sortedCards = sorted(self.cards, key=lambda card: card.numericValue)

  # Returns a list of tuples(Card.SUIT, n)
  def __suitCount(self):
    card = self.cards[0]
    self.suitCountDict = {card.HEARTS : 0, card.DIAMONDS : 0, card.SPADES : 0, card.CLUBS : 0}
    for card in self.cards:
      self.suitCountDict[card.suit] += 1
    # Sort the suits in descending order of counts(the most counts first)
    sortedKeys = sorted(self.suitCountDict, key=self.suitCountDict.__getitem__, reverse=True)
    self.suitCountOrdered = [(k, self.suitCountDict[k]) for k in sortedKeys]

    return self.suitCountOrdered

  # Returns a list of tuples(Card.numericRank, n)
  def __faceCardCount(self):
    self.faceCountDict = {1:0, 2:0, 3:0, 4:0, 5:0, 6:0, 7:0, 8:0, 9:0, 10:0, 11:0, 12:0, 13:0}
    for card in self.cards:
      self.faceCountDict[card.numericRank] += 1
    # Sort the face values in descending order of counts(the most counts first)
    sortedKeys = sorted(self.faceCountDict, key=self.faceCountDict.__getitem__, reverse=True)
    self.faceCountOrdered = [(k, self.faceCountDict[k]) for k in sortedKeys]
    return self.faceCountOrdered

  def __isPair(self):
    vPair1, countPair1 = self.faceCountOrdered[0]
    return countPair1 == 2

  def __isTwoPairs(self):
    vPair1, countPair1 = self.faceCountOrdered[0]
    vPair2, countPair2 = self.faceCountOrdered[1]
    return countPair1 == 2 and countPair2 == 2

  def __isThreeOfKind(self):
    v, count = self.faceCountOrdered[0]
    return count == 3

  def __findLongestStraight(self, values):
    prev = values[0]
    n = 1
    nMax = n
    for v in values:
      if v == prev+1:
        n += 1
        if n>nMax:
          nMax = n
      else:
        n = 1
      prev = v
    return nMax

  def __isStraight(self):
    unrepeatedCards = []
    for card in self.cards:
      if card.numericRank not in unrepeatedCards:
        unrepeatedCards.append(card.numericRank)
        if card.numericRank == 1:
          # Add King + 1, so it can detect 10,J,Q,K,A
          unrepeatedCards.append(14)
    unrepeatedCards.sort()
    longestStraight = self.__findLongestStraight(unrepeatedCards)
    return longestStraight >= 5

  def __isFullHouse(self):
    v3, count3 = self.faceCountOrdered[0]
    v2, count2 = self.faceCountOrdered[1]
    return count3 == 3 and count2 >= 2

  def __isFourOfKind(self):
    v, count = self.faceCountOrdered[0]
    return count == 4

  # It doesn't consider Royal Flush (as it was evaluated already)
  def __isStraightFlushFromThisCard(self, suit, lCards):
    previousCard = lCards[0].numericRank
    count = 1
    for card in lCards[1:]:
      if card.suit != suit:
        return False
      if card.numericRank == previousCard+1:
        count += 1
        if count==5:
          return True
      else:
        count = 1
      previousCard = card.numericRank
    return False

  def __islStraightFlush(self, suit):
    # The hand has no repeats, its not a royal flush, and has at least 5 of same suit
    cardsInRoyalFlush = 0;
    for idx, card in enumerate(self.sortedCards):
      if card.suit == suit:
        return self.__isStraightFlushFromThisCard(suit, self.sortedCards[idx:])
    return False

  def __isRoyalFlush(self, suit):
    # The hand has no repeats, so count how many are in T, J, Q, K, A range for suit
    cardsInRoyalFlush = 0;
    for card in self.sortedCards:
      if card.suit == suit:
        if card.symbolicRank in [card.ACE, card.TEN, card.JACK, card.QUEEN, card.KING]:
          cardsInRoyalFlush += 1
    return cardsInRoyalFlush == 5

  def evaluate(self):
    if len(self.cards) != 7:
      return None
    self.__sortCards()
    self.__suitCount()

    suit, count = self.suitCountOrdered[0]

    # Only bother with RoyalFlush and Straight Flush if possible
    if count >= 5:
      if self.__isRoyalFlush(suit):
        return self.VAL_ROYAL_FLUSH, self.suitCountOrdered
      elif self.__islStraightFlush(suit):
       return self.VAL_STRAIGHT_FLUSH, self.suitCountOrdered
 
    self.__faceCardCount()

    if self.__isFourOfKind():
      return self.VAL_FOUR_OF_A_KIND, self.faceCountOrdered

    if self.__isFullHouse():
      return self.VAL_FULL_HOUSE, self.faceCountOrdered

    if count >= 5:
      return self.VAL_FLUSH, self.suitCountOrdered

    if self.__isStraight():
      return self.VAL_STRAIGHT, self.faceCountOrdered

    if self.__isThreeOfKind():
      return self.VAL_THREE_OF_A_KIND, self.faceCountOrdered

    if self.__isTwoPairs():
      return self.VAL_TWO_PAIR, self.faceCountOrdered

    if self.__isPair():
      return self.VAL_PAIR, self.faceCountOrdered

    return self.VAL_HIGH_CARD, self.suitCountOrdered

if __name__ == '__main__':
  h = Hand()

  c = Card.Card(1); h.accept(c)
  c = Card.Card(13+2); h.accept(c)
  c = Card.Card(3); h.accept(c)
  c = Card.Card(13+3); h.accept(c)
  c = Card.Card(5); h.accept(c)
  c = Card.Card(4); h.accept(c)
  c = Card.Card(13*1+4); h.accept(c)

  h.evaluate()

