流程的部分，可以看source檔中的註解；這段程式碼是從最早的ItemRank一直修過來的，有些function已經註解掉，也有些不會被呼叫，所以看起來有點亂。
如果按照目前的參數，直接跑壓縮檔中的training set/testing set，應該費時18秒左右，label數目為3，clustering數目為269，DOA：95.7692%，RMSE0.989858，MAE0.744268