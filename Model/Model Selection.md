# Model Selection

After selecting and making a suitable dataset, the next task was to select a model. We will use a pre trained model for our work. This is called Tranfer Learning.
There were a few options that we were considering from the start. We wanted a model with less number of prameters but high accuracy. Few networks that we were considering were:
1. ResNet 50
2. MobileNetv2
3. EfficientNet Lite 0-4

We read a few articles to compare the working of some of these networks after being trained. 

## ResNet 50
![image](https://miro.medium.com/max/1400/0*tH9evuOFqk8F41FG.png)

ResNet-50 is a convolutional neural network that is 50 layers deep. You can load a pretrained version of the network trained on more than a million images from the ImageNet database.
ResNet-50 has more number of parameters to be used so it is obvious that it will show better performance as compared to other networks but due to a large number of parameters, the model size is large. As we will have to run our model on ESP32, ResNet-50 is not suitable for us.

## MobileNetV2
![image](https://user-images.githubusercontent.com/114467415/193272087-c540a9d3-1248-41c9-b498-7301dc6079ba.png)

Next, we considered using MobileNetV2. MobileNetV2 is a convolutional neural network that is 53 layers deep. You can load a pretrained version of the network trained on more than a million images from the ImageNet database. MobileNetV2 is very similar to the original MobileNet, except that it uses inverted residual blocks with bottlenecking features. Its accuracy and model size are less than EfficientNet.

## EfficientNetLite0

We then considered using EfficientNetLite0. It is better than other EfficientNet networks due to the following reasons:
- Removed squeeze-and-excitation networks since they are not well supported
- Replaced all swish activations with RELU6, which significantly improved the quality of post-training quantization
- Fixed the stem and head while scaling models up to reduce the size and computations of scaled models

## Comparision between the models
![image](https://user-images.githubusercontent.com/111455150/189773871-8cc41a2f-5678-494c-ad98-7e5b44138412.png)

After analysing the performance and model size of various models, we decided to use EfficientNetLite0. Even though the size of EfficientNetLite0 model was larger than MobileNetV2, accuracy was our primary concern. 

## Using MobileNetV2

After using EfficientNetLite0, our model size was around 41Mb even after quantization. We could not prune our model as pruning is not supported in the Tensorflow Lite API. We tried looking for some alternatives but at the end, decided to switch to MobileNetV2 as the model size is smaller than EfficientNetLite0 and we can prune our MobileNetV2 model. 
We also pruned and quantized our model to reduce the size. For pruning, we used the prune_low_magnitude function. This function wraps a tf.keras model or layer with pruning functionality which sparsifies the layer's weights during training. For used Dynamic range quantization method. This type of quantization, statically quantizes only the weights from floating point to integer at conversion time, which provides 8-bits of precision. After pruning and quantizing our MobileNetV2 model, the model size was reduced to around 16Mb. We also tried other quantization and pruning methods and compared the performance of our model.

<img width="517" alt="image" src="https://user-images.githubusercontent.com/114467415/194197146-4716c5d3-c2d8-440e-81b2-291a84a70902.png">


Even after this, we could not use this model as we have to run our model on ESP32. In the end, we used the human_face_detection model provided by [Espressif](https://github.com/espressif/esp-who/tree/master/examples/human_face_detection) for ESP32 models. 

## Using model_data.cc

model_data.cc is the c array of our model. Our model was made using python which is supported on ESP32. In order to run our model on ESP32, we had to convert our model to a C array. It can be run on devices the support C. The user will have to write an inference program to get live data from the source and use the model to make predictions on the data provided.


### Reference:

[Comparison between MobileNet and EfficientNet](https://towardsdatascience.com/bye-bye-mobilenet-hello-efficientnet-9b8ec2cc1a9c)

[Comparison between MobileNet and ResNet](https://analyticsindiamag.com/mobilenet-vs-resnet50-two-cnn-transfer-learning-light-frameworks/)

[Performance of different EfficientNet models](https://paperswithcode.com/model/tf-efficientnet-lite?variant=tf-efficientnet-lite3)
