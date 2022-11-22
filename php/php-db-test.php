<?php
$loginfile = "login.ro";
$dbaddr = "172.20.241.9";
$dbname = "measurements";
$username = "dbaccess_ro";
$password = "vsdjkvwselkvwe234wv234vsdfas";
$sqlquery = "SELECT * FROM rawdata WHERE sensorvalue_e IN(88,89,90,120,121,122) AND groupid = 5;";

echo "Reading login details...\n";
$file = fopen($loginfile, "r") or die("Could not open ".$loginfile);
$login = fgets($file);
//list($username, $password) = explode(",", $login, 3);
fclose($file);

echo "Connecting to database ".$dbname." at ".$dbaddr." as ".$username." with password ".$password."\n";
$connection = new mysqli($dbaddr, $username, $password, $dbname);
if($connection->connect_error){
	die("Connection failed: ".$connection->connect_error);
}

$result = $connection->query($sqlquery);
if ($result->num_rows > 0) {
	// output data of each row
	while($row = $result->fetch_assoc()) {
		//echo var_dump($row);
		//echo "ID: ".$row["id"]."\t\tTimestamp: ".$row["timestamp"]."\t\tGroup ID: ".$row["groupid"]."\t\tFlag: ".chr($row["sensorvalue_e"])."\t\tX: ".intval($row["sensorvalue_a"])."\t\tY: ".intval($row["sensorvalue_b"])."\t\tZ: ".intval($row["sensorvalue_c"])."\n";
		printf("ID: %d | Timestamp: %s | Group ID: %d | Flag: %s | X: %-6.0f | Y: %-6.0f | Z: %-6.0f\n", $row["id"], $row["timestamp"], $row["groupid"], chr($row["sensorvalue_e"]), intval($row["sensorvalue_a"]), intval($row["sensorvalue_b"]), intval($row["sensorvalue_c"]));
	}
} else {
 	echo "No results\n";
}
$connection->close();
?>
