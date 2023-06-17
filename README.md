# Linear-Hashing
Implemented Linear hashing in secondary memory. Also implement insert and search operations on Linear hashing.
## Problem:
### Dataset Creation:
create a synthetic table (simulating sales records of department stores) containing 60000 records. Each record in this file contains four fields: (1) Transaction ID (an integer), (2) Transaction sale amount (an integer), (3) Customer name (string) and, (4) category of item. Transaction ID is an integer to identify each transaction uniquely in the dataset. You can create this field using a simple “counter” in your code. Transaction sale amount is a random integer between 1 and 80000. Customer name is a random 3 letter string. You can model this as a character array of length 3. Category of the item is a random integer between 1 --1500.

### Linear Hashed File:
After creating this dataset, you need to store it in a linear hashed file. The file would be hashed on the Transaction ID
attribute of the records. This linear hashed file should be implemented in a secondary memory. Assume that the size of 1
bucket is 1 disk block in your secondary memory. In your code, you need to define a disk block as a file which can store
only B records of the synthetic table. Assume an unspanned organization i.e., records are not allowed to span across two
disk blocks. Do not hard code the value of B. It may be changed during the evaluation. You would have to name the disk
block simulating files as 1.txt, 2.txt, 3.txt, etc. Basically the filenames should correspond to the bucket addresses
generated by your hash function. Overflow buckets also need to be stored using the same simulated disk blocks.
Moreover, the overflow buckets should be linked to the main bucket. This linking can be done by storing the name of the
file simulating the disk block corresponding to the overflow at the end of the main bucket disk block. Similar things can
be done for linking the overflow buckets as well. Records need to be inserted one by one.


### How the program runs:
Just run the program and Dataset will automatically be created at first and stored in a file named "demo.txt".
After that, insertion will take place and Linear Hashing will be applied.
After all records inserted, it'll ask the record which we want to search in which we provide the record number.
And if record is there it will show at which line and in which file the particular record is residing.
ByDefault, capacity(B records) is 5 and dataset is 15. These are defined in program at the topmost lines which can be further changed accordingly.

