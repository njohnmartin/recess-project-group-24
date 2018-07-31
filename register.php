<?php session_start(); ?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Register - String Task Server</title>
	<link rel="stylesheet" href="styles.css">
</head>
<body style="background-image: url(uni2.jpg)">
	<div class="container">
		<div class="row">
			<div class="title">
				<h2>String Task Server</h2>
			</div>
		</div>
		<div class="row">
			<form action="create_user.php" method="post" class="login-form">
				<fieldset style="border-width: 1px; border-color: #eee;">
					<legend align="center"><h3>Registration</h3></legend>
					<div class="form-input">
						<label for="firstname">Firstname: </label>
						<input type="text" name="firstname" id="firstname">
					</div>
					<div class="form-input">
						<label for="lastname">Lastname: </label>
						<input type="text" name="lastname" id="lastname">
					</div>
					<div class="form-input">
						<label for="email">Email: </label>
						<input type="email" name="email" id="email">
					</div>
					<div class="form-input">
						<label for="username">Username: </label>
						<input type="text" name="username" id="username">
					</div>
					<div class="form-input">
						<label for="password">Password: </label>
						<input type="password" name="password" id="password">
					</div>
					<div class="form-submit">
						<input type="submit" value="Register">
					</div>
				</fieldset>
			</form>
		</div>
	</div>
</body>
</html>