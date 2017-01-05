<?php
include_once'inc/loginsession.inc';	
include 'inc/PDO.inc';
$error = '';

if(!isset($_SESSION['email']))
{
	header( 'Location: index.php' );
	exit;
}

// Collect user data from database

if(isset($_POST['updated']))
{
	include 'inc/updateInspection.inc';
}

try {
  $query = $pdo->prepare('SELECT inspections.inspection_id, DATE_FORMAT(inspections.date, "%d/%m/%Y") AS date, house.house_id, house.address, inspections.details, inspections.completed FROM inspections '.
	'inner join staff_members as staff on staff.staff_id = inspections.staff_id '.
	'inner join house_information as house on house.house_id = inspections.house_id '.
	'WHERE staff.email = :email '.
	'ORDER BY inspections.date;');
  $query->bindValue(':email', $_SESSION['email']);
  $query->execute();
  $inspections = $query->fetchAll();
}
catch (PDOException $e) {
  echo $e->getMessage();
}



try {
  $query = $pdo->prepare('SELECT house.address, house.house_id FROM houses '.
	'inner join staff_members as staff on staff.staff_id = houses.staff_id '.
	'inner join house_information as house on house.house_id = houses.house_id '.
	'WHERE staff.email = :email ');
  $query->bindValue(':email', $_SESSION['email']);
  $query->execute();
  $houses = $query->fetchAll();
}
catch (PDOException $e) {
  echo $e->getMessage();
}



?>

<head>
	<title>Inspections</title>
  <link rel="icon" type="image/png" href="img/favicon.png" />
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">
	<!-- override stylesheet -->
	<link rel="stylesheet" type="text/css" href="css/defaultStyle.css">
  <!-- index stylesheet -->
  <link rel="stylesheet" type="text/css" href="css/inspectionsStyle.css">
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
	<script src="js/inspectionScript.js"></script>
</head>

<?php include 'inc/navigation.inc'; ?>
<div class="container">
  <div class="page-header">
    <h1 class="text-center">Inspections</h1>
	<h3 class="text-center error"><?php echo $error; ?></h3>
  </div>
  <div class="container border schedule">
	  <h3 class="text-center">Schedule new Inspection</h3>
	  
  <form id="inspectionForm" action="inspections.php" onsubmit="return validateForm()" method="post">
    <select id='houseID' required name="houseID" >
		<option value=''>Select House</option>
		<?php
			foreach($houses as $house)
			{
			echo '<option value=',$house['house_id'],'>',$house['address'],'</option>';
			}
		?>
		</select>
		
	Date: <input id='date' name='date' type="date" required placeholder='dd/mm/yyyy'></input>
	Completed: <input name='complete' type="checkbox" value=1></input><br>
	<textarea id="details" name="details" form="inspectionForm" placeholder="Extra Details"></textarea>
	<input type="hidden" name="updated" value="true"></input>
	<input id='inspectionID' type="hidden" name="inspectionID" value=""></input>
	<input type="submit" id='createButton' class="btn createButton btn-primary" name="action" value="Create">
	<input type="submit" id='updateButton' class="btn hidden btn-primary" name="action" value="Update">
	<input type="submit" id='deleteButton' class="btn hidden btn-danger" name="action" value="Delete">
	</form>
	
	</div>
  <div class="container center-container">
	<div class="col-sm-5 border">
		<h3 class="text-center">Planned Inspections</h3>
		<table id='plannedInspections'>
		<?php 
			$i=0;
			foreach($inspections as $inspection)
			{
				if($inspection['completed'] == 0) 
				{
					if($inspection['details'] == '')
					{
						$inspection['details'] = 'No details for this inspection';
					}
					
					echo "<tr>";
					echo "<td>",$inspection['address'],"</td>";
					echo "<td>",$inspection['date'],"</td>";
					echo "<td><button class='btn btn-primary' onclick='editInspection($i)' title='Edit'>Edit</button></td>";
					echo "<td><a href='property.php?house_id=",$inspection['house_id'],"' class='btn btn-primary' title='Details'>Details</a></td>";
					echo "<td>",$inspection['details'],"</td>";
					echo "<td class='hidden'>",$inspection['house_id'],"</td>";
					echo "<td class='hidden'>",$inspection['inspection_id'],"</td>";
					echo "</tr>";
					$i++;
				}
			}
			?>
		</table>
    </div>
    <div class="col-sm-5 border">
		<h3 class="text-center">Previous Inspections</h3>
		<table>
		<?php 
			foreach($inspections as $inspection)
			{
				if($inspection['completed'] == 1) 
				{
					if($inspection['details'] == '')
					{
						$inspection['details'] = 'No details for this inspection';
					}
					
					echo "<tr>";
					echo "<td><b>",$inspection['address'],"</b></td>";
					echo "<td>",$inspection['date'],"</td>";
					echo "<td>&nbsp;</td>";
					echo "<td><a href='property.php?house_id=",$inspection['house_id'],"' class='btn btn-primary' title='Details'>Details</a></td>";
					echo "<td><p>",$inspection['details'],"</p></td>";
					echo "</tr>";
					
				}
			}
			?>
		</table>
    </div>
</div>
</div>
<?php include 'inc/footer.inc'; ?>

<script src="js/headerScript.js"></script>
<script src="js/modalScript.js"></script>