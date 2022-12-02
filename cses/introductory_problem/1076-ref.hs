-- https://cses.fi/problemset/hack/1076/entry/4178207/
import qualified Data.ByteString.Char8 as C
import qualified Data.IntSet as S
import qualified Data.ByteString.Lazy as B
import qualified Data.ByteString.Builder as BB
import Data.Bits

print1 :: [Int] -> Char -> IO ()
print1 a c = do
  let c1 = BB.char7 c
      f y = mappend (BB.intDec y) c1
      x = mconcat $ map f a
  B.putStr $ BB.toLazyByteString x

readInts :: IO [Int]
readInts = do
  s <- C.getLine
  let read1 x = let Just (y,_) = C.readInt x in y
  return $! map read1 (C.words s)

type MS = (Int,S.IntSet)
type MS2 = (MS,MS)

-- assume x not in s
insert1 :: Int -> MS -> MS
insert1 x (c,s) = (c+1,S.insert x s)

-- assume x in s
delete1 :: Int -> MS -> MS
delete1 x (c,s) = (c-1,S.delete x s)

init1 :: MS
init1 = (0,S.empty)

med2 :: MS2 -> Int
med2 ((_,s1),_) = S.findMax s1

-- assume size diff between s1, s2 <= 1
balance2 :: MS2 -> MS2
balance2 mm@((c1,s1),(c2,s2))
  | c1 < c2 =
    let (x,s2') = S.deleteFindMin s2
        s1' = S.insert x s1
    in ((c1+1,s1'), (c2-1,s2'))
  | c1 > c2+1 =
    let (x,s1') = S.deleteFindMax s1
        s2' = S.insert x s2
    in ((c1-1,s1'), (c2+1,s2'))
  | otherwise = mm

-- maintain size diff <= 1 property
insert2 :: Int -> MS2 -> MS2
insert2 x mm@(m1@(c1,_),m2)
  | c1 == 0 || med2 mm > x =
    balance2 (insert1 x m1, m2)
  | otherwise =
    balance2 (m1, insert1 x m2)

-- main size diff <= 1 property
delete2 :: Int -> MS2 -> MS2
delete2 x mm@(m1,m2)
  | med2 mm >= x =
    balance2 (delete1 x m1, m2)
  | otherwise =
    balance2 (m1, delete1 x m2)

init2 :: MS2
init2 = (init1,init1)

solve1 :: Int -> [Int] -> [Int] -> MS2 -> [Int]
solve1 _ [] _ _ = []
solve1 1 (a:as) (b:bs) mm =
  let mm1 = insert2 a mm
      res = med2 mm1
      mm2 = delete2 b mm1
  in res : solve1 1 as bs mm2
solve1 k (a:as) bs mm | k > 1 = -- insert till k element before start emitting answers
  let mm1 = insert2 a mm
  in solve1 (k-1) as bs mm1
solve1 _ _ _ _ = undefined

-- hash elements by (x << 20) + 1 to make every element unique
solve :: Int -> [Int] -> [Int]
solve k a0 =
  let a = map(\(i, x) -> shift x 20 + i) $ zip [0..] a0
      res = solve1 k a a init2
  in map (\x -> shift x (-20)) res

main :: IO ()
main = do
  [_,k] <- readInts
  a <- readInts
  let ans = solve k a
  print1 ans ' '
