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

## Intersection Over Union (IOU):
* It is used to calculate the accuracy of the prediction by calculating the ratio of intersection and union of the output bounding box and the ground truth.
* Its value is one for the most accurate prediction.
* Correct threshold can be set to 0.5, so boxes with IOU less than 0.5 are eliminated.

## Non-Max Suppression:
* Multiple grid cells might output that the centre of the car is present in the grid cell, but in reality only 1 gridcell must contain the centre.
* To eliminate this, only the grid cell with the highest probability / output label is considered, and others are suppressed.

## Anchor-Boxes:
* This needs to be used in case of one grid cell containing multiple objects.
* Pre-defined anchor box shapes are made and the output for these boxes are stored with the same grid cell, hence the number of channels are increased to the **(number_of_anchor_boxes * the_number_of_output_labels in each anchor box)**.
* This does not work well in case of more number of objects present than the number of anchor boxes present, or in case multiple objects have the same shape of anchor box.

## YOLO Algorithm:
* First generate grid cells of dimensions eg: 19X19
* Each grid cells gives some output labels. Hence the number of channels in the output will be **output_labels*no_of_anchor_boxes**.
* For each grid cell get 2 bounding boxes.
* Remove all the boxes with low probability.
* Run non-max suppression for each output class.


## Region Based proposal (R-CNN):
* First the input image is put through image segmentation algorithm.
* Then the detection algorithm is performed only on few of the segmented parts of the image, and not all the windows of the image.
* It is relatively slower.

## Semantic Segmentation:
* It detects the edges of the object instead of just bounding boxes.
* Each pixel is clasiified as whether it belongs to object or not.
* For this the output labels matrix should be of the same size as that of the input.
* This is done using Transpose conv after CNN.
![Semantic Segmentation](/Assets/Semantic_segmentation.png)

## Transpose Conv:
* A small input image is output into a larger image using this convolution.
* Stride padding and filter size is first decided.
* The value of each pixel of the input image is multiplied to all the pixels of the filter, and the output is put into the output matrix.
* In case of 0 padded parts of the output matrix, those parts are set to 0.
*  Then the 2nd pixel of the input image is multiplied to the filter and the same process is repeated but with a stride.
* The pixels of the output image overlapping with the previous one are added.
* This is done for all the pixels of the input image.

## U-Net Architecture:
* Skip connections similar to the ones in ResNet is used along with Transpose Conv and CNN.

![U-Net Structure](/Assets/U_Net.png)

* The **input image** is shown as a **sideways view**, hence the number of channels of the image becomes the width of the **input matrix**, the width of the image becomes the number of channels of the input matrix, the height remains same in both.
* Consecutive Conv and ReLU is applied along with MaxPool.
* This reduces the height of the input matrix and increases its width(no of channels of the input image).
* Hence now transpose conv is applied to increase the height again, and along with that, corresponding Shortcut path is added.
* This process is repeated until the output image is of the same size as that of the Input image.
* The number of channels in the output image is equal to the number of classes/segments.
---
# Face Detection:
## One Shot Detection:
* Prediction needs to be made based on only 1 training example.
* This is done by comparing similarity/difference of the test image from different training images.

## Siemese Network:
* First face (x1) is passed through a neural network, let the output vector or encoding be f(x1).
* The second face(x2) is passed through the same network having the same parametrs. Let the output vector/encoding obtained be f(x2).
* The difference between the two image encodings is then defined as d(x1,x2)= |f(x1)-f(x2)|<sup>2</sup>
* The parameters are learned such that the d for 2 images of the same person is minimum.
* If d between 2 images is very large then they are different people.

## Triplet Loss:
* 3 images are compared at once.
    * 1st is Anchor Image (A)
    * 2nd is Positive Image (image of the same person as that of anchor image) (P)
    * 3rd is Negative Image (image of a different person than the other 2) (N)
* The d between A and P should be minimum and the d between A and N should be maximum.
    ### d(A,P)<=d(A,N) or d(A,P)-d(A,N) + alpha<=0
* Here alpha const is called margin, and is introduced to prevent the trivial solution of all encodings of A,P and N to be 0.
* Hence the Triplet Loss L(A,P,N) is defined as: 
## L(A,P,N) = max(d(A,P)-d(A,N) + alpha , 0)
* This is so that if the left part is negative, the loss is set to 0 .

## Cost Function:
* It is the sum of all the losses of triplets over all the training example.
* The training triplets cannot be passed randomly as chances are that A and P randomly chosen are very differrnt from A and N.

## Alternative to triplet loss:
* It can also be trained using binary classification.
* 2 images are passed through the neural network and the encoding (output vectors) are calculated.
* The elemental differences between the 2 encodings can be found and their product with weight can be passed through an activation function along with margin.
* the output will be 0 if they are same, and 1 if they are different.

For better efficiency, the encoding for the different faces are pre-computed and hence do not need to be passed through the neural network, every time a person needs to be checked.

# Neural Style Tranfer:
* The initial layers of a ConvNet detect small features of an image, eg: vertical edges, etc.
* The final or layers in the later part of the network detect broader parts of the image, eg: faces, etc.

## Cost Function in NST:
* The cost of the genererated image(G) consists of 2 parts: one from the content image and one from the style image.
* J(G) = alpha X J(G,C) + beta X J(G,S)
* First the output image(G) is generated randomly and then the pixel values are tweaked using gradient descent to find the desired output.
* J(G,S) is calculated as the correlation between diffrent channels of the activations of a specific layer in the generated image and the style image.
This is found by passing both the generated and style images through the same network and measuring the correlation between the activations of the diffrent channels of a particular layer in both the images.
it is given by the formula:
![Style Cost Function](/Assets/Style_cost_function.png)

* The Content Cost Function is calculated as:
![Content Cost Function](/Assets/Content_cost_function.png)