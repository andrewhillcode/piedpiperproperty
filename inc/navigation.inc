<?php
	include_once'inc/loginsession.inc';
	if (isset($_GET['logout'])) {
		if (isset($_SESSION['email'])) {
			unset($_SESSION['email']);
		}
	}
?>

<!-- Login Modal -->
<div class="modal fade" id="loginModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Login</h4>
      </div>
      <div class="account-wall">
        <img class="profile-img" src="img/footer-logo.png" alt="">
        <!-- Login Form -->
        <form class="form-signin" method="post">
          <input type="text" name="email" class="form-control" placeholder="Email" required autofocus>
          <input type="password" name="password" class="form-control" placeholder="Password" required>
          <button type="submit" name="submitButton" class="btn btn-lg btn-primary btn-block">Login</button>
          <span id="incorrectDetails" style="visibility:hidden;"> Incorrect username or password.</span>
        </form>
        <a id="noAccountButton" href="#" class="text-center new-account">Don't have an account?</a>
      </div>
    </div>
  </div>
</div>

<?php include 'inc/login.inc' ?>

<!-- Register Modal -->
<div class="modal fade" id="registerModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
  <div class="modal-dialog" role="document">
    <div class="modal-content">
      <div class="modal-header">
        <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
        <h4 class="modal-title" id="myModalLabel">Register</h4>
      </div>
      <div class="account-wall">
        <img class="profile-img" src="img/footer-logo.png" alt="">
        <form action="index.html" class="form-signin">
          <input type="text" class="form-control" placeholder="Name" required autofocus>
          <input type="text" class="form-control" placeholder="Email" required>
          <input type="password" class="form-control" placeholder="Password" required>
          <input type="password" class="form-control" placeholder="Confirm password" required>
          <br>
          <button class="btn btn-lg btn-primary btn-block" type="submit">
            Register</button>
          <span class="clearfix"></span>
        </form>
        <a id="haveLoginButton" href="#" class="text-center new-account">Already have an account?</a>
      </div>
    </div>
  </div>
</div>


<div id="bg-img" class="background-image"> </div>

<nav id="navbar" class="navbar navbar-default navbar-static-top">
	<div class="container">
		 <!-- Brand and toggle get grouped for better mobile display -->
    <div class="navbar-header">
      <button type="button" class="navbar-toggle collapsed" data-toggle="collapse" data-target="#bs-example-navbar-collapse-1" aria-expanded="false">
        <span class="sr-only">Toggle navigation</span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
        <span class="icon-bar"></span>
      </button>
      <a class="navbar-brand" href="#">
        <img alt="Brand" src="img/pp.png" href="index.php">
      </a>
			<div class="nav navbar-nav navbar-left">
				<p class="navbar-text">Pied Piper Property</p>
	    </div>
    </div>


    <?php 
      $isStaff = false;
      $isOwner = false;

      if (isset($_SESSION['email'])) {
      //determine if owner
        try {
          $ownerID = $pdo->prepare('SELECT owner_id FROM owners WHERE email = :email');
          $ownerID->bindValue(':email', $_SESSION['email']);
          $ownerID->execute();
        }
        catch (PDOException $e) {
          echo $e->getMessage();
        }

        if ($ownerID->rowCount() == 0) {
          $isOwner = false;
        } else {
          $isOwner = true;
        }

        //determine if staff
        try {
          $staffID = $pdo->prepare('SELECT staff_id FROM staff_members WHERE email = :email');
          $staffID->bindValue(':email', $_SESSION['email']);
          $staffID->execute();
        }
        catch (PDOException $e) {
          echo $e->getMessage();
        }

        if ($staffID->rowCount() == 0) {
          $isStaff = false;
        } else {
          $isStaff = true;
        }

        try { //determine if admin
          $adminID = $pdo->prepare('SELECT admin_id FROM administrators WHERE email = :email');
          $adminID->bindValue(':email', $_SESSION['email']);
          $adminID->execute();
        }
        catch (PDOException $e) {
          echo $e->getMessage();
        }

        if ($adminID->rowCount() == 0) {
          $isAdmin = false;
        } else {
          $isAdmin = true;
        }
      }

    ?>


    <!-- Collect the nav links, forms, and other content for toggling -->
    <div class="collapse navbar-collapse" id="bs-example-navbar-collapse-1">
      <ul class="nav navbar-nav navbar-right">
	      <li><a href="index.php">Home</a></li>
	      <li><a href="allListings.php">All Listings</a></li>
			<?php
			if (!isset($_SESSION['email'])) {
				//Display Login Button for people not logged in
				echo '<li><a id="loginButton" href="#">Login</a></li>';
				echo '<li><a id="registerButton" href="#">Register</a></li>';
			}
			else {
				//Display contracts button, for everyone logged in
				echo '<li><a href="mycontracts.php">Contracts</a></li>';
				
				if ($isOwner) {
					echo '<li><a href="myprop.php">My Listed Properties</a></li>';
				}
				
				if ($isStaff) {
					echo '<li><a href="assignedProp.php">Assgined Properties</a></li>';
					echo '<li><a href="inspections.php">Inspections</a></li>';
				}
				
				if ($isAdmin) {
					echo '<li><a href="manage.php">Manage Properties</a></li>';
				}
				
				if (!$isOwner && !$isStaff && !$isAdmin){
					echo '<li><a href="favourites.php">Favourites</a></li>';
				}
				
				//Profile and logout buttons
				echo '<li><a href="profile.php">Profile</a></li>';
				echo '<li><a href="index.php?logout=true">Logout</a></li>';
          }
		  
			?>
				<!--<li><a id="loginButton" href="#">Login</a></li>
	      <li><a id="registerButton" href="#">Register</a></li>-->
	    </ul>
		</div>
  </div>
</nav>
