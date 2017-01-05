<?php
error_reporting(-1);
ini_set('display_errors', 'On');

	include 'inc/PDO.inc';
  $date = date("Y-m-d");

 if (isset($_POST['submit'])){

 	  try { //Grab filepath to all images for the house
    $images = $pdo->prepare('SELECT AUTO_INCREMENT FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = :dbName AND   TABLE_NAME = :tableName');
    $images->bindValue(':dbName', 'ifb299');
    $images->bindValue(':tableName', 'house_images');
    $images->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $imagenumber = $images->fetch();
  $imagenumber = $imagenumber[0];

  	$newfilename = 'prop'.$imagenumber.".png";
	$target_dir = "img";	

	move_uploaded_file($_FILES["file"]["tmp_name"], "$target_dir/$newfilename");

    try {
      $insertToHouses = $pdo->prepare('INSERT INTO houses (staff_id, owner_id) VALUES (:staff_id, :owner_id)');
      $insertToHouses->bindValue(':staff_id', $_POST['staff_id']);
      $insertToHouses->bindValue(':owner_id', $_POST['owner_id']);
      $insertToHouses->execute();
      
      $insertToHouseInfo = $pdo->prepare('INSERT INTO house_information (house_id, address, bed_number, bath_number, carport_number, price, date_listed, house_description, furnished,  type, available) 
        VALUES (LAST_INSERT_ID(), :address, :beds, :baths, :cars, :price, :datelisted, :description, :furnished, :type, :available)');
      $insertToHouseInfo->bindValue(':address', $_POST['address']);
      $insertToHouseInfo->bindValue(':beds', $_POST['beds']);
      $insertToHouseInfo->bindValue(':baths', $_POST['baths']);
      $insertToHouseInfo->bindValue(':cars', $_POST['cars']);
      $insertToHouseInfo->bindValue(':price', $_POST['price']);
      $insertToHouseInfo->bindValue(':furnished', $_POST['furnished']);
      $insertToHouseInfo->bindValue(':description', $_POST['houseDescription']);
      $insertToHouseInfo->bindValue(':datelisted', $date);
      $insertToHouseInfo->bindValue(':type', $_POST['type']);
      $insertToHouseInfo->bindValue(':available', $_POST['available']);
      $insertToHouseInfo->execute();

      $insertToViewingTimes = $pdo->prepare('INSERT INTO viewing_times (house_id, day, time) VALUES (LAST_INSERT_ID(), :day, :time)');
      $insertToViewingTimes->bindValue(':day', $_POST['viewingDay']);
      $insertToViewingTimes->bindValue(':time', $_POST['viewingTime']);
      $insertToViewingTimes->execute();

      $insertToHouseImages = $pdo->prepare('INSERT INTO house_images (house_id, image_path) VALUES (LAST_INSERT_ID(), :file)');
      $insertToHouseImages->bindValue(':file', $newfilename);
      $insertToHouseImages->execute();
      header('Location: manage.php');
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    } 
  }

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
  <!-- editProp stylesheet -->
  <link rel="stylesheet" type="text/css" href="css/editPropertyStyle.css">
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
</head>

<?php
	include 'inc/navigation.inc';
	include 'inc/addPropContent.inc';
	include 'inc/footer.inc';
?>

<script src="js/headerScript.js"></script>
<script src="js/modalScript.js"></script>
