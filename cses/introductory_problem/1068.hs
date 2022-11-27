f :: Int -> [Int]
f x
  | x == 1 = [1]
  | x `mod` 2 == 0 = x:f (x `div` 2)
  | x `mod` 2 == 1 = x:f (x * 3 + 1)
 
p :: [Int] -> [Char]
p [] = ""
p xs = (show (xs!!0)) ++ (if length xs > 1 then " " else "") ++ (p (tail xs))
 
main = do
  x <- getLine
  putStrLn (p (f (read x :: Int)))
