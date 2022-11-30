import numpy as np
import pandas as pd
import tensorflow
import keras
from keras import layers

# Input files:
trainfile = "nn-train.csv"
testfile = "nn-test.csv"

# Output files:
checkpoint_path = "neuralnetweights.ckpt"
trainedmodel_path = "model.h5"
weightcsv = "neuralnetweights.csv"

data_train = pd.read_csv(trainfile)
data_test = pd.read_csv(testfile)

train_inputs = data_train.values[:,1:4] / 4096
train_outputs = data_train.values[:,4:10]

test_inputs = data_test.values[:,1:4] / 4096
test_outputs = data_test.values[:,4:10]

# Create a callback that saves the model's weights
save_callback = keras.callbacks.ModelCheckpoint(filepath=checkpoint_path,
                                                save_weights_only=True,
                                                verbose=1)


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
model.fit(train_inputs,
          train_outputs,
          epochs=500,                   # 500 epochs seems to reliably reach accuracy 1.0
          callbacks=[])    # Function to use when saving model weights

print("\nEvaluating algorithm...")
test_loss, test_accuracy = model.evaluate(test_inputs, test_outputs)

print("\nTest Accuracy:", test_accuracy, "\nTest Loss:", test_loss)

print("\nTesting prediction...")
predictions = model.predict(test_inputs)
print("XYZ:", test_inputs[0])
print("Prediction:", class_names[np.argmax(predictions[0])])

print("\nSaving model as H5...")
model.save(trainedmodel_path)

weights = []
print("\nPrinting weights...")
for layer in model.layers:
    weights = np.append(weights, layer.get_weights(), axis=0)
    print(layer.get_weights())
print("Weights:")
for each in weights:    
    print(each)
#TODO parse weights to csv
