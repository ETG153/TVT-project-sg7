import numpy as np
import pandas as pd
import seaborn as sns

#inputfilepath = "arduino/Kmeans-test-results.csv"
inputfilepath = "arduino/NN-test-results.csv"
#outputfilepath = "documentation/kmeans-confusionmatrix-results.png"
outputfilepath = "documentation/nn-confusionmatrix-results.png"

results = pd.read_csv(inputfilepath)
#print(results)

confusionmatrix = pd.crosstab(results["Estimate"], results["Answer"], rownames=["Actual"], colnames=["Estimate"])
matrixrowsums = confusionmatrix.sum(axis="columns")
normalizedmatrix = confusionmatrix.divide(matrixrowsums, axis="index")
#print(confusionmatrix)
#print(matrixrowsums)
#print(normalizedmatrix)

rowindices = ["Neg Z", "Neg Y", "Neg X", "Pos Z", "Pos Y","Pos X"]
colindices = rowindices[::-1]

sns.heatmap(normalizedmatrix, cmap="RdYlGn", linewidths=0.5, annot=True).get_figure().savefig(outputfilepath)
