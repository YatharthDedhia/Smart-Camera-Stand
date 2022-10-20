# Preparing the Dataset For Neural Network

* The dataset we are using for this model is [CIFAR-100](https://www.kaggle.com/datasets/fedesoriano/cifar100).
* This dataset contains 32x32 images which are divided into 100 classes with 600 images per class.
* Each class is under a superclass which is a superset of a 5 classes.
* For our use-case, we only need to train the model for the presence of a person, we only need 2 classes for binary classification.
* Hence all the images from the superclass 'person' is labelled as 1, hence it contains 3000 images.
* Initially, we labelled all the remaining 57000 images as 0 or 'not-person', which cause the model to overfit and give false accuracy of 95% as it was trained more towards 'not-people' class.
* We rectified this by taking equal number of images for both 1 and 0 class.
* This is done by taking 31 images from each class, hence we got 2945 images for the 'not-people' class.
* These images were then split into 80-20% for training and testing.

### Advantages:
* It contains a very large number of images to train the network on.
* The images are 32x32 which is reduces the size of the dataset.
* The images are well labelled and uniform with a large variety of images.

### Disadvantages:
* The resolution of the images is quite low.

## Class structure:
![100 Classes](/Assets/Classes_cifar_100.png)

## Superclass structure:
![Superclasses](/Assets/superclasses.png)