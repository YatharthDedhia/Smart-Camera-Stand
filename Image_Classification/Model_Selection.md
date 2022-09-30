# Model Selection

After selecting and making a suitable dataset, the next step is the selection of model for it training on our prepared dataset. 

We use the concept of Transfer-Learning to train our model by freezing the layers of a pre-trained model.

This is done to reduce the time required to train a whole model from scratch using randomly initialised weights, and to improve the accuracy of our model too.

We considered various pre-trained models for out model. An ideal model should contain less number of parameters but have high accuracy. 

Few networks that we were considering were:
1. ResNet 50
2. MobileNetV2
3. EfficientNet Lite 0-4

ResNet-50 has more number of parameters to be used so it is obvious that it will show better performance as compared to the MobileNet 
but we can noticed that the MobileNet model became more accurate on increasing the number of epochs.

>## ResNet 50:
**Advantages:**

**Disadvantages:**
* model size after training is very large
![ResNet 50](https://user-images.githubusercontent.com/111455150/189772554-8e8b9561-6dc5-4e05-838c-cb2ab43931c5.png)

>## MobileNet:
**Advantages:**

**Disadvantages:**
![MobileNet](https://user-images.githubusercontent.com/111455150/189772608-43faf67c-a9d5-4790-ba52-787997728388.png)

>## EfficientNetLite:
**Advantages:**

**Disadvantages:**
<!-- Insert image -->
On comparing the accuracy and model size of MobileNetv2 and EfficientNet Lite 0-4, we decided to use EfficientNet Lite 0 as the model size for EfficientNet Lite 1-4 increases drastically.

In comparision to MobileNetV2, we found out EffNet Lite 0 is a lot more accurate. Even though the model size was was also increased, which was not very significant.

## Comparision between the models
![image](https://user-images.githubusercontent.com/111455150/189773871-8cc41a2f-5678-494c-ad98-7e5b44138412.png)

Hence as a conclusion from the research conducted, we decided to go forth with using EfficientNetLite0.


References:

[MobileNet vs EfficientNet](https://towardsdatascience.com/bye-bye-mobilenet-hello-efficientnet-9b8ec2cc1a9c)

[MobileNet vs ResNet50](https://analyticsindiamag.com/mobilenet-vs-resnet50-two-cnn-transfer-learning-light-frameworks/)

[EfficientNetLite](https://paperswithcode.com/model/tf-efficientnet-lite?variant=tf-efficientnet-lite3)
