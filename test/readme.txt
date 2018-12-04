以下所提到的matrix皆為以linked list實現的sparse matrix
架構如同課本上的一樣 
1. 參考課本上的範例code，加以改良
    1.1 移除用不到的"tag"
    1.2 課本上原本並沒有將相同column鏈結起來
        => 在mread()時每加入一個元素時，就將它接在該column最後
           並將其的"down"指向該column的頭
    1.3 課本沒有mtranspose()和mmult()自己加上
2. mtranspose(req)
    2.1 創建一個新的matrix res，儲存轉置後的結果
    2.2 每次讀取req一個column，存到res新的一個column
    2.3 存入res的方法相當於再mmread()一個新的matrix
        => 只是這次不用等輸入，直接從要被轉置的matrix拿
    2.4 最後回傳res
3. mmult(req1, req2)
    3.1 先檢查req1的column數量等不等於req2的row數量
        3.1.1 如果相等繼續執行
        3.1.2 如果不相等回傳NULL
    3.2 創建一個新的matrix res，儲存相乘後的結果
    3.3 每次從req1抓一個新的row，如果該row為空就抓下一個row
    3.4 每次從req2抓一個新的column，如果該column為空就抓下一個column
        => 如果抓到req1和req2非零項位置相對應(req1.col==req2.row)
           相乘並儲存到用來暫存的二維矩陣相對應的位置
    3.5 完成後再將結果存進res，然後回傳res