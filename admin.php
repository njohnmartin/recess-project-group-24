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
      <b><h1 style="text-align: center; color: purple; font-family: algerian"> WELCOME TO THE ADMIN </h1></b><b><h1 style="text-align: center; color: purple; font-family: algerian">WEB INTERFACE</h1></b>
    </p><br><br>
    </h1></b></h5>
  </header>

  <div class="w3-row-padding w3-margin-bottom">
    <div class="w3-quarter">
      <div class="w3-container w3-red w3-padding-16">
        <div class="w3-left"><i class="fa fa-comment w3-xxxlarge"></i></div>
        <div class="w3-right">
          <h3></h3>
        </div>
        <div class="w3-clear"></div>
        <h4>PROCESSING JOBS LIST </h4>
      </div>
    </div>
       <div class="w3-quarter">
      <div class="w3-container w3-teal w3-padding-16">
        <div class="w3-left"><i class="fa fa-share-alt w3-xxxlarge"></i></div>
        <div class="w3-right">
          <h3></h3>
        </div>
        <div class="w3-clear"></div>
        <h4>BUSY JOBS LIST</h4>
      </div>
    </div>
    <div class="w3-quarter">
      <div class="w3-container w3-orange w3-text-white w3-padding-16">
        <div class="w3-left"><i class="fa fa-users w3-xxxlarge"></i></div>
        <div class="w3-right">
          <h3></h3>
        </div>
        <div class="w3-clear"></div>
        <h4>BLACKLSTED JOBS LIST</h4>
      </div>
    </div>
  </div>

<?php
$query = <<<SQL
  SELECT al.userid,
    ( SELECT COUNT(*) FROM ready_jobs WHERE userid=al.userid ) as success_count,
    ( SELECT COUNT(*) FROM failed_jobs WHERE userid=al.userid ) as failure_count
  FROM (
    SELECT DISTINCT(userid) FROM ready_jobs
    UNION
    SELECT DISTINCT(userid) FROM failed_jobs
    ) AS al
    GROUP BY al.userid
SQL;
?>

  <hr>
  <div class="w3-container">
    <h5>General Stats</h5>
    <p>The student's ID with the Highest percentage success rate: <span class="dname"> U001</span></p>
    <div class="w3-grey">
      <div class="w3-container w3-center w3-padding w3-green" style="width:25%">+25%</div>
    </div>

    <p>The student's ID with highest percentage failure rate: <span class="dname"> U004</span></p>
    <div class="w3-grey">
      <div class="w3-container w3-center w3-padding w3-orange" style="width:50%">50%</div>
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

