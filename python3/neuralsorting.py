import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import tensorflow
import keras
from keras import layers

trainfile = "nn-train.csv"
testfile = "nn-test.csv"

data_train = pd.read_csv(trainfile)
data_test = pd.read_csv(testfile)

train_inputs = data_train.values[:,1:4] / 4096
train_outputs = data_train.values[:,4:10]

test_inputs = data_test.values[:,1:4] / 4096
test_outputs = data_test.values[:,4:10]

print(test_inputs)

num_classes  =  6
class_names = ["-X", "-Y", "-Z", "+X", "+Y", "+Z"]
input_shape  =  3

model  =  keras.Sequential([
    keras.Input(shape=input_shape),
    layers.Dense(6,  activation='relu',name='hidden1'),
    layers.Dense(12,  activation='relu',name='hidden2'),
    layers.Dense(num_classes,  activation="softmax",name  =  'output'),
])

model.summary()

model.compile(optimizer="adam",loss=keras.losses.CategoricalCrossentropy() , metrics="accuracy")

print("Starting training...")
model.fit(train_inputs, train_outputs, epochs=500)

print("\nEvaluating algorithm...")
test_loss, test_accuracy = model.evaluate(test_inputs, test_outputs)

print("\nTest Accuracy:", test_accuracy, "\nTest Loss:", test_loss)
