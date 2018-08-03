<?php session_start();

include_once('db.php');

$errors = "Invalid username and password combination";

if (isset($_POST['username'], $_POST['password'])) {
	$username = $_POST['username'];
	$password = $_POST['password'];

	$query = "SELECT * FROM admins WHERE username=?";
	$stmt = mysqli_prepare($conn, $query) or die(mysqli_error($conn));
	mysqli_stmt_bind_param($stmt, "s", $username);
	mysqli_stmt_execute($stmt);

	$result = mysqli_stmt_get_result($stmt);

	$row = mysqli_fetch_assoc($result);

	if (password_verify($password,$row['password'])) {
		$_SESSION['userid'] = $row['id'];
		header("location:index.php");
	}else{
		echo "Wrong password or username";
echo $username. ' '. $password;
	}

}



