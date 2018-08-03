<?php 

	include_once 'includes/header.php';
 ?>
<table border='1' class="data-table" >
 	<thead>
 	<tr>
 		<th>User ID</th>
 		<th>Job name</th>
 		<th>command</th>
 		<th>Priority</th> 		
 	</tr>
 	</thead>
 	<tbody>
 		<?php
          $csv = array_map('str_getcsv', file("waiting_jobs.csv"));
          foreach ($csv as $key => $job) {
 		  ?>
			<tr>
				
				<td><?php echo $job[1]; ?></td>
				<td><?php echo $job[2]; ?></td>
				<td><?php echo $job[3]; ?></td>
				<td><?php echo $job[5]; ?></td>
			</tr>
 		<?php } ?>
 	</tbody>
 </table>