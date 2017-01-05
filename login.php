<?php
  include_once'loginsession.inc';
  include 'inc/testheader.inc';
  include 'inc/PDO.inc';

//Persistent login info, change displays if user is logged in / not logged in
  if (isset($_GET['logout'])) {
    if (isset($_SESSION['email'])) {
      unset($_SESSION['email']);
    }
  }

  echo '
    <div id="formContainer">
    <form action="login.php" id="loginForm" method="post">
      Username:<br>
      <input type="text" name="email"><span id="usernameRequired" style="visibility:hidden;"> Username is required</span>
      <br><br>
      Password:<br>
      <input type="password" name="password"></input><br><br>
      <input type="submit" name="submitButton"><br><br>
      <span id="incorrectDetails" style="visibility:hidden;"> Incorrect username or password.</span>
    </form>

    </div>';

  if (isset($_POST['email']) && isset($_POST['password'])) {
    //Check login against SQL, if success redirect to index and set vars, else display error
    $stmt = $pdo->prepare('SELECT email, password FROM user_information WHERE email = :email AND password = :pass');
    $stmt->bindValue(':email', $_POST['email']);
    $stmt->bindValue(':pass', $_POST['password']);
    $stmt->execute();

    if ( $stmt->rowCount() > 0 ) {
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
