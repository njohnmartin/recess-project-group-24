<?php
include_once 'db.php';
include_once 'includes/header.php';

$sql = 'SELECT * 
		FROM failed_jobs';
		
$query = mysqli_query($conn, $sql);

if (!$query) {
	die ('SQL Error: ' . mysqli_error($conn));
}
?>


	<h3>FAILED JOBS LIST AND THE REASON</h3>
	<table border="1"; class="data-table">

		
		<thead>
			<tr>
				<th>id</th>
				<th>userid</th>
				<th>command</th>
				<th>string_task</th>
				<th>reason</th>
				<th>date</th>
				<th>time</th>
			</tr>
		</thead>
		<tbody>
		<?php
	
		while ($clients = mysqli_fetch_array($query))
		{
			


           echo "<tr>";
               echo "<td>".$clients['id']."</td>";
               echo "<td>".$clients['userid']."</td>";
               echo "<td>".$clients['command']."</td>";
               echo  "<td>".$clients['string_task']."</td>";
               echo "<td>".$clients['reason']."</td>";
               echo "<td>".$clients['date']."</td>";
               echo "<td>".$clients['time']."</td>";
           echo "</tr>";

     }


			?>
		</tbody>
		<tfoot>
			
		</tfoot>
	</table>
</body>
</html>