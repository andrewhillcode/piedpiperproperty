<body>
  <p>This is a test header file</p>
  <?php
    if (!isset($_SESSION['email'])) {
      //Display Login Button
      echo '<a href="registration.php">Register</a>';
      echo '<a href="login.php">Login</a>';
    }
    else {
      //Display Logout Button
      echo '<a href="profile.php">Profile</a>';
      echo '<a href="login.php?logout=true">Logout</a>';
    }
  ?>
</body>
