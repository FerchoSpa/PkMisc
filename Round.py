#! /usr/bin/env python

import Hand
import Deck

class Round:
  """ A Round of N poker players(each has a Hand) """

  def __init__(self, numberOfPlayers):
    self.hands = []
    self.numberOfPlayers = numberOfPlayers

    # For efficiency, only use the cards that are needed for this players
    nCardsNeeded = numberOfPlayers*2 + 5
    self.deck = Deck.Deck(nCardsNeeded)

  def dealFirstTwoCards(self):
    for i in range(self.numberOfPlayers):
      hand = Hand.Hand()
      hand.accept(self.deck.dealCard())
      self.hands.append(hand)

    for hand in self.hands:
      hand.accept(self.deck.dealCard())


  def dealFlop(self):
    card = self.deck.dealCard()
    for hand in self.hands:
      hand.accept(card)

    card = self.deck.dealCard()
    for hand in self.hands:
      hand.accept(card)

    card = self.deck.dealCard()
    for hand in self.hands:
      hand.accept(card)


  def dealTurn(self):
    card = self.deck.dealCard()
    for hand in self.hands:
      hand.accept(card)

  def dealRiver(self):
    card = self.deck.dealCard()
    for hand in self.hands:
      hand.accept(card)

  def evaluate(self, i):
    hand = self.hands[i]
    return hand.evaluate()

  def deal(self):
    self.dealFirstTwoCards()
    self.dealFlop()
    self.dealTurn()
    self.dealRiver()

if __name__ == '__main__':
  r = Round(2);

  r.dealFirstTwoCards()
  r.dealFlop()
  r.dealTurn()
  r.dealRiver()
  r.evaluate()
