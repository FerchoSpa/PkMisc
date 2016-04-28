#! /usr/bin/env python

import Round

if __name__ == '__main__':

  counts = [0, 0, 0, 0, 0, 0, 0, 0, 0, 0]
  
  for i in range(100000):
    r = Round.Round(1);
    r.deal()
    v, h = r.evaluate(0)
    #print i, v
    counts[v] += 1

  print counts

