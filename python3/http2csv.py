import requests
import csv

# Get database contents from server
data = requests.get("http://172.20.241.9/luedataa_kannasta_groupid_csv.php?groupid=56")

# Use existing line terminator to split text to list
lines = data.text.split("\n")
outlist = []

# Split each row to values
for each in lines:
    each = each.split(";")
    templist = []
    for each1 in each:
        templist.append(each1)
    outlist.append(templist)

# Write result to .csv file
with open("output.csv", "w") as outfile:
    writer = csv.writer(outfile, lineterminator="\n")
    writer.writerows(outlist)