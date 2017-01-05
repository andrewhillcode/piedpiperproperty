<?php
  function distance($lat1, $lon1, $lat2, $lon2) {
    $R = 6371; // km
    $lat1 = floatval($lat1);
    $lon1 = floatval($lon1);
    $lat2 = floatval($lat2);
    $lon2 = floatval($lon2);
    $dLat = deg2rad($lat2-$lat1);
    $dLon = deg2rad($lon2-$lon1);
    $lat1 = deg2rad($lat1);
    $lat2 = deg2rad($lat2);
    $a = sin($dLat/2) * sin($dLat/2) +
        sin($dLon/2) * sin($dLon/2) * cos($lat1) * cos($lat2);
    $c = 2 * atan2(sqrt($a), sqrt(1-$a));
    $d = $R * $c;
    return $d;
  }

  try {
    $result = $pdo->prepare('SELECT * FROM house_information WHERE available = 1');
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
?>

<div class="container">
  <div class="page-header">
    <h1 class="text-center">Results</h1>
  </div>
  <div class="container">
    <?php
      $usersLat = 153.0244888;
      $usersLong = -27.4712909;
      //$usersLat = $_POST['lat'];
      //$usersLong = $_POST['long'];

      $i = 0;
      if ($result->rowCount() == 0) {
        echo "<h2>No results</h2>";
      } else {
        echo "<div id='mapHolder'>";
        echo "<div id='map-canvas'></div>";
        echo "<script>createMap()</script>";
        echo "<br></div>";

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
                echo "<h3>",number_format((float)distance($usersLat, $usersLong, $house['latitude'], $house['longitude']), 1),"km away</h3>";
                echo "<a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='See more'>More Details</a>";
              echo "</div>";
            echo "</div>";
            echo "<div class='col-md-6 result-thumbnail'>";
              echo "<a href='property.php?house_id=",$house['house_id'],"'>";
                echo "<img src='img/$image' alt='House' class='img-thumbnail'>";
              echo "</a>";
            echo "</div>";
            echo "<script>addMarker(",$house['house_id'],", '".$house['address']."', ",$house['longitude'],", ",$house['latitude'],");</script>";
          echo "</div>";
          $i++;
        }
      }
    ?>
  </div>
</div>

<div class="container">
  <div class="page-header">
    <h1 class="text-center">Want to refine your search?</h1>
  </div>
  <div class="col-lg-12  search-again">
    <a href="index.php" class="btn btn-primary" title="See more">Refine search</a>  </div>
    <br><br><br><br>
<!-- /container -->
</div>
