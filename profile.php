<?php
include_once'inc/loginsession.inc';	
include 'inc/PDO.inc';
$error = '';

if(!isset($_SESSION['email']))
{
	header( 'Location: index.php' );
	exit;
}

// Check if form was submitted previously, submit new data to the database if so

if(isset($_POST['updated']))
{
	include 'inc/updateUserInfo.inc';
}

// Collect user data from database

try {
  $query = $pdo->prepare('SELECT * '.
   'FROM user_information '.
   'WHERE email = :email ');
  $query->bindValue(':email', $_SESSION['email']);
  $query->execute();
}
catch (PDOException $e) {
  echo $e->getMessage();
}

$userInfo = $query->fetch();

$firstName = $userInfo['first_name'];
$lastName = $userInfo['last_name'];
$contactNumber = $userInfo['contact_number'];
$joinDate = $userInfo['date_joined'];
$email = $_SESSION['email'];

// Set a default profile picture if one isn't provided

if($userInfo['profile_picture'] == '')
{
	$profilePicture = 'img/default.png';
}
else
{
	$profilePicture = 'img/'.$userInfo['profile_picture'];
}
?>

<!DOCTYPE html>
<html>
<head>
	<title>Your Profile</title>
  <link rel="icon" type="image/png" href="img/favicon.png" />
	<!-- Latest compiled and minified CSS -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap.min.css">
	<!-- Optional theme -->
	<link rel="stylesheet" href="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/css/bootstrap-theme.min.css">
	<!-- override stylesheet -->
	<link rel="stylesheet" type="text/css" href="css/defaultStyle.css">
  <!-- index stylesheet -->
  <link rel="stylesheet" type="text/css" href="css/profileStyle.css">
	<!-- Latest compiled and minified JavaScript -->
	<script src="https://ajax.googleapis.com/ajax/libs/jquery/1.11.3/jquery.min.js"></script>
	<script src="https://maxcdn.bootstrapcdn.com/bootstrap/3.3.5/js/bootstrap.min.js"></script>
</head>
<body>	
<?php include 'inc/navigation.inc'; ?>
<script src="js/profileScript.js"></script>
<div class="container">
  <div class="page-header">
    <h1 class="text-center">Your Profile</h1>
	<h3 class="text-center error"><?php echo $error; ?></h3>
  </div>
  <div class="container">
	<div class="col-sm-3">
		<img class="profilePicture" src="<?php echo $profilePicture ?>">
		<button class="btn btn-default profileForm">Upload Photo</button>
    </div>
    <div class="col-sm-4">
		<form name="profileInfoForm" action="profile.php" onsubmit="return validateForm()" method="post">
        <h3 class="profileInfo"><?php echo $firstName.' '.$lastName ?></h3>
		<input required class="profileForm inlineInput form-control" type="text" name="firstNameForm" placeholder="First Name" value="<?php echo $firstName ?>"></input>
		<input required class="profileForm inlineInput form-control" type="text" name="lastNameForm" placeholder="Last Name" value="<?php echo $lastName ?>"><br></input>
        <br>
		Join Date: <h4><?php echo $joinDate ?></h4><br>
		Email Address: <h4 class="profileInfo"><?php echo $email ?></h4>
		<input required class="profileForm form-control" type="text" name="emailForm" placeholder="Email Address" value="<?php echo $email ?>"></input><br>
        Contact Number: <h4 class="profileInfo"><?php echo $contactNumber ?></h4>
		<input class="profileForm form-control" type="text" name="contactForm" placeholder="Contact Number" value="<?php echo $contactNumber ?>"></input><br>
		
		<label class="profileForm">(Optional)</label>
		<input class="profileForm form-control" type="password" name="passwordForm" placeholder="New Password"></input>
		<input class="profileForm form-control" type="password" name="passwordConfirmForm"placeholder="Confirm Password"></input>
		
		<input type="hidden" name="updated" value="true"></input>
		<input type="submit" class="btn btn-default profileForm inlineInput" value="Update Details"></button>
		<button onclick="endEdit();" class="btn btn-default profileForm inlineInput">Cancel</button>
		</form>
		<button onclick="beginEdit();" class="btn btn-default profileInfo">Edit Details</button>
		<hr>
    </div>
</div>
</div>
<?php include 'inc/footer.inc'; ?>

<script src="js/headerScript.js"></script>
<script src="js/modalScript.js"></script>
</body>
</html>