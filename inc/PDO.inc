<?php
ini_set('memory_limit', '-1');
  $username = 'piperuser';
  $password = 'password';
  $pdo = new PDO('mysql:host=localhost;dbname=ifb299', $username, $password);
  $pdo->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

?>