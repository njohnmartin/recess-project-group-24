<?php
include_once 'db.php';
include_once 'includes/header.php';

$sql = 'SELECT * 
		FROM ready_jobsdb';
		
$query = mysqli_query($conn, $sql);

if (!$query) {
	die ('SQL Error: ' . mysqli_error($conn));
}
?>



	<h1>Ready_jobs table</h1>
	<table border="1"; class="data-table">

		
		<thead>
			<tr>
				<th>JobId</th>
				<th>UserID</th>
				<th>Job_Name</th>
				<th>Result</th>
				<th>Duration</th>
				<th>Time</th>
				<th>Date</th>
			</tr>
		</thead>
		<tbody>
		<?php
	
		while ($clients = mysqli_fetch_array($query))
		{
			


           echo "<tr>";
               echo "<td>".$clients['jobid']."</td>";
               echo "<td>".$clients['userid']."</td>";
               echo "<td>".$clients['job_name']."</td>";
               echo "<td>".$clients['result']."</td>";
               echo "<td>".$clients['duration']."</td>";
               echo "<td>".$clients['time']."</td>";
               echo "<td>".$clients['date']."</td>";
           echo "</tr>";

     }


			?>
		</tbody>
		<tfoot>
			
		</tfoot>
	</table>
</body>
</html>