# Convolutional Neural Network

## Working - Edge Detection

Edge detection helps in detecting objects. Vertical edges, horizontal edges and also edges at a particular angle can be detected using a particular filter. 

![image](https://user-images.githubusercontent.com/111455150/188259813-312a11da-7fd7-46c2-aa00-017b13b8c5e9.png)
![image](https://user-images.githubusercontent.com/111455150/188259825-1db447f1-7b7e-447a-88f9-c4babf01b9b1.png)
![image](https://user-images.githubusercontent.com/111455150/188259834-0942328a-cbfa-4d20-be7b-7a351e3c1c4f.png)
![image](https://user-images.githubusercontent.com/111455150/188259841-b3789a9f-f893-414f-af34-1827b9b76524.png)

## Pooling

![image](https://user-images.githubusercontent.com/111455150/188259849-c6824b57-4dc8-44ca-b586-ad372170a278.png)

# Classic Networks
## LeNet-5

This is an old network. It has approximately 60k parameters. It is a smaller network. Its task was to identify handwritten numbers.

![image](https://user-images.githubusercontent.com/111455150/188259882-91ce3cf0-e8e2-4066-96a6-4fd44e1c8b5c.png)

## AlexNet

This is similar to LeNet-5 bt is bigger. It includes 60M parameters. This uses ReLU function and also uses multiple GPU. Also, this network uses Local response normalization(LRN) that normalizes the values of a certain element along the channels.

![image](https://user-images.githubusercontent.com/111455150/188259899-674a1839-8baa-4694-b7b7-cf5b435a979c.png)
## VGG-16

It uses the same Convolutional and pooling filter in each layer.

CONV = 3x3 filter, s=1, same
MAX POOL= 2x2, s=2
This network uses 138M parameters. 
![image](https://user-images.githubusercontent.com/111455150/188259913-93cc659c-aef6-4166-8c44-0eedb3fa5569.png)

## ResNet

Residual blocks allows different layer to access the activations from a previous layers. When there are multiple layer, theres a chance that the performance of the network will deteroit. Using a residual block maintains the accuracy or might also increase the accuracy. 

![image](https://user-images.githubusercontent.com/111455150/188261011-af02d20e-a2fc-4660-960a-9dfb66fcb00b.png)

Training error in a plain network increases after a certain value bt the training error is low for a ResNet.

![image](https://user-images.githubusercontent.com/111455150/188260022-44c487fa-c651-46a2-ae72-f1d68cdcfd8c.png)

## 1X1 Convolution

![image](https://user-images.githubusercontent.com/111455150/188260045-4955dddf-044e-4744-959c-555409c48f01.png)

## Inception Network

Inception allows multiple filters to work on the input to form different matrices and are later compiled.

![image](https://user-images.githubusercontent.com/111455150/188260070-0b76aadb-e88f-4a55-9b3c-c5fe04412924.png)

## MobileNet

![image](https://user-images.githubusercontent.com/111455150/188260119-b1c4c960-28d7-404f-8b01-e8ad48e1c7ad.png)

This include two steps. Depthwise convolution and point wise convolution. This reduces the computation cost drastically and is more preferable.

### MobileNet V1

This contains 13 layers. Each layer has a depthwise layer and a pointwise layer. Ends with a fully connected layer and softmax.

### MobileNet V2

![image](https://user-images.githubusercontent.com/111455150/188260317-5cc2bcd1-9f14-49fa-8871-c42dadf7eeb2.png)

This also contains an expansion layer. The network works on a large vector which is later reduced which allows the network to be deep but also the computation cost is less.
