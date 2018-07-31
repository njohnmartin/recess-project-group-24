<?php 

$dbuser = "root";
$dbpass = "Sinner@256";
$dbhost = "localhost";
$database = "recess";

$conn = mysqli_connect($dbhost, $dbuser, $dbpass, $database);

if (mysqli_connect_errno($conn)) {
	echo "Failed to connect to database: " . mysqli_connect_error();
}

