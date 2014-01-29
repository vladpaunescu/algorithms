import System.IO
import Data.List (intercalate)


pascal n = 
    let p = [1] : [ (zipWith (+) (x ++ [0]) (0:x)) | x <-p ] in
        take n p

main = do
    l <- getLine
    let n = (read l :: Int) in        
        putStr $ intercalate "\n" $ map (\l -> (foldl (\acc el-> acc ++ show el ++ " ") "" l) ) $ pascal n