import Data.Set

f :: String -> Char -> (Int, Int)
f "" ch = (0, 0)
f (x:xs) ch
  | ch == x = (c+1, mx)
  | otherwise = (0, mx)
  where (c, cur) = f xs x
        mx = max cur (c+1)

main :: IO ()
main = do
  str <- getLine
  let (_, res) = f str '-'
  print res
