#! /usr/bin/env python

import Card
import HandEvaluation as he

class Hand:
  """ A Hand of Poker cards """

  def __init__(self, handId):
    self.handId= handId
    self.cards = []
    self.suitCountDict = {Card.Card.HEARTS : 0, Card.Card.DIAMONDS : 0, Card.Card.SPADES : 0, Card.Card.CLUBS : 0}
    self.faceCountDict = {}

  def accept(self, card):
    self.cards.append(card)
    self.suitCountDict[card.suit] += 1
    if self.faceCountDict.has_key(card.numericRank):
      self.faceCountDict[card.numericRank] += 1
    else:
      self.faceCountDict[card.numericRank]  = 1

  """
  def removeLast(self):
    card = self.cards[-1]
    self.cards = self.cards[:-1]
    self.suitCountDict[card.suit] -= 1
    self.faceCountDict[card.numericRank] -= 1
  """

  def __repr__(self):
    return str(self.cards)

  def __sortCards(self):
    self.sortedCards = sorted(self.cards, key=lambda card: card.numericValue)

  # Returns a list of tuples(Card.SUIT, n)
  def __suitCount(self):
    # Sort the suits in descending order of counts(the most counts first)
    sortedKeys = sorted(self.suitCountDict, key=self.suitCountDict.__getitem__, reverse=True)
    self.suitCountOrdered = [(k, self.suitCountDict[k]) for k in sortedKeys]
    return self.suitCountOrdered

  # Returns a list of tuples(Card.numericRank, n)
  def __faceCardCount(self):
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
    unrepeatedCardsSet = set([k.numericRank for k in self.cards])
    unrepeatedCards = list(unrepeatedCardsSet)
    unrepeatedCards.sort()
    if unrepeatedCards[0]==1:
      # Add King + 1, so it can detect 10,J,Q,K,A
      unrepeatedCards.append(14)
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
        return he.HandEvaluation.ROYAL_FLUSH, self.suitCountOrdered
      elif self.__islStraightFlush(suit):
       return he.HandEvaluation.STRAIGHT_FLUSH, self.suitCountOrdered
 
    self.__faceCardCount()

    if self.__isFourOfKind():
      return he.HandEvaluation.FOUR_OF_A_KIND, self.faceCountOrdered

    if self.__isFullHouse():
      return he.HandEvaluation.FULL_HOUSE, self.faceCountOrdered

    if count >= 5:
      return he.HandEvaluation.FLUSH, self.suitCountOrdered

    if self.__isStraight():
      return he.HandEvaluation.STRAIGHT, self.faceCountOrdered

    if self.__isThreeOfKind():
      return he.HandEvaluation.THREE_OF_A_KIND, self.faceCountOrdered

    if self.__isTwoPairs():
      return he.HandEvaluation.TWO_PAIR, self.faceCountOrdered

    if self.__isPair():
      return he.HandEvaluation.PAIR, self.faceCountOrdered

    return he.HandEvaluation.HIGH_CARD, self.suitCountOrdered

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

