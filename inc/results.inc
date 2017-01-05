<script src="js/sortResults.js"></script>
<div class="container">
  <div id="sortSelection" style="display:none">1</div>
  <div class="page-header">
    <h1 class="text-center">Results</h1>
    <div id="sort" class="dropdown">
      <button class="btn btn-primary dropdown-toggle" type="button" data-toggle="dropdown">Sort Results By
      <span class="caret"></span></button>
      <ul class="dropdown-menu" role="menu">
        <li><a href="#" onclick="sortResults(1);">Address: A &#x2192; Z</a></li>
        <li><a href="#" onclick="sortResults(2);">Address: Z &#x2192; A</a></li>
        <li class="divider"></li>
        <li><a href="#" onclick="sortResults(3);">Price: Highest &#x2192; Lowest</a></li>
        <li><a href="#" onclick="sortResults(4);">Price: Lowest &#x2192; Highest</a></li>
        <li class="divider"></li>
        <li><a href="#" onclick="sortResults(5);">Beds: Most &#x2192; Least</a></li>
        <li><a href="#" onclick="sortResults(6);">Beds: Least &#x2192; Most</a></li>
        <li class="divider"></li>
        <li><a href="#" onclick="sortResults(7);">Baths: Most &#x2192; Least</a></li>
        <li><a href="#" onclick="sortResults(8);">Baths: Least &#x2192; Most</a></li>
        <li class="divider"></li>
        <li><a href="#" onclick="sortResults(9);">Car Ports: Most &#x2192; Least</a></li>
        <li><a href="#" onclick="sortResults(10);">Car Ports: Least &#x2192; Most</a></li>
      </ul>
    </div>
  </div>
  <div class="container">
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
    $getAgentEmail = $pdo->prepare('SELECT email FROM user_information WHERE first_name LIKE :name');
    $getAgentEmail->bindValue(':name', '%'.$_POST['agent'].'%');
    $getAgentEmail->execute();
    $email = $getAgentEmail->fetch();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  try {
    $getAgentId = $pdo->prepare('SELECT staff_id FROM staff_members WHERE email LIKE :agentEmail');
    $getAgentId->bindValue(':agentEmail', '%'.$email[0].'%');
    $getAgentId->execute();
    $id = $getAgentId->fetch();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  try {
    $getHouseId = $pdo->prepare('SELECT house_id FROM houses WHERE staff_id LIKE :agentId');
    $getHouseId->bindValue(':agentId', '%'.$id[0].'%');
    $getHouseId->execute();
    $houseIds = $getHouseId->fetchAll(PDO::FETCH_ASSOC);
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $order = 1;
  $ASC = true;

  try {
    if ($_POST['price'] == "") {
      if ($ASC) {
        $result = $pdo->prepare('SELECT * FROM house_information WHERE address LIKE :search AND bed_number LIKE :beds AND bath_number LIKE :baths AND carport_number LIKE :cars AND furnished LIKE :furnished AND available = 1 ORDER BY :order ASC');
      } else {
        $result = $pdo->prepare('SELECT * FROM house_information WHERE address LIKE :search AND bed_number LIKE :beds AND bath_number LIKE :baths AND carport_number LIKE :cars AND furnished LIKE :furnished AND available = 1 ORDER BY :order DESC');
      }
    } else {
      if ($ASC) {
        $result = $pdo->prepare('SELECT * FROM house_information WHERE price <= :price AND address LIKE :search AND bed_number LIKE :beds AND bath_number LIKE :baths AND carport_number LIKE :cars AND furnished LIKE :furnished AND available = 1 ORDER BY :order ASC');
      } else {
        $result = $pdo->prepare('SELECT * FROM house_information WHERE price <= :price AND address LIKE :search AND bed_number LIKE :beds AND bath_number LIKE :baths AND carport_number LIKE :cars AND furnished LIKE :furnished AND available = 1 ORDER BY :order DESC');
      }
      $result->bindValue(':price', $_POST['price']);
    }
    $result->bindValue(':search','%'.$_POST['search-field'].'%');
    $result->bindValue(':beds', '%'.$_POST['beds'].'%');
    $result->bindValue(':baths', '%'.$_POST['baths'].'%');
    $result->bindValue(':cars', '%'.$_POST['cars'].'%');
    $result->bindValue(':furnished', '%'.$_POST['furnished'].'%');
    $result->bindParam(':order', $order, PDO::PARAM_INT);
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  //Note the latitude and longitude are around the wrong way in the database.
  //$usersLat = 153.0244888;
  //$usersLong = -27.4712909;
  $usersLat = $_POST['long'];
  //echo "<p>My latitude: ",$usersLat,"</p>";
  $usersLong = $_POST['lat'];
  //echo "<p>My longitude: ".$usersLong."</p>";

  if ($result->rowCount() == 0) {
    echo "<h2>No results</h2>";
  } else {
    echo "<div id='mapHolder'>";
      echo "<div id='map-canvas'></div>";
      echo "<script>createMap()</script>";
    echo "<br></div>";
    echo "<div id='resultsContainer'>";
    postResults($result, $usersLat, $usersLong, $pdo);
  }
  if (isset($_GET['sortSelection'])) {
    sortResults();
  }

  function postResults($result, $usersLat, $usersLong, $pdo) {
    $i = 0;

    foreach($result as $house) {
      if (distance($usersLat, $usersLong, $house['latitude'], $house['longitude']) <= $_POST['distance']) {
        if ($_POST['agent'] == "" || $house["house_id"] == $houseIds[$i]["house_id"]) {
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

          echo "<div id='results' class='row'>";
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
    }
  }
?>
  </div>
  </div>
</div>
<div class="container">
  <div class="page-header">
    <h1 class="text-center">Not what you were looking for?</h1>
  </div>
  <div class="col-lg-12  search-again">
    <a href="index.php" class="btn btn-primary" title="See more">Search again</a>  </div>
    <br><br><br><br>
<!-- /container -->
</div>
