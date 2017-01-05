<?php
  $date = date("Y-m-d");
  $id = $_GET['house_id'];

  try { //Grab all of the house information to display on page
    $query = $pdo->prepare('SELECT * '.
     'FROM house_information '.
     'WHERE house_id = :house_id ');
    $query->bindValue(':house_id', $id);
    $query->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  try { //Grab filepath to all images for the house
    $images = $pdo->prepare('SELECT image_path '.
     'FROM house_images '.
     'WHERE house_id = :house_id ');
    $images->bindValue(':house_id', $id);
    $images->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  //Count how many images need to be displayed
  $imagenumber = $images->rowCount();

  if (isset($_SESSION['email'])){
    $notLoggedIn = false;

    //Grab tenant id from database
    try {
      $getID = $pdo->prepare('SELECT tenant_id FROM tenants WHERE email = :email');
      $getID->bindValue(':email', $_SESSION['email']);
      $getID->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }

    //Set the tenant__id to a variable
    $userID = $getID->fetch();

    if (!isset($userID[0])){ //if the user is not logged in as a tenant
      $currentTenant = false;
    } else {
       $userID = $userID[0];

      if (isset($_POST['remove'])){ //if user has clicked remove from favourites
        try {
          $removeFromFavourites = $pdo->prepare('UPDATE favourites SET tenant_id=NULL, house_id=NULL WHERE tenant_id = :user AND house_id = :id');
          $removeFromFavourites->bindValue(':id', $id);
          $removeFromFavourites->bindValue(':user', $userID);
          $removeFromFavourites->execute();
        }
        catch (PDOException $e) {
          echo $e->getMessage();
        }
      }

      if (isset($_POST['add'])){ //if user has clicked add to favourites
        try {
          $removeFromFavourites = $pdo->prepare('INSERT INTO favourites (tenant_id, house_id) VALUES (:user, :id)');
          $removeFromFavourites->bindValue(':id', $id);
          $removeFromFavourites->bindValue(':user', $userID);
          $removeFromFavourites->execute();
        }
        catch (PDOException $e) {
          echo $e->getMessage();
        }
      }

      try { //See if user has favourited this property
        $favourites = $pdo->prepare('SELECT * FROM favourites WHERE house_id = :id AND tenant_id = :user');
        $favourites->bindValue(':id', $id);
        $favourites->bindValue(':user', $userID);
        $favourites->execute();
      }
      catch (PDOException $e) {
        echo $e->getMessage();
      }

        if ($favourites->rowCount() == 0){ //if no favourites set variable to false
          $favourite = false;
        } else {
          $favourite = true;
        }

      try { //find is user is the current tenant
        $currentTenants = $pdo->prepare('SELECT * FROM renting_tenants WHERE house_id = :house_id AND tenant_id = :user ');
        $currentTenants->bindValue(':house_id', $id);
        $currentTenants->bindValue(':user', $userID);
        $currentTenants->execute();
      }
      catch (PDOException $e) {
        echo $e->getMessage();
      }

      if ($currentTenants->rowCount() == 0){ //if no currentTenants set variable to false
        $currentTenant = false;
      } else {
        $currentTenant = true;
      }

      if (isset($_POST['bookViewing'])){
        $staff_id = $pdo->prepare('SELECT staff_id FROM houses WHERE house_id = :house_id');
        $staff_id->bindValue(':house_id', $id);
        $staff_id->execute();

        $staff_id = $staff_id->fetch();
        $staff_id = $staff_id[0];

        $insertBooking = $pdo->prepare('INSERT INTO viewing_bookings (staff_id, tenant_id, house_id, date, time) VALUES (:staff_id, :user, :id, :date, :time)');
        $insertBooking->bindValue(':id', $id);
        $insertBooking->bindValue(':user', $userID);
        $insertBooking->bindValue(':staff_id', $staff_id);
        $insertBooking->bindValue(':date', $_POST['viewingDay']);
        $insertBooking->bindValue(':time', $_POST['viewingTime']);
        $insertBooking->execute();
      }
      
      try { //find if user has a booking
        $hasBooking = $pdo->prepare('SELECT * FROM viewing_bookings WHERE house_id = :house_id AND tenant_id = :user');
        $hasBooking->bindValue(':house_id', $id);
        $hasBooking->bindValue(':user', $userID);
        $hasBooking->execute();
      } catch (PDOException $e) {
        echo $e->getMessage();
      }

      if ($hasBooking->rowCount()){
        $hasBooking = true;
      } else {
        $hasBooking = false;
      }

    }

    if (isset($_POST['reviewSubmit'])){
      try{
        $insertReview = $pdo->prepare('INSERT INTO reviews (tenant_id, house_id, rating, description, date) VALUES (:user, :id, :rating, :description, :date)');
        $insertReview->bindValue(':id', $id);
        $insertReview->bindValue(':user', $userID);
        $insertReview->bindValue(':rating', $_POST['rating']);
        $insertReview->bindValue(':description', $_POST['review']);
        $insertReview->bindValue(':date', $date);
        $insertReview->execute();
      }
      catch (PDOException $e) {
        echo $e->getMessage();
      }
    }

    try { //Check if already reviewed
      $alreadyReviewed = $pdo->prepare('SELECT * FROM reviews WHERE house_id = :house_id AND tenant_id = :user');
      $alreadyReviewed->bindValue(':house_id', $id);
      $alreadyReviewed->bindValue(':user', $userID);
      $alreadyReviewed->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }

  } else {
    $notLoggedIn = true;
  }

  try { //Grab all reviews for the house
    $reviews = $pdo->prepare('SELECT * FROM reviews WHERE house_id = :house_id');
    $reviews->bindValue(':house_id', $id);
    $reviews->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  try { //Grab owner's contact details
    $ownerDetails = $pdo->prepare('SELECT first_name, contact_number FROM houses JOIN owners ON houses.owner_id = owners.owner_id JOIN user_information ON owners.email = user_information.email WHERE house_id = :house_id');
    $ownerDetails->bindValue(':house_id', $id);
    $ownerDetails->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
  foreach ($ownerDetails as $owner){}

  try { //Grab viewing times
    $viewingTimes = $pdo->prepare('SELECT * FROM viewing_times WHERE house_id = :house_id');
    $viewingTimes->bindValue(':house_id', $id);
    $viewingTimes->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

?>

<div class="container content-padding">
  <?php
  foreach($query as $detail) {
    if ($detail['available'] == 1){
    echo "<div>";
    echo "<div class='col-lg-4 text-center'>";
          echo "<h1>",$detail['address'],"</h1>";
          echo "<img src='img/bed.png' alt='Beds'>";
          echo "<span class='property-details'>",$detail['bed_number'],"</span>";
          echo "<img src='img/bath.png' alt='baths'>";
          echo "<span class='property-details'>",$detail['bath_number'],"</span>";
          echo "<img src='img/car.png' alt='cars'>";
          echo "<span class='property-details'>",$detail['carport_number'],"</span>";
          echo "<br><br>";
          if (!$isOwner && !$isStaff && !$notLoggedIn && !$isAdmin){ //if user is not a staff member and not an owner display the favourite button
            if ($favourite == true) {
              echo "<form method='post' action='property.php?house_id=",$id,"'>";
             /* echo "<span class='glyphicon glyphicon-star' aria-hidden='true'></span>"; */
              echo "<input class='btn btn-danger' type='submit' name='remove' value='Remove from Favourites'>";
              echo "</form>";
            } else {
              echo "<form method='post' action='property.php?house_id=",$id,"'>";
            /*  echo "<span class='glyphicon glyphicon-star-empty' aria-hidden='true'></span>"; */
              echo "<input class='btn btn-success' type='submit' name='add' value='Add to Favourites'>";
              echo "</form>";
            }
          }
          echo "<p class='text-left'>",$detail['house_description'],"</p>";

      ?>
    </div>
    <div class="col-lg-8 carousel-col">
      <div id="carousel-example-generic" class="carousel slide" data-ride="carousel">
        <ol class="carousel-indicators">
        <?php
          for ($i = 0; $i < $imagenumber; $i++){
            if ($i == 0) {
              echo "<li data-target='#carousel-example-generic' data-slide-to='",$i,"' class='active'></li>";
            } else {
              echo "<li data-target='#carousel-example-generic' data-slide-to='",$i,"'></li>";
            }
          }
        echo "</ol>";

        echo "<div class='carousel-inner' role='listbox'>";

        //$curr = $image[0];
        $image = $images->fetch();
        for ($i = 0; $i < $imagenumber; $i++) {
          $curr = $image[0];
          if ($i == 0) {
            echo "<div class='item active'>";
          } else {
            echo "<div class='item'>";
          }
          echo "<img src='img/$curr' alt='House'>";
          echo "</div>";
          $image = $images->fetch();
        }
        echo "</div>";
     ?>
        <!-- Controls -->
        <a class="left carousel-control" href="#carousel-example-generic" role="button" data-slide="prev">
          <span class="glyphicon glyphicon-chevron-left" aria-hidden="true"></span>
          <span class="sr-only">Previous</span>
        </a>
        <a class="right carousel-control" href="#carousel-example-generic" role="button" data-slide="next">
          <span class="glyphicon glyphicon-chevron-right" aria-hidden="true"></span>
          <span class="sr-only">Next</span>
        </a>
      </div>
    </div>
  </div>
</div>
<div class="container content-padding">
  <div class='col-lg-4'>
  <?php
    echo "<h3>Rental Details</h3>";
    echo "<hr class='separator'>";
    echo "<span>Price:</span><h3>$",$detail['price'],"/week</h3>";
    if ($detail['furnished'] ==  1){
      $furnishing = 'Yes';
    } else {
      $furnishing = 'No';
    }
    echo "<span>Furnished?</span><h3>",$furnishing,"</h3>";
    echo "<span>Property Type:</span><h3>",$detail['type'],"</h3>";
    echo "<span>Contact:</span><h3>",$owner['first_name']," - call 0",$owner['contact_number'],"</h3>";

    $views = $detail['views'] + 1;

    try{
      $removeFromFavourites = $pdo->prepare('UPDATE house_information SET views = :views WHERE house_id = :id');
      $removeFromFavourites->bindValue(':id', $id);
      $removeFromFavourites->bindValue(':views', $views);
      $removeFromFavourites->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }


    echo "<span>Page Views:</span><h3>",$views,"</h3>";

  ?>
  </div> <!-- /////////////////////////////////////////////////////////////////// -->
  <div class="col-lg-4">
    <h3>Book Property Viewing</h3>
    <hr class="separator">
    <?php 
    foreach ($viewingTimes as $viewingTime){
      $nextDay = "next ".$viewingTime['day'];

      $nextDate = date('Y-m-d', strtotime($nextDay));
      $displayDate = date('d/m/y', strtotime($nextDay));
      $time  = date("g:i a", strtotime($viewingTime['time']));
      echo "<h4>",$viewingTime['day']." (".$displayDate,") ",$time,"</h4>";
      echo "<form class='bookingForm' action='property.php?house_id=",$id,"' method='post'>";
        echo "<input type='hidden' name='viewingDay' value='",$nextDate,"'>";
        echo "<input type='hidden' name='viewingTime' value='",$viewingTime['time'],"'>";
        if (!$notLoggedIn){
          if(!$isOwner && !$isStaff && !$notLoggedIn && !$isAdmin){
            if(!$hasBooking){
              echo "<button type='submit' class='btn btn-primary inline-button' title='Book now' name='bookViewing'>Book now</button>";
            } else {
              echo "<button type='submit' class='btn btn-danger inline-button' disabled='disabled' title='Book now' name='bookViewing'>Book now</button>";
            }
          }
        } else {
          echo "<button type='submit' class='btn btn-danger inline-button' disabled='disabled' title='Book now' name='bookViewing'>Book now</button>";
        }
      echo "</form>";
    }
    ?>
    <br><br>
    <h3>Property Reviews</h3>
    <hr class="separator">
    <?php
    echo "<div class='row text-center'>";
      if ($reviews->rowCount()){
      foreach ($reviews as $review) {}
        for ($i = 0; $i < $review['rating']; $i++){
          echo "<span class='glyphicon glyphicon-star' aria-hidden='true'></span>";
        }
        for ($i = $review['rating']; $i < 5; $i++){
          echo "<span class='glyphicon glyphicon-star-empty' aria-hidden='true'></span>";
        }
        echo "<span>    ",$review['date'],"</span>";
        echo "</div>";
        echo "<div class='row text-center'>";
        echo "<span>",$review['description'],"</span>";
        echo "</div>";
      } else {
        echo "<span>No reviews</span>";
        echo "</div>";
      }
      echo "<br>";
      if (!$notLoggedIn){
        echo "<div class='row text-center'>";
        if ($currentTenant){
          if (!$alreadyReviewed->rowCount()){
            echo "<a id='reviewButton' href='#' class='btn btn-success inline-button' title='Review Property'>Add Review</a>";
          } else {
            echo "<a href='#' class='btn btn-warning inline-button' disabled='disabled' title='Review Property'>Add Review</a>";
          }
        } else {
          echo "<a href='#' class='btn btn-warning inline-button' disabled='disabled' title='Review Property'>Add Review</a>";
        }
        echo "</div>";
      }
      echo '</div>';
       echo '<div class="col-lg-4">';
        echo '<div class="map-placeholder">';
          echo '<div id="mapHolder">';
            echo '<div id="map-canvas"></div>';
            echo '<script>createMap();</script>';

            echo "<script>addMarker(",$detail['house_id'],", '".$detail['address']."', ",$detail['longitude'],", ",$detail['latitude'],");</script>";
          echo '</div>';
        echo '</div>';
      echo '</div>';
    } else {
      echo "<div class='col-lg-12'>";
      echo "<h2>This property is currently unavailable</h2>";
      echo "</div>";
    }
  }?>

    <!-- Review Modal -->
  <div class="modal fade" id="reviewModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
          <h4 class="modal-title" id="myModalLabel">Review</h4>
        </div>
        <div class="account-wall">
          <!-- Review Form -->
          <?php echo "<form class='form-review' action='property.php?house_id=",$id,"' method='post'>"; ?>
            <table>
              <tr>
                <td>Review:</td>
                <td><textarea required name="review"></textarea></td>
              </tr>
              <tr>
                <td>Rating:</td>
                <td><select name="rating" class="form-control">
                 <?php
                 for ($i=1; $i <= 5; $i++){
                    echo "<option value=",$i,">",$i,"</option>";
                 }
                 ?>
                </select>
              </td>
            </tr>
          </table>
          <br>
            <button type="submit" name="reviewSubmit" class="btn btn-lg btn-primary center-button">Submit Review</button>
          </form>
        </div>
      </div>
    </div>
  </div>

  <script>
    $("#reviewButton").click(function(){
      $('#reviewModal').modal('show');
    });
    </script>

</div>
