<?php
if (isset($_POST['remove'])){
  $username = 'piperadmin';
  $password = 'password';
  $adminPDO = new PDO('mysql:host=localhost;dbname=ifb299', $username, $password);
  $adminPDO->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

  try {
    $sql = "DELETE FROM house_information WHERE house_id = :house_id";
    $stmt = $adminPDO->prepare($sql);
    $stmt->bindValue(':house_id', $_GET['house_id'], PDO::PARAM_INT);
    $stmt->execute();

    $grabImageNames = $pdo->prepare('SELECT image_path FROM house_images WHERE house_id = :house_id');
    $grabImageNames->bindValue(':house_id', $_GET['house_id'], PDO::PARAM_INT);
    $grabImageNames->execute();

    $sql = "DELETE FROM house_images WHERE house_id = :house_id";
    $stmt = $adminPDO->prepare($sql);
    $stmt->bindValue(':house_id', $_GET['house_id'], PDO::PARAM_INT);
    $stmt->execute();

    $imgnumber = $grabImageNames->rowCount();

    while ($imgnumber > 0) {
      $image = $grabImageNames->fetch(); 
      $image = $image[0];
      unlink("img/".$image);
      $imgnumber--;
    }

    $sql = "DELETE FROM viewing_times WHERE house_id = :house_id";
    $stmt = $adminPDO->prepare($sql);
    $stmt->bindValue(':house_id', $_GET['house_id'], PDO::PARAM_INT);
    $stmt->execute();

    $sql = "DELETE FROM houses WHERE house_id = :house_id";
    $stmt = $adminPDO->prepare($sql);
    $stmt->bindValue(':house_id', $_GET['house_id'], PDO::PARAM_INT);
    $stmt->execute();


  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
}

  try { //grab staff
    $result = $pdo->prepare('SELECT * FROM house_information JOIN houses ON house_information.house_id = houses.house_id JOIN staff_members ON houses.staff_id = staff_members.staff_id JOIN user_information ON staff_members.email = user_information.email JOIN owners ON houses.owner_id = owners.owner_id ORDER BY houses.house_id ASC');
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $date = date('Y-m-d');
  try {
    $bookings = $pdo->prepare('SELECT * FROM viewing_bookings JOIN house_information ON viewing_bookings.house_id = house_information.house_id JOIN staff_members ON viewing_bookings.staff_id = staff_members.staff_id JOIN user_information ON staff_members.email = user_information.email JOIN tenants ON tenants.tenant_id = viewing_bookings.tenant_id AND viewing_bookings.date >= :date ORDER BY viewing_bookings.date');  
    $bookings->bindValue(':date',$date);
    $bookings->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
?>
<div class="container">
  <div class="page-header">
    <h1 class="text-center">Manage Properties</h1>
  </div>
  <div class="container">
    <?php
      if ($result->rowCount() == 0) {
        echo "<h2>No properties</h2>";
      } else {

        echo "<div class='row'>";
        echo "<div class='col-md-10'>";

        echo "<table class='property-table'>";
          echo "<tr>";
            echo "<td></td>";
            echo "<td><b>Address</b></td>";
            echo "<td><b>Staff</b></td>";
            echo "<td><b>Owner</b></td>";
            echo "<td></td>";
            echo "<td></td>";
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
                echo "<td>",$house['first_name']," ",$house['last_name'],"</td>";
                echo "<td>",$house['email'],"</td>";
                echo "<td><a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='Details'>Details</a></td>";
                echo "<td><a href='editPropAdmin.php?house_id=",$house['house_id'],"' class='btn btn-warning' title='Edit'>Edit</a></td>";
                echo "<td>";
                  echo "<form method='post' action='manage.php?house_id=",$house['house_id'],"'>";
                  echo "<input class='btn btn-danger' type='submit' name='remove' value='Remove'>";
                  echo "</form>";
                echo "</td>";
              echo "</tr>";
            }
          echo "</table>";
        echo "</div>";
        echo "<div class='col-md-2'>";        
          echo "<h4>Add a property</h4>";
          echo "<a href='addProperty.php' class='btn btn-success' title='Add'>Add Property</a>";
        echo "</div>";
      echo "</div>";  
      }

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
              echo '<b>Staff</b>';
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
                echo $booking['email'] ;
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
  </div>
  <br><br>
</div>