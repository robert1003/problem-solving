import Data.List (intersperse)

f :: Int -> IO ()
f n
  | n == 0 = return ()
  | otherwise = do
      f (n-1)
      putStrLn $ show ((n*n)*(n*n-1) `div` 2 - (n-1)*(n-2)*4)

main :: IO ()
main = do
  n <- getLine
  f $ read n
