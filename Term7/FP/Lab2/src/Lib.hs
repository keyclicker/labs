module Lib where

import GHC.Conc.Sync (par, pseq, numCapabilities)


integral :: (Double, Double) -> (Double -> Double) -> Double -> Bool -> Double
integral (intA, intB) fun prec isConc = 
  integralIterator (riemannSum [intA, intB] fun isConc) 1 (intA, intB) fun prec isConc


integralIterator :: Double -> Double -> (Double, Double) -> (Double -> Double) -> Double -> Bool -> Double
integralIterator lastInt lastN (intA, intB) fun prec paral
  | prec > abs (lastInt - currentInt) = currentInt
  | otherwise = integralIterator currentInt currentN (intA, intB) fun prec paral
  where currentN = lastN * 2
        currentInt = riemannSum (createPartition (intA, intB) currentN) fun paral


riemannSum :: [Double] -> (Double -> Double) -> Bool -> Double
riemannSum partition fun paral = sum (riemannIteratorPar partition fun paral 1)


createPartition :: (Double, Double) -> Double -> [Double]
createPartition (intA, intB) n
  | intA > intB = createPartition (intB, intA) n
  | otherwise = [intA, intA+(intB-intA)/n .. intB]


riemannIteratorPar :: [Double] -> (Double -> Double) -> Bool -> Int -> [Double]
riemannIteratorPar [a] _ _ _ = []
riemannIteratorPar (p:q:r) fun paral num
    | paral && num <= numCapabilities = (tailR `par` headR) `pseq` (headR : tailR)
    | otherwise = headR:tailR
    where 
        headR = riemannBlock p q fun 
        tailR = riemannIteratorPar (q:r) fun paral (num + 1)


riemannBlock :: Double -> Double -> (Double -> Double) -> Double
riemannBlock intA intB fun
  | intA > intB = riemannBlock intB intA fun
  | otherwise = (fun intA + fun intB) / 2.0 * (intB-intA) 








