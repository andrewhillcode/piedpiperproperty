<?php
  include 'inc/PDO.inc';
  $date = date('Y-m-d');


  //find owner id
  try {
    $getID = $pdo->prepare('SELECT staff_id FROM staff_members WHERE email = :email');
    $getID->bindValue(':email', $_SESSION['email']);
    $getID->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }


  $staffID = $getID->fetch();
  $staffID = $staffID[0];

  try {
    $result = $pdo->prepare('SELECT * FROM house_information JOIN houses ON house_information.house_id = houses.house_id JOIN staff_members ON houses.staff_id = staff_members.staff_id JOIN user_information ON staff_members.email = user_information.email JOIN owners ON houses.owner_id = owners.owner_id WHERE houses.staff_id = :staff_id ORDER BY houses.house_id ASC');
    $result->bindValue(':staff_id', $staffID);
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }


  try {
    $bookings = $pdo->prepare('SELECT * FROM viewing_bookings JOIN house_information ON viewing_bookings.house_id = house_information.house_id JOIN tenants ON viewing_bookings.tenant_id = tenants.tenant_id JOIN user_information ON tenants.email = user_information.email WHERE staff_id = :staff_id AND viewing_bookings.date >= :date ORDER BY viewing_bookings.date');  
    $bookings->bindValue(':staff_id',$staffID);
    $bookings->bindValue(':date',$date);
    $bookings->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }



?>
<div class="container">
   <?php 
     if ($bookings->rowCount() > 0){      
      echo '<div class="page-header">';
        echo '<h1 class="text-center">Upcoming Bookings</h1>';
      echo '</div>';
      echo '<div class="container">';
        echo '<table class="bookings">';
          echo '<tr>';
            echo '<td>';
              echo "<b>Address</b>";
            echo '</td>';
            echo '<td>';
              echo "<b>Date</b>";
            echo '</td>';
            echo '<td>';
              echo "<b>Time</b>";
            echo '</td>';
            echo '<td>';
              echo '<b>Tenant</b>';
            echo '</td>';
            echo '<td></td>';
         echo '</tr>';
          foreach ($bookings as $booking){
            echo '<tr>';
              echo '<td>';
                echo $booking['address'];
              echo '</td>';
              echo '<td>';
                echo $booking['date'];
              echo '</td>';
              echo '<td>';
                echo $booking['time'];
              echo '</td>';
              echo '<td>';
                echo $booking['first_name']." ".$booking['last_name'] ;
              echo '</td>';
              echo '<td>';
                echo "<a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='Details'>Details</a>";
              echo '</td>';
            echo '</tr>';
          }
        echo '</table>';
      echo '</div>';

    } 
  ?>
  <div class="page-header">
    <h1 class="text-center">Assigned Properties</h1>
  </div>
  <div class="container">
    <?php
      $i = 0;
      if ($result->rowCount() == 0) {
        echo "<h2>You are not assigned to any properties</h2>";
      } else {
        
        echo "<table class='property-table'>";
          echo "<tr>";
            echo "<td></td>";
            echo "<td><b>Address</b></td>";
            echo "<td><b>Owner</b></td>";
            echo "<td></td>";
          echo "</tr>";
        foreach($result as $house) {       
              echo "<tr>";
                if ($house['available'] == 1) {
                  echo "<td><span class='glyphicon glyphicon-eye-open' aria-hidden='true'></span></td>";
                } else {
                  echo "<td>&nbsp</td>";
                }
                echo "<td>",$house['address'],"</td>";
                echo "<td>",$house['email'],"</td>";
                echo "<td><a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='Details'>Details</a></td>";
              echo "</tr>";
            }
          echo "</table>";
      }
    ?>
  </div>
</div>