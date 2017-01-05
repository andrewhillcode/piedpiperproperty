<?php

	ini_set('display_errors',1);
	ini_set('display_startup_errors',1);
	error_reporting(-1);
?>

<head>
	<title>Pied Piper Property</title>
  <link rel="icon" type="image/png" href="img/favicon.png" />
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">
	<!-- override stylesheet -->
	<link rel="stylesheet" type="text/css" href="css/defaultStyle.css">
 	<!-- index stylesheet -->
  	<link rel="stylesheet" type="text/css" href="css/propertyStyle.css">
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
	<script src="https://maps.googleapis.com/maps/api/js"></script>
	<script src="js/geolocationScript.js"></script>
	<script src="js/map.js"></script>
</head>

<?php
  include 'inc/PDO.inc';
	include 'inc/navigation.inc';
	include 'inc/propertyInfo.inc';
	include 'inc/footer.inc';
?>

<script src="js/headerScript.js"></script>
<script src="js/modalScript.js"></script>
