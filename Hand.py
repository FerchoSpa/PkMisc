#! /usr/bin/env python

import Card
import HandEvaluation as he

class Hand:
  """ A Hand of Poker cards """

  def __init__(self, handId):
    self.cardNumbers = []
    self.handId= handId
    self.suitCountDict = {Card.Card.HEARTS : 0, Card.Card.DIAMONDS : 0, Card.Card.SPADES : 0, Card.Card.CLUBS : 0}
    self.faceCountDict = {}

  def accept(self, cardNumber):
    self.cardNumbers.append(cardNumber)
    cardSuit = cardNumber / 13
    cardNumericRank = cardNumber % 13;
    self.suitCountDict[cardSuit] += 1
    if self.faceCountDict.has_key(cardNumericRank):
      self.faceCountDict[cardNumericRank] += 1
    else:
      self.faceCountDict[cardNumericRank]  = 1

  def __repr__(self):
    return str(self.cardNumbers)

  def __sortCards(self):
    #self.sortedCards = sorted(self.cardNumbers, key=lambda int: card.numericValue)
    self.sortedCards = sorted(self.cardNumbers)

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
    unrepeatedCardsSet = set([k%13 for k in self.cardNumbers])
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
    previousCard = lCards[0] % 13
    count = 1
    for card in lCards[1:]:
      cardSuit = card/13
      if cardSuit != suit:
        return False
      cardNumericRank = card % 13
      if cardNumericRank == previousCard+1:
        count += 1
        if count==5:
          return True
      else:
        count = 1
      previousCard = cardNumericRank
    return False

  def __islStraightFlush(self, suit):
    # The hand has no repeats, its not a royal flush, and has at least 5 of same suit
    cardsInRoyalFlush = 0;
    for idx, card in enumerate(self.sortedCards):
      cardSuit = card/13
      if cardSuit == suit:
        return self.__isStraightFlushFromThisCard(suit, self.sortedCards[idx:])
    return False

  def __isRoyalFlush(self, suit):
    # The hand has no repeats, so count how many are in T, J, Q, K, A range for suit
    cardsInRoyalFlush = 0;
    for card in self.sortedCards:
      cardSuit = card/13
      if cardSuit == suit:
        cardSymbolicRank = card%13
        if cardSymbolicRank in [0, 9, 10, 11, 12]:
          cardsInRoyalFlush += 1
    return cardsInRoyalFlush == 5

  def evaluate(self):
    if len(self.cardNumbers) != 7:
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
  h = Hand(0)

  """
  h.accept(1)
  h.accept(13+2)
  h.accept(3)
  h.accept(13+3)
  h.accept(5)
  h.accept(4)
  h.accept(13*1+4)

  h.evaluate()
  """

  """
  d = 0

  h.accept(13*d+2)
  h.accept(15)
  h.accept(13*d+5)
  h.accept(13*d+4)
  h.accept(13*d+1)
  h.accept(32)
  h.accept(13*d+3)

  rank, hv = h.evaluate()

  print len(hv), 4
  suit, count = hv[0]
  print suit, d
  print count, 5
  print rank, he.HandEvaluation.STRAIGHT_FLUSH
  """




  d = 3

  h.accept(13*d+2)
  h.accept(15)
  h.accept(13*d+1)
  h.accept(13*d+4)
  h.accept(22)
  h.accept(13*d+0)
  h.accept(13*d+3)

  rank, hv = h.evaluate()

  print len(hv), 4
  suit, count = hv[0]
  print suit, d
  print count, 5
  print rank, he.HandEvaluation.STRAIGHT_FLUSH


