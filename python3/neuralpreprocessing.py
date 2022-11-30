'''
Tässä tehdään koneoppimiskurssin kotitehtävän 5 mukaiset
datan käsittelyt, eli luetaan kiihtyvyysanturidata ja labelit
csv tiedostosta. Suodatetaan liian suuret arvot pois, muokataan
labeleista numeroarvot ja jaetaan näin saatu data opetus ja
testi dataan. Tämän jälkeen datalla voidaan opettaa esim neuroverkko
'''

import sklearn # This is anyway how package is imported
import numpy as np
import matplotlib.pyplot as plt
import pandas as pd
import time
import tensorflow
import keras
from sklearn.model_selection import train_test_split

trainfile = "nn-train.csv"
testfile = "nn-test.csv"

df = pd.read_csv('data.csv',
                  sep=",",
                  header=None)
df = df[1:]                                    # poistetaan eka rivi dataframesta


print("Row count: ",len(df.index))
datain = np.zeros((len(df.index),4),dtype=float)              # Tehdään tilaa x, y, z ja vielä sille labelille, joka on muutettu numeroksi.
                                                # tämä siksi, että suodatus tapahtuu kätevästi myös tuon labelin osalta
datain[:,0] = df[5].to_numpy()
datain[:,1] = df[6].to_numpy()
datain[:,2] = df[7].to_numpy()
datain[:,3] = df[9].astype('category').cat.codes.to_numpy()    

data = datain.astype(int)

print("numpy array = ", data[50:])

#tehdään suodatin
suodatin = np.zeros((len(df.index),4),dtype=bool) 
for i in range(len(df.index)):
    if( (data[i,0]<4069) and (data[i,1]<4096) and (data[i,2]<4096) ):
        suodatin[i] = [True,True,True,True]
    else:
        suodatin[i] = [False,False,False,False]

suodatettu = data[suodatin]
riveja = int(len(suodatettu)/4)
suodatettu = suodatettu.reshape(riveja,4)

print("suodatin = ", suodatin[50:])
print("suodatettu = ",suodatettu[40:])

inputs = suodatettu[:,0:3]                 # kiihtyvyysanturidata x,y,z
answers = suodatettu[:,3]                  # tunnetut labelit
num_classes = 6
answers = keras.utils.to_categorical(answers, num_classes)

inputs_train, inputs_test, answers_train, answers_test = train_test_split(inputs, answers,test_size=0.2)
print(inputs_train.shape)
print(inputs_test.shape)

data_train = pd.DataFrame(np.hstack((inputs_train.astype(int), answers_train.astype(int))))
data_test = pd.DataFrame(np.hstack((inputs_test.astype(int), answers_test.astype(int))))

data_train.to_csv(trainfile)
data_test.to_csv(testfile)
