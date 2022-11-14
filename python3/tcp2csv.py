import mysql.connector as db
import csv

loginfile = "login.txt"
outputfile = "data.csv"

# Read login info from file
file = open(loginfile, 'r')
_host = file.readline()
_user = file.readline()
_passwd = file.readline()
_database = file.readline()
file.close();

# Trim trailing newline
_host = _host[:(len(_host) - 1)]
_user = _user[:(len(_user) - 1)]
_passwd = _passwd[:(len(_passwd) - 1)]
_database = _database[:(len(_database) - 1)]

# Create database connection
dataBase = db.connect(
  host = _host,
  user = _user,
  passwd = _passwd,
  database = _database
)

# Create and execute DB query
dbCursor = dataBase.cursor()
dbCursor.execute("SELECT * FROM rawdata WHERE sensorvalue_e IN(88,89,90,120,121,122) AND groupid = 56")
results = dbCursor.fetchall()

# Output query results to .csv with titles
with open(outputfile, 'w') as fileout:
  writer = csv.writer(fileout)
  writer.writerow(["id","timestamp","groupid","from_mac","to_mac","accelX","accelY","accelZ","messageid","flag","extra"])
  writer.writerows(results)
  
# Disconnect from the server
dataBase.close()