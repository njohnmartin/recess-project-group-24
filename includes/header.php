<?php session_start(); 
if (!isset($_SESSION['userid'])) {
  header("location: login.php");
}else {
 echo  $_SESSION['userid'];
}
 ?>
<!DOCTYPE html>
<html>
<title>admin web interface</title>
<meta charset="UTF-8">
<meta name="viewport" content="width=device-width, initial-scale=1">
<link rel="stylesheet" href="style1.css">
<style>
html,body,h1,h2,h3,h4,h5 {font-family: "Raleway", sans-serif}
.w3-bar-block .w3-bar-item {
    width: 100%;
    height: 80px;
    display: block;
    padding: 8px 16px;
    text-align: left;
    border: none;
    border-bottom: 1px solid #fefe;
    white-space: normal;
    float: none;
    outline: 0;
}

.data-table {
  margin: 15px 20px;
  border-radius: 5px;
}

.data-table thead {
  background-color: #4f4f4f;
  color: #fff;
}

.data-table td, .data-table th {
  padding: 5px 10px;
}


</style>
<body style = "background-image:url()" class="w3-light-grey">

<!-- Top container -->
<h4><a href="logout.php" style="float: right;"> logout </a></h4>


<div class="w3-bar w3-top w3-black w3-large" style="z-index:4">
  <button class="w3-bar-item w3-button w3-hide-large w3-hover-none w3-hover-text-light-grey" onclick="w3_open();"><i class="fa fa-bars"></i>  Menu</button>
  <span class="w3-bar-item w3-right">Logo</span>
</div>

<!-- Sidebar/menu -->
<nav class="w3-sidebar w3-collapse w3-white w3-animate-left" style="z-index:3;width:300px;" id="mySidebar"><br>
  <div class="w3-container w3-row">
    <div class="w3-col s4">
      <img src="benard.jpg" class="w3-circle w3-margin-right" style="width:46px">
    </div>
    <div class="w3-col s8 w3-bar">
      <span><h4>Welcome to</h4><strong><h3 style="color: blue">GROUP 24</h3></strong></span>
      <a href="#" class="w3-bar-item w3-button"><i class="fa fa-envelope"></i></a>
      <a href="#" class="w3-bar-item w3-button"><i class="fa fa-user"></i></a>
      <a href="#" class="w3-bar-item w3-button"><i class="fa fa-cog"></i></a>
    </div>
  </div>
  <hr>
  <div class="w3-container">
    <h5>Dashboard</h5>
  </div>


  <p style="text-align: center">
  <div class="w3-bar-block">
    <a href="#" class="w3-bar-item w3-button w3-padding-16 w3-hide-large w3-dark-grey w3-hover-black" onclick="w3_close()" title="close menu"><i class="fa fa-remove fa-fw"></i>  Close Menu</a>
    <a href="index.php" class="w3-bar-item w3-button w3-padding w3-green"><i class="fa fa-eye fa-fw"></i>  Home</a>
    <a href="ready_list.php" class="w3-bar-item w3-button w3-padding w3-green"><i class="fa fa-eye fa-fw"></i>  READY JOBS</a>
    <a href="waiting_jobs.php" class="w3-bar-item w3-button w3-padding w3-green"><i class="fa fa-users fa-fw"></i>WAITING JOBS</a>
   
    <a href="failed_jobs.php" class="w3-bar-item w3-button w3-padding w3-green"><i class="fa fa-diamond fa-fw"></i>  FAILED JOBS</a>
    
    <br><br>
  </div>
  </p>


</nav>
<div class="w3-overlay w3-hide-large w3-animate-opacity" onclick="w3_close()" style="cursor:pointer" title="close side menu" id="myOverlay"></div>

<!-- !PAGE CONTENT! -->
<div class="w3-main" style="margin-left:300px;margin-top:43px;">