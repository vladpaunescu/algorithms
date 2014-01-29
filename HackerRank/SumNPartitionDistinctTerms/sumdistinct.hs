import Data.Array.IArray
main = do
x <- getLine -- 1 <= x <= 1000
y <- getLine -- 1 <= y <= 10
let xx = (read x :: Int)
   yy = (read y :: Int)
   max = limit xx yy 1
putStrLn $ show $ result xx yy max

limit :: Int -> Int -> Int -> Int
limit x y z = if z ^ y > x then z - 1
                          else limit x y (z + 1)

result :: Int -> Int -> Int -> Int
result m yy n = dp ! (m,n)
    where dp :: Array (Int,Int) Int
          dp = listArray ((0,0),(m,n)) [f i j | i <- [0 .. m], j <- [0 .. n]]
          f i j | i == 0 = 1
                | i == 0 || j == 0 = 0
                | i - j ^ yy < 0 = dp ! (i, j - 1)
                | otherwise = dp ! (i, j - 1) + dp ! (i - j ^ yy, j - 1)