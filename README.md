mnist-parser
============

Parser for MNIST database files.

More information about the MNIST database can be found at [[1]](http://yann.lecun.com/exdb/mnist/) and [[2]](http://en.wikipedia.org/wiki/MNIST_database).

Basically these are databases of handwritten digits and their labels.

Split into 4 files, 2 (image and label) for training and 2 of testing.

````
train-images-idx3-ubyte.gz:  training set images (9912422 bytes) 
train-labels-idx1-ubyte.gz:  training set labels (28881 bytes) 
t10k-images-idx3-ubyte.gz:   test set images (1648877 bytes) 
t10k-labels-idx1-ubyte.gz:   test set labels (4542 bytes)
````

The files are in a very simple format as follows:

#### TRAINING SET LABEL FILE (train-labels-idx1-ubyte):

````
[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000801(2049) magic number (MSB first)
0004     32 bit integer  60000            number of items
0008     unsigned byte    5               label
0009     unsigned byte    0               label
````
The labels values are 0 to 9.

#### TRAINING SET IMAGE FILE (train-images-idx3-ubyte):

````
[offset] [type]          [value]          [description]
0000     32 bit integer  0x00000803(2051) magic number
0004     32 bit integer  60000            number of images
0008     32 bit integer  28               number of rows
0012     32 bit integer  28               number of columns
0016     unsigned byte   ??               pixel
````

Pixels are organized row-wise. Pixel values are 0 to 255. 0 means background
(white), 255 means foreground (black).

#### Decoded Labels and Images

The file ````train_labels.txt.gz```` contains the label of image ````i```` on the ````i^{th}```` line.

The file ````train_images.txt.gz```` contains, on each row, the grey scale value of the pixels separated by a space in row major format, i.e. the rows are appended.

--

The parser was written to get back in some shape in C programming.
