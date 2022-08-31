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

### Example:
![Example of CNN](/Assets/Example_of_CNN.png)

## Types of layers:
* Convolutional
* Pooling
* Fully Connected (FC)

>## Pooling:
### Max Pooling:
* The filter used if max filter, which just finds the max value in the corresponding apart of image.\
Eg:![Example of Pooling layer](/Assets/Pooling_layer_Example.png)

## Note: A pooling layer does not have any parameters, so gradient descent is not applicable to this layer.

### Average Pooling:
* Instead of max in the above mentioned step, avg is taken.
---
># Week 2

## LeNet-5:
Structure:

![LeNet5 Structure](/Assets/LeNet_5_structure.png)

* Old Network
* Realtively low number of parameters compared to today's standards.
* Dimension of image goes on decreasing.
* Number of channels goes on increasing.
---
## AlexNet:
Structure:
![Structure of Alexnet](/Assets/AlexNet.png)

* Bigger network than LeNet.

---
![Comparison](/Assets/Comparison_image_neural_networks.svg
)

---
## VGG-16:
![Structure of VGG-16](/Assets/VGG16.png)

* Very Big Network
* Simple trend od doubling channels and half dimensions
---
# **ResNets (Residual Networks):**
* Helps to train deep models.
* In a multi layered network, the input or any layer output A(l) is added to the A(l+i) layer output and then passed through the activation function, thus creating 2 paths, shortcut and main.
Structure:
![Structure of ResNet](/Assets/resnets.png)
* Any number of layers can be skipped.
* A(l) is added to Z(l+i) and the result is passed through activation function.

Example:
![ResNets Example](/Assets/resnets2.png)

---
# **Network in Network: (1x1 Conv)**
* 1x1 convolution is used with same number of channels as the input image.
* Thus it helps in reducing the number of channels of the image.
* The output image is of the same height anad width but its no. of channels = number of filters applied.
* After applying 1x1 conv, ReLU is applied, thus reducing the number of channels to 1 neuron for each filter applied.
![Structure of 1x1 Conv](/Assets/1x1conv.png)

---
# **Inception Network:**
* Multiple combinations of filters and pooling layers are applied of different filter size and the output of each filter operation is stacked as channels.
* Thus the output of each filter needs to be of same height and width, in order to add to the channels. For this reason, **same padding** is applied in each filter convolution.
* This increases the computation.
* To reduce the computational cost, 1x1 convolution can be applied before applying inception, hence reducing the number of channels for performing convolution/pooling on.
* The output from the 1x1 conv is referred to as bottle-neck layer, as the layer has the least number of channels in the network, as the number of channels increases again after applying inception.
* Sometimes the output from some of the layers is directly used to make prediction by passing it to softmax layer along with the output of the FC (Fully-Connected) layer.

Example:
![Inception Example](/Assets/Inception_module.png)

* In an inception network, multiple inception module may be used.
---
# **MobileNet:**
* It is used to do computation in low compute power applications, like microprocessors, mobile phones, etc.
## Depthwise Convolution:
* Individual 2D filters are applied to each channel of the input image.
* The number of filters used = number of channels in input image.
* The number of channels in output image will be same as well.
![Depthwise Conv](/Assets/Depthwise_conv.png
)
## Pointwise Convolution:
* 1x1xnc filter is used with nc' such filters.
* the number of channels in output image will be nc'
---
# MobileNet V1
* It used 13 layers with each layer containing 1 depthwise and 1 pointwise convolution. After this, the output of the 13 layers was pooled and then passed through FC and softmax.

# MobileNet V2:
* It is a combination of ResNet and MobileNet V1.
    ![Structure of MobileNet V2](/Assets/MobileNetV2.png)
## Structure:
![Structure of MobileNet V1 and V2](/Assets/MobileNet.png)

---
># **Object Detection:**
* Detection involves detecting what all objects the image contains.
* Localization involves finding where the objects are located in the image using bounding boxes.
* For this purpose, multiple softmax output labels are used. eg:
    * class labels    
    * Bounding box centre x (bx)
    * Bounding box centre y (by)
    * width of box (bw)
    * height of box (bh)
* the image has top left corner value (0,0) and the bottom right corner is assumed to be (1,1).
* Hence the values of x and y of the bounding box will be between 0 and 1.
* Loss for each output label is calculated as:L = (y1-y1hat)<sup>2</sup> + (y2-y2hat)<sup>2</sup> + (y3-y3hat)<sup>2</sup>....

## Sliding Window Detection:
* A small filter/ window is passed over the image with some stride, and each window is run through the above softmax and has several output labels.
* This is done convolutionally, as shown:
![Convolutional Sliding Windows](/Assets/sliding_windows.png)
* Thus each pixel in the output corresponds to each window.
* The above example shows only 4 output labels, denoted as channels of the output image. There can be more channels/output labels through the softmax layer too.
* This is faster and requires lesser number of computations than using a for loop to loop through each window.
