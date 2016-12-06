from fileio import write_txt_file
from fileio import read_txt_file

"""
Python script shuffle_list_batch_write.py: 
Shuffles the lines in a txt file and writes them to a new file. 
Optionally, the output is split into several batches.
"""
import random

txt_list = "/Users/oliver/data/cache/cl1236_sam610.txt"
# txt_list = "/Users/oliver/data/cache/test_simple.txt"
# image_list = "/Users/oliver/data/tmp/0.png 6"


if __name__ == '__main__':
  batch_size = 1000
  big_list = read_txt_file(txt_list)
  i = 0
  while big_list:
    batch = [big_list.pop(random.randrange(len(big_list)))
            for _ in range(min(batch_size,len(big_list)))]

    write_txt_file("/Users/oliver/data/imgdb/data_batch_"
                   + str(i) + ".txt", batch)
    i +=1
  print("Done!")
