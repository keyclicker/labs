module Main where

import Data.Time.Clock (diffUTCTime, getCurrentTime)
import Lib

main :: IO ()
main = let 
    inter = (-1, 1)
    fun = (\x -> 1 - x*x) 
    prec = 0.0000000000001
    in do
        putStrLn "Sequentially:"
        start1 <- getCurrentTime

        putStrLn $ "Res: " ++ show (integral inter fun prec False)
        end1 <- getCurrentTime
        putStrLn $ "Time: " ++ show (end1 `diffUTCTime` start1)


        putStrLn "\nConcurrently:"
        start2 <- getCurrentTime

        putStrLn $ "Res: " ++ show (integral inter fun prec True)
        end2 <- getCurrentTime
        putStrLn $ "Time: " ++ show (end2 `diffUTCTime` start2)