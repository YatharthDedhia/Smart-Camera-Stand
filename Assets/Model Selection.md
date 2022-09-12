# Model Selection

After selecting and making a suitable, the next task was to select the model that we will be using. We will be reusing a pre trained model for our work. This is called Tranfer Learning.
There were a few options that we were considering from the start. We wanted a model with less number of prameters but high accuracy. Few networks that we were considering were:
1. ResNet 50
2. MobileNetv2
3. EfficientNet Lite 0-4

We read a few articles to compare the working of some of these networks after being trained. We decided to not used ResNet 50 as the model size after training was quite large as compared to other models.
ResNet-50 has more number of parameters to be used so it is obvious that it will show better performance as compared to the MobileNet 
but we can noticed that the MobileNet model became more accurate on increasing the number of epochs.

#### ResNet 50
![image](https://user-images.githubusercontent.com/111455150/189772554-8e8b9561-6dc5-4e05-838c-cb2ab43931c5.png)

#### MobileNet
![image](https://user-images.githubusercontent.com/111455150/189772608-43faf67c-a9d5-4790-ba52-787997728388.png)

Now, we compared the accuracy and model size of MobileNetv2 and EfficientNet Lite 0-4. We decided to not used EfficientNet Lite 1-4 as the model size increases drastically.
On comparing MobileNetv2 and EffNet Lite 0, we found out EffNet Lite 0 is a lot more accurate than MobileNetv2. Even though the model size was was also increased, that was somthing the we could deal with.

#### Comparision between the models
![image](https://user-images.githubusercontent.com/111455150/189773871-8cc41a2f-5678-494c-ad98-7e5b44138412.png)

Based on what we understood after examining at the performance of each model, we decided to used EfficientNet Lite 0 for our project.





Reference:

[Link](https://towardsdatascience.com/bye-bye-mobilenet-hello-efficientnet-9b8ec2cc1a9c)

[Link](https://analyticsindiamag.com/mobilenet-vs-resnet50-two-cnn-transfer-learning-light-frameworks/)

[Link](https://paperswithcode.com/model/tf-efficientnet-lite?variant=tf-efficientnet-lite3)
