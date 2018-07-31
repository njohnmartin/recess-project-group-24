<?php session_start(); ?>
<!DOCTYPE html>
<html lang="en">
<head>
	<meta charset="UTF-8">
	<title>Login - String Task Server</title>
	<link rel="stylesheet" href="styles.css">
</head>
<body>
	<div class="container">
		<div class="row">
			<div class="title">
				<h2>String Task Server</h2>
			</div>
		</div>
		<div class="row">
			<?php if (isset($_SESSION['errors'])) {
				echo "<p class='text-error'>".$_SESSION['errors']."</p>";
				unset($_SESSION['errors']);
			} ?>
			<form action="validate.php" method="post" class="login-form">
				<fieldset style="border-width: 1px; border-color: #eee;">
					<legend align="center"><h3>Administrator Login</h3></legend>
					<div class="form-input">
						<label for="username">Username: </label>
						<input type="text" name="username" id="username">
					</div>
					<div class="form-input">
						<label for="password">Password: </label>
						<input type="password" name="password" id="password">
					</div>
					<div class="form-submit">
						<input type="submit" value="Login">
					</div>
				</fieldset>
			</form>
		</div>
	</div>
</body>
</html>