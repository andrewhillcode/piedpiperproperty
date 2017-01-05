<?php
  include 'inc/PDO.inc';
 


  //find owner id
  try {
    $getID = $pdo->prepare('SELECT owner_id FROM owners WHERE email = :email');
    $getID->bindValue(':email', $_SESSION['email']);
    $getID->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }


  $ownerID = $getID->fetch();
  $ownerID = $ownerID[0];

  try {
    $result = $pdo->prepare('SELECT * FROM house_information, houses WHERE owner_id = :owner_id AND houses.house_id = house_information.house_id');
    $result->bindValue(':owner_id', $ownerID);
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
?>
<div class="container">
  <div class="page-header">
    <h1 class="text-center">My Properties</h1>
  </div>
  <div class="container">
    <?php
      $i = 0;
      if ($result->rowCount() == 0) {
        echo "<h2>You don't have any properties</h2>";
      } else {

        echo "<div class='row'>";
        echo "<div class='col-md-10'>";

        echo "<table class='property-table'>";
          echo "<tr>";
            echo "<td></td>";
            echo "<td><b>Address</b></td>";
            echo "<td><b>Views</b></td>";
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
                echo "<td>",$house['views'],"</td>";
                echo "<td><a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='Details'>Details</a></td>";
                echo "<td><a href='editProp.php?house_id=",$house['house_id'],"' class='btn btn-warning' title='Edit'>Edit</a></td>";
              echo "</tr>";
            }
          echo "</table>";
        echo "</div>";
      echo "</div>";

/*
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
              echo "<div class='col-md-6 property-details'>";
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
                  echo "<a href='editProp.php?house_id=",$house['house_id'],"' class='btn btn-warning' title='See more'>Edit Details</a>";
                echo "</div>";
              echo "</div>";
              echo "<div class='col-md-6'>";
                echo "<a href='property.php?house_id=",$house['house_id'],"'>";
                  echo "<img src='img/$image' alt='House' class='img-thumbnail'>";
                echo "</a>";
              echo "</div>";
            echo "</div>";
            $i++;
          */
        
      }
    ?>
  </div>
</div>