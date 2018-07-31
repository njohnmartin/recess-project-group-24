<?php session_start();

include_once('db.php');

$errors = "All fields are required";

if (isset($_POST['username'], $_POST['password'])) {
	$username = $_POST['username'];
	$password = password_hash($_POST['password'], PASSWORD_DEFAULT);

	$query = "INSERT INTO admins SET username=?, password=?";
	$stmt = mysqli_prepare($conn, $query) or die(mysqli_error($conn));
	mysqli_stmt_bind_param($stmt, "ss", $username, $password);
	mysqli_stmt_execute($stmt);

	echo "<h2>User: $username has successfully been created</h2>";


}
