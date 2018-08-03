<?php 

include_once 'db.php';


$file = file(dirname(__FILE__)."/ready_jobs.csv");

if ($file) {
//unlink("ready_jobs.csv ");

     $f = fopen(dirname(__FILE__)."/ready_jobs.csv", "w");
     fclose($f);

	foreach ($file as $line) {
		$csv = str_getcsv($line);
		$userid = $csv[0];
		$task = $csv[1];
		$result = $csv[2];
		$duration = $csv[3];
		$date = date('Y-m-d', strtotime(str_replace("/", "-", $csv[4])));
		$time = $csv[5];

		$query = "INSERT INTO ready_jobsdb SET userid=?, `job_name`=?, result=?, `duration`=?, `date`=?, `time`=?";
		$stmt = mysqli_prepare($conn, $query) or die(mysqli_error($conn));
		mysqli_stmt_bind_param($stmt, "sssdss", $userid, $task, $result, $duration, $date, $time);
		mysqli_stmt_execute($stmt) or die("Error: ". mysqli_error($conn).PHP_EOL.$query.PHP_EOL);

	}


}

$file2 = file(dirname(__FILE__)."/failed_jobs.csv");

if ($file2) {
//unlink("ready_jobs.csv ");

$f = fopen(dirname(__FILE__)."/failed_jobs.csv", "w");
     fclose($f);

	foreach ($file2 as $line) {
		$csv = str_getcsv($line);
		$userid = $csv[0];
		$command = $csv[1];
		$str = $csv[2];
		$reason = $csv[3];
		$date = date('Y-m-d', strtotime(str_replace("/", "-", $csv[4])));
		$time = $csv[5];

		$query = "INSERT INTO failed_jobs SET userid=?, `command`=?, string_task=?, reason=?, `date`=?, `time`=?";
		$stmt = mysqli_prepare($conn, $query) or die(mysqli_error($conn));
		mysqli_stmt_bind_param($stmt, "ssssss", $userid, $command, $str, $reason, $date, $time);
		mysqli_stmt_execute($stmt) or die("Error: ". mysqli_error($conn).PHP_EOL.$query.PHP_EOL);
	}


}



?>