#!/usr/bin/env stack
-- stack --install-ghc runghc

{-# LANGUAGE OverloadedStrings #-}
module Main where

import Connector ( connectDB, deployDB, closeDB )
import qualified Interaction as I ( doAction )


main :: IO ()
main = do
	conn <- connectDB
	deployDB conn

	I.doAction conn
	
	closeDB conn
