<?php 

include_once 'db.php';

$file = file("ready_jobs.csv");

if ($file) {
//unlink("ready_jobs.csv ");



	foreach ($file as $line) {
		$csv = str_getcsv($line);
		$userid = $csv[0];
		$task = $csv[1];
		$duration = $csv[3];
		$date = date('Y-m-d', strtotime(str_replace("/", "-", $csv[4])));
		$time = $csv[5];

		$query = "INSERT INTO ready_jobsdb SET userid=?, `job_name`=?, `duration`=?, `date`=?, `time`=?";
		$stmt = mysqli_prepare($conn, $query) or die(mysqli_error($conn));
		mysqli_stmt_bind_param($stmt, "ssdss", $userid, $task, $duration, $date, $time);
		mysqli_stmt_execute($stmt) or die("Error: ". mysqli_error($conn).PHP_EOL.$query.PHP_EOL);
	}


}

$file2 = file("failed_jobs.csv");

if ($file2) {
//unlink("ready_jobs.csv ");



	foreach ($file2 as $line) {
		$csv = str_getcsv($line);
		$userid = $csv[0];
		$command = $csv[1];
		$reason = $csv[2];
		$date = date('Y-m-d', strtotime(str_replace("/", "-", $csv[4])));
		$time = $csv[5];

		$query = "INSERT INTO failed_jobs SET userid=?, `command`=?, reason=?, `date`=?, `time`=?";
		$stmt = mysqli_prepare($conn, $query) or die(mysqli_error($conn));
		mysqli_stmt_bind_param($stmt, "sssss", $userid, $command, $reason, $date, $time);
		mysqli_stmt_execute($stmt) or die("Error: ". mysqli_error($conn).PHP_EOL.$query.PHP_EOL);
	}


}