<?php	
	
// Check Email form is valid (Just blank for now)
$error = '';
if($_POST['emailForm'] == '')
{
	$error = $error . "Email cannot be blank. ";
}

// If user attempted to change passwords
if( $_POST['passwordForm'] != '' )
{
	// Ensure submitted passwords match
	if( $_POST['passwordForm'] == $_POST['passwordConfirmForm'] )
	{
		$passwordQuery = ', password=:password';
	}
	else
	{
		$error = $error . "Passwords do not match. ";
	}
}
else
{
	$passwordQuery = '';
}

// If the password has to be changed, the query will be changed accordingly
// Otherwise nothing will be added

if(!isset($error))
{	
	try {
		$query = $pdo->prepare('UPDATE user_information '.
			'SET email=:email, first_name=:firstName, last_name=:lastName, contact_number=:contactNumber'.
			$passwordQuery.
			' WHERE email=:oldEmail'
		);
			
		
		$query->bindValue(':email', $_POST['emailForm']);
		$query->bindValue(':firstName', $_POST['firstNameForm']);
		$query->bindValue(':lastName', $_POST['lastNameForm']);
		$query->bindValue(':contactNumber', $_POST['contactForm']);
		$query->bindValue(':oldEmail', $_SESSION['email']);
		
		if($passwordQuery != '')
		{
			$query->bindValue(':password', $_POST['passwordForm']);
		}
		
		$query->execute();
	}
	catch (PDOException $e) 
	{
	echo $e->getMessage();
	}
}
?>