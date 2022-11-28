import Control.Monad
import Data.List (intersperse)

f :: Int -> Int -> Int
f x y
  | m `mod` 2 == 0 = m*m - (abs (x - m)) - (abs (y - 1))
  | m `mod` 2 == 1 = m*m - (abs (x - 1)) - (abs (y - m))
  where m = max x y

g :: [String] -> [Int]
g [] = []
g (t:ts) = [f (s!!0) (s!!1)] ++ (g ts)
  where s = map (\x -> read x :: Int) (words t)

main :: IO ()
main = do
  t <- getLine
  xys <- replicateM (read t) getLine
  putStrLn $ concat . intersperse "\n" $ map show (g xys)
