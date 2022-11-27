
f :: [Int] -> Int -> Int
f (x:xs) mx
  | null xs = 0
  | otherwise = diff + f xs (xs!!0+diff)
  where diff = max 0 ((max mx x) - (xs!!0))

readNums :: String -> [Int]
readNums = map read . words

main :: IO ()
main = do
  n <- getLine
  str <- getLine
  let arr = readNums str
  print (f arr 0)
