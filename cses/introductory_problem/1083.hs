import Data.Set

buildset :: [Int] -> Set Int
buildset [] = empty
buildset xs = insert (head xs) (buildset (tail xs))

findmiss :: Set Int -> Int -> Int
findmiss set qry = if member qry set
  then findmiss set (qry+1)
  else qry

readnums :: String -> [Int]
readnums = Prelude.map read . words

main :: IO()
main = do
  n <- getLine
  nums <- getLine
  print $ (findmiss (buildset $ readnums nums) 1)
