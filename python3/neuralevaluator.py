import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import tensorflow
import keras
from keras import layers

checkpoint_path = "neuralnetweights.ckpt"
trainfile = "nn-train.csv"
testfile = "nn-test.csv"

data_train = pd.read_csv(trainfile)
data_test = pd.read_csv(testfile)

test_inputs = data_test.values[:,1:4] / 4096
test_outputs = data_test.values[:,4:10]

num_classes  =  6
class_names = ["-X", "-Y", "-Z", "+X", "+Y", "+Z"]
input_shape  =  3

model  =  keras.Sequential([
    keras.Input(shape=input_shape),
    layers.Dense(6,  activation='relu',name='hidden1'),
    layers.Dense(12,  activation='relu',name='hidden2'),
    layers.Dense(num_classes,  activation="softmax",name  =  'output'),
])

model.compile(optimizer="adam",loss=keras.losses.CategoricalCrossentropy() , metrics="accuracy")

print("\nEvaluating untrained algorithm...")
test_loss, test_accuracy = model.evaluate(test_inputs, test_outputs)

model.load_weights(checkpoint_path)

print("\nEvaluating restored algorithm...")
test_loss, test_accuracy = model.evaluate(test_inputs, test_outputs)
