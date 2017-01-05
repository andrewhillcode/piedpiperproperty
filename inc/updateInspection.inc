<?php	
	
try {
  $query = $pdo->prepare('SELECT staff_id FROM staff_members WHERE email = :email ;');
  $query->bindValue(':email', $_SESSION['email']);
  $query->execute();
  $staffquery = $query->fetch();
  
  $staffID = $staffquery['staff_id'];
}
catch (PDOException $e) {
  echo $e->getMessage();
}
	
$error = '';
if($_POST['houseID'] == '' || $_POST['date'] == '')
{
	$error = $error . "Address or Date not Selected ";
}

if(!($_POST['action'] == 'Create' || $_POST['action'] == 'Update' || $_POST['action'] == 'Delete'))
{
	$error = 'invalid form action';
}
	
if($error =='')
{	
	try {
		if($_POST['action'] == 'Create')
		{
			$query = $pdo->prepare('INSERT INTO inspections (staff_id, house_id, details, date) '.
			'VALUES (:staffID, :houseID, :details, str_to_date(:date, "%d/%m/%Y"));'
			);
		
			$query->bindValue(':staffID', $staffID);
			$query->bindValue(':houseID', $_POST['houseID']);
			$query->bindValue(':details', $_POST['details']);
			$query->bindValue(':date', $_POST['date']);
		}
		
		if($_POST['action'] == 'Update')
		{
			$query = $pdo->prepare('UPDATE inspections SET details=:details, date=str_to_date(:date, "%d/%m/%Y"), house_id = :houseID, completed = :completed '.
			'WHERE inspection_id = :inspectionID ;'
			);
			$query->bindValue(':houseID', $_POST['houseID']);
			$query->bindValue(':inspectionID', $_POST['inspectionID']);
			$query->bindValue(':details', $_POST['details']);
			$query->bindValue(':date', $_POST['date']);
		
			$completed = 0;
			if(isset($_POST['complete']))
			{
				$completed = 1;
			}
			$query->bindValue(':completed', $completed);
		}	
		
		if($_POST['action'] == 'Delete')
		{
			$query = $pdo->prepare('DELETE FROM inspections '.
			'WHERE inspection_id = :inspectionID ;'
			);
			$query->bindValue(':inspectionID', $_POST['inspectionID']);
		}
		$query->execute();
	}
	catch (PDOException $e) 
	{
	echo $e->getMessage();
	}
}
?>