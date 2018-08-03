<?php
include_once 'includes/header.php';
include_once 'db.php';
?>

<style>
  .dname {
    font-weight: bold;
  }
</style>

  <!-- Header -->
  <header class="w3-container" style="padding-top:22px">
    <h5><b><i class="fa fa-dashboard"></i>
      <b><h1 style="text-align: center; color: purple; font-family: algerian"> WELCOME TO THE ADMIN </h1></b><br><b><h1 style="text-align: center; color: purple; font-family: algerian">WEB INTERFACE</h1></b>
    </p><br><br>
    </h1></b></h5>
  </header>






    


    <!-- CALCULATING THE SUCCESS RATE  AND FAILURE RATE -->
<?php
$query = <<<SQL
  SELECT al.userid,
    ( SELECT COUNT(*) FROM ready_jobsdb WHERE userid=al.userid ) as success_count,
    ( SELECT COUNT(*) FROM failed_jobs WHERE userid=al.userid ) as failure_count
  FROM (
    SELECT DISTINCT(userid) FROM ready_jobsdb
    UNION
    SELECT DISTINCT(userid) FROM failed_jobs
    ) AS al
    GROUP BY al.userid
SQL;


$maxfail;
$maxsuccess;

$result = mysqli_query($conn, $query) or die(mysqli_error($conn));

while ($row = mysqli_fetch_assoc($result)) {

  
  $total = $row['success_count'] + $row['failure_count'];
  $fail = ($row['failure_count'] * 100)/$total;
  $success = ($row['success_count'] * 100)/$total;

  if (!isset($maxfail) || $fail > $maxfail['count'])
  {
    $maxfail['count'] = $fail;
    $maxfail['obj'] = $row;
  }
  if (!isset($maxsuccess) || $success > $maxsuccess['count'])
  {
    $maxsuccess['count'] = $success;
    $maxsuccess['obj'] = $row;
  }
}


             

?>






  <hr>

  <!-- CALCULATING AVERAGE PROCESSING RATE -->

        <p>The average processing rate is: 
<?php
include_once 'db.php';

$sql2="SELECT COUNT(userid) as av_rate FROM ready_jobsdb";

$result = mysqli_query($conn, $sql2);
$values= mysqli_fetch_assoc($result);
$num = $values['av_rate'];


$sql= "SELECT duration  FROM ready_jobsdb";
$result1 = mysqli_query($conn, $sql);
$sum =0;
while($row = mysqli_fetch_array($result1)){

  $sum = $sum + $row['duration'];




}

$avg = $sum/($num*60);

echo "<a style='color:blue;'>".$avg."\tjob-1"."</a>";



  
?>
        </p>









        

  <hr>

  <div class="w3-container" >
    <h5>General Stats</h5>
    <p>The student's ID with the Highest percentage success rate: <span class="dname"> <?php echo $maxsuccess['obj']['userid'] ?></span></p>
    <div class="w3-grey">

      <div class="w3-container w3-center w3-padding w3-green" style="width:<?php echo $maxsuccess['count'] ?>%"><?php echo $maxsuccess['count'] ?>%</div>
    </div>

    <p>The student's ID with highest percentage failure rate: <span class="dname"> <?php echo $maxfail['obj']['userid'] ?></span></p>
    <div class="w3-grey">
      <div class="w3-container w3-center w3-padding w3-orange" style="width:<?php echo $maxfail['count'] ?>%"><?php echo $maxfail['count'] ?>%</div>
    </div>



  <div class="w3-panel">
    <div class="w3-row-padding" style="margin:0 -16px">
           <div class="w3-twothird">



        </div>


    </div>
  </div>






  <!-- End page content -->
</div>

<script>
// Get the Sidebar
var mySidebar = document.getElementById("mySidebar");
// Get the DIV with overlay effect
var overlayBg = document.getElementById("myOverlay");
// Toggle between showing and hiding the sidebar, and add overlay effect
function w3_open() {
    if (mySidebar.style.display === 'block') {
        mySidebar.style.display = 'none';
        overlayBg.style.display = "none";
    } else {
        mySidebar.style.display = 'block';
        overlayBg.style.display = "block";
    }
}
// Close the sidebar with the close button
function w3_close() {
    mySidebar.style.display = "none";
    overlayBg.style.display = "none";
}
</script>

</body>
</html>