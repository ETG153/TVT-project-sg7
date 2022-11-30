import matplotlib.pyplot as plt
import numpy as np
import pandas as pd
import tensorflow
import keras
from keras import layers

trainedmodel_path = "model.h5"
trainfile = "nn-train.csv"
testfile = "nn-test.csv"

weightcsv = "neuralnetweights.csv"

data_train = pd.read_csv(trainfile)
data_test = pd.read_csv(testfile)

test_inputs = data_test.values[:,1:4] / 4096
test_outputs = data_test.values[:,4:10]

num_classes  =  6
class_names = ["-X", "-Y", "-Z", "+X", "+Y", "+Z"]
input_shape  =  3

model = keras.models.load_model(trainedmodel_path)

print("\nEvaluating restored algorithm...")
model.evaluate(test_inputs, test_outputs)

print("\nPrinting weights to .csv file...")
weights = []
for layer in model.layers:
    weights = np.append(weights, layer.get_weights(), axis=0)

weightdf = pd.DataFrame(np.full(shape=(1,12), fill_value=np.nan), columns=["node0", "node1", "node2", "node3", "node4", "node5", "node6", "node7", "node8", "node9", "node10", "node11"])

print("\n", len(weights[4]))
print(weights[4])

weightdf.loc[0,"node0":"node5"] = weights[0][0]
weightdf.loc[1,"node0":"node5"] = weights[0][1]
weightdf.loc[2,"node0":"node5"] = weights[0][2]
weightdf.loc[3,"node0":"node5"] = weights[1][0]

weightdf.loc[4,"node0":"node11"] = weights[2][0]
weightdf.loc[5,"node0":"node11"] = weights[2][1]
weightdf.loc[6,"node0":"node11"] = weights[2][2]
weightdf.loc[7,"node0":"node11"] = weights[2][3]
weightdf.loc[8,"node0":"node11"] = weights[2][4]
weightdf.loc[9,"node0":"node11"] = weights[2][5]
weightdf.loc[10,"node0":"node11"] = weights[3][0]

weightdf.loc[11,"node0":"node5"] = weights[4][0]
weightdf.loc[12,"node0":"node5"] = weights[4][1]
weightdf.loc[13,"node0":"node5"] = weights[4][2]
weightdf.loc[14,"node0":"node5"] = weights[4][3]
weightdf.loc[15,"node0":"node5"] = weights[4][4]
weightdf.loc[16,"node0":"node5"] = weights[4][5]
weightdf.loc[17,"node0":"node5"] = weights[4][6]
weightdf.loc[18,"node0":"node5"] = weights[4][7]
weightdf.loc[19,"node0":"node5"] = weights[4][8]
weightdf.loc[20,"node0":"node5"] = weights[4][9]
weightdf.loc[21,"node0":"node5"] = weights[4][10]
weightdf.loc[22,"node0":"node5"] = weights[4][11]
weightdf.loc[23,"node0":"node5"] = weights[5][0]

print("\nDataframe:")
print(weightdf)

weightdf.to_csv(weightcsv)
