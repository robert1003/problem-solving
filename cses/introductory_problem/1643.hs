import qualified Data.ByteString.Char8 as C

readInts :: IO [Int]
readInts = do
  s <- C.getLine
  let read1 x = let Just (y, _) = C.readInt x in y
  return $! map read1 (C.words s)

f :: [Int] -> Int -> Int
f (a:as) sum
  | sum+a < 0 = max (sum+a) (f as 0)
  | otherwise = max (sum+a) (f as (sum+a))
f [] _ = -1000000000-1

main :: IO ()
main = do
  _ <- getLine
  as <- readInts
  print $ f as 0
