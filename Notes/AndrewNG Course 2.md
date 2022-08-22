# Personal Notes
## Sources: , [Coursera 2](https://www.coursera.org/learn/convolutional-neural-networks/home/week/1)
---
# WEEK 1:

* Sometimes image are too large for a Deep Neural Network to be applied.
* Thus to solve this we apply convolutions.
* Convolutions are some transformations applied to the original input image.
* For Convolutions, we need a Kernel/Filter:
    * A Kernel is a matrix with some predefined values which when convoluted over the input image gives the convoluted output image.
    * A Kernel is generally a square matrix with the dimensions 3x3, 4x4, 6x6, etc.
* When a Kernel is convoluted over the input image, elemental product of the kernel and the equivalent portion of the image are found and the resultant sum is output to the corresponding pixel of the output image.
* This operation is performed, shifting the part of image in focus, column by column and then row by row.
* Convolution can be used to detect edges (vertical, horizontal, etc).

![Convolution in 1 region](/Assets/Convolution_In_1_Part.png)

![Convolution in region shifted by 1 column](/Assets/Convolution_shifted_by_a_column.png)

* Similarly convolution is performed over all the regions of the input image.

## Vertical Edge Detector:
![Vertical Edge Detector working](/Assets/Vertical_Edge_detector.png)

* Thus vertical Edges can be detected using this.
* For detecting Horizontal Edges, the kernel used is:

|1      |1      |1   |
|:---   |:---:  |---:|
|0      |0      |0   |
|-1     |-1     |-1  |

* In case of image size of n x n, and filter size f x f, the size of the output image will be (n-f+1) x (n-f+1)
* Hence the size of the image shrinks.
* To prevent this, a padding is applied.
* The size of the padding is equal to (f-1)/2
## Strided Convolutions:
* The convolutions are applied for every sth column i.e. for s = 2, convolutions are applied for alternate columns.
* The output image size obtained will be:((n+2p-f)/s + 1) x ((n+2p-f)/s + 1) 
* In case the output dimensions are fractional, we round it down using floor() function.

## Convolutions Over Volume:
* If the image has 3 channeled input (RGB), it is represented by n x n x nc matrix.
### Note: The number of channels of input and output must be equal.

* Thus, for this type of image, we need a 3D filter of dimensions: f x f x nc
    * where nc is the number of channels of the input image
* Multiple such filters are used in case of CNNs.
* The output of each of the convolution filters is added to the bias and then activation function is applied.
* THe output of each filter is then stacked on top of each other, thus the dimensions of the matrix after stacking is : (n-f-1) x (n-f-1) x nf
    * where, nf is the number of filters applied.
# Single Layer CNN:
* Here A0 = X is the input image.
* A1 is the output obtained after convolution with multiple filters, then passig it through activation function with bias and stacking different filter outputs.
* this is then used as input for the next layer, similar to deep neural network.
* Hence, the filters act as weights.
* nf is analogous to number of nodes in the layer.

### Structure:
![Single layer CNN](/Assets/single_layer_cnn.png)

* Hence the number of parameters does no depend on the size of the input, but instead depends on the number of filters/nodes and the size of each filter.