<?php
  error_reporting(-1);
  ini_set('display_errors', 'On');
  include 'inc/PDO.inc';
 $date = date('Y-m-d');
  //find tenant id
  try {
    $getID = $pdo->prepare('SELECT tenant_id FROM tenants WHERE email = :email');
    $getID->bindValue(':email', $_SESSION['email']);
    $getID->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $userID = $getID->fetch();
  $userID = $userID[0];

  try {
    $result = $pdo->prepare('SELECT * FROM house_information, favourites WHERE tenant_id = :tenant_id AND favourites.house_id = house_information.house_id AND available = 1');  
    $result->bindValue(':tenant_id',$userID);
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  try {
    $bookings = $pdo->prepare('SELECT * FROM viewing_bookings JOIN house_information ON viewing_bookings.house_id = house_information.house_id WHERE tenant_id = :tenant_id AND viewing_bookings.date >= :date ORDER BY viewing_bookings.date');  
    $bookings->bindValue(':tenant_id',$userID);
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
        echo '<table>';
          echo '<tr>';
            echo '<td>';
              echo "Address";
            echo '</td>';
            echo '<td>';
              echo "Date";
            echo '</td>';
            echo '<td>';
              echo "Time";
            echo '</td>';
            echo '<td>';
            echo '</td>';
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
                echo "<td><a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='Details'>Details</a></td>";
              echo '</td>';
            echo '</tr>';
          }
        echo '</table>';
      echo '</div>';

    } 
  ?>
  <div class="page-header">
    <h1 class="text-center">Favourites</h1>
  </div>
  <div class="container">
    <?php
      $i = 0;
      if ($result->rowCount() == 0) {
        echo "<h2>It looks like you don't have any favourites! </h2>";
      }
        foreach($result as $house) {
          try {
            $imagequery = $pdo->prepare('SELECT image_path FROM house_images WHERE house_id = :house_id ');
            $imagequery->bindValue(':house_id', $house['house_id']);
            $imagequery->execute();
          }
          catch (PDOException $e) {
            echo $e->getMessage();
          }
          $image = $imagequery->fetch();
          $image = $image[0];

          echo "<div class='row'>";
            echo "<div class='col-md-4 property-details'>";
              echo "<div>";
                echo "<h2>",$house['address'],"</h2>";
                echo "<img src='img/bed.png' alt='Beds'>";
                echo "<span class='property-icon'>",$house['bed_number'],"</span>";
                echo "<img src='img/bath.png' alt='baths'>";
                echo "<span class='property-icon'>",$house['bath_number'],"</span>";
                echo "<img src='img/car.png' alt='cars'>";
                echo "<span class='property-icon'>",$house['carport_number'],"</span>";
                echo "<h3>$",$house['price']," per week</h3>";
                echo "<a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='See more'>More Details</a>";
              echo "</div>";
            echo "</div>";
            echo "<div class='col-md-6 result-thumbnail'>";
              echo "<a href='property.php?house_id=",$house['house_id'],"'>";
                echo "<img src='img/$image' alt='House' class='img-thumbnail'>";
              echo "</a>";
            echo "</div>";
          echo "</div>";
          $i++;
        }
      
    ?>
  </div>
</div>

