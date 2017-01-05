<?php
include_once'inc/loginsession.inc';
include 'inc/PDO.inc';

//Persistent login info, change displays if user is logged in / not logged in
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
<?php
  if (isset($_POST['email']) && isset($_POST['password'])) {
    //Check login against SQL, if success redirect to index and set vars, else display error
    $stmt = $pdo->prepare('SELECT email, password FROM user_information WHERE email = :email AND password = :pass');
    $stmt->bindValue(':email', $_POST['email']);
    $stmt->bindValue(':pass', $_POST['password']);
    $stmt->execute();

    if ($stmt->rowCount() > 0) {
      //Successful login
      $result = $stmt->fetch();
      $_SESSION['email'] = $result['email'];
      //if ($result['isAdmin'] == 1) {
      //  $_SESSION['isAdmin'] = 1;
      //}

    } else {
      echo '
      <script>
        document.getElementById("incorrectDetails").style.visibility = "visible";
      </script>';
    }
  }
?>
