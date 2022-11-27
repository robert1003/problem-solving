import Data.List (intersperse)

g :: Int -> Int -> [Int]
g start end
  | start >= end = []
  | otherwise = [start] ++ g (start+2) end

f :: Int -> [Int]
f n
  | n == 2 || n == 3 = []
  | n == 4 = [3,1,4,2]
  | otherwise = [1] ++ (g 3 (n+1)) ++ (g 2 (n+1))


main :: IO ()
main = do
  n <- getLine
  let arr = f (read n)
  if null arr
  then putStrLn "NO SOLUTION"
  else putStrLn $ concat . intersperse " " $ map show arr
