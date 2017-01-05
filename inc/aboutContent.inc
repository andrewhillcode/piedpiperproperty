<?php 
  $date = date("Y-m-d");

 if (isset($_SESSION['email'])){
    $notLoggedIn = false;  

    try { //determine if user is a tenant
      $findTenant = $pdo->prepare('SELECT * FROM tenants WHERE email = :email');
      $findTenant->bindValue(':email', $_SESSION['email']);
      $findTenant->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }

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
    $userID = $userID[0];


    if ($findTenant->rowCount() == 0){ //if not a tenant set variable to false
      $isTenant = false;
    } else {
      $isTenant = true;
    }

     if (isset($_POST['testimonySubmit'])){
        try{
          $insertReview = $pdo->prepare('INSERT INTO testimonies (tenant_id, rating, description, date) VALUES (:user, :rating, :description, :date)');
          $insertReview->bindValue(':user', $userID);
          $insertReview->bindValue(':rating', $_POST['rating']);
          $insertReview->bindValue(':description', $_POST['testimony']);
          $insertReview->bindValue(':date', $date);
          $insertReview->execute();
        }
        catch (PDOException $e) {
          echo $e->getMessage();
        }
      }

    try { //Check if already reviewed
      $alreadyReviewed = $pdo->prepare('SELECT * FROM testimonies WHERE tenant_id = :user');
      $alreadyReviewed->bindValue(':user', $userID);
      $alreadyReviewed->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }

  } else {
    $notLoggedIn = true; 
  }

   try { //grab testimonies
      $testimonies = $pdo->prepare('SELECT * FROM testimonies ORDER BY date DESC LIMIT 3');
      $testimonies->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }

?>

<div class="container">
  <div class="container top-space">
    <div class="row">
      <div class="col-sm-8">
        <h1 class="text-center">About us</h1>
        <p>Pied Piper Property is the result of hard word and dedication from the founder, Mr. David. For 20 years he has managed his own real estate company through websites like Gumtree. His attention to detail and perseverance is key to the success of his business Pied Piper Property.</p>
        <h1 class="text-center">Testimonies</h1>
       
        <?php
        
      
          foreach ($testimonies as $testimony) {
            echo "<div class='row text-center'>";
              $rating = $testimony['rating'];
              for ($i = 0; $i < $rating; $i++){
                echo "<span class='glyphicon glyphicon-star' aria-hidden='true'></span>";
              }
              for ($i = $rating; $i < 5; $i++){
                echo "<span class='glyphicon glyphicon-star-empty' aria-hidden='true'></span>";
              }
                echo "<span>    ",$testimony['date'],"</span>";
            echo "</div>";
            echo "<div class='row text-center'>";
              echo "<span>",$testimony['description'],"</span>";
            echo "</div>";

         echo "<br>";
        }
          if (!$notLoggedIn){ 
            echo "<div class='row text-center'>";
            if ($isTenant){
              if (!$alreadyReviewed->rowCount()){
                echo "<a id='testimonyButton' href='#' class='btn btn-success inline-button' title='Review Property'>Add Review</a>";
              } else {
                echo "<a href='#' class='btn btn-warning inline-button' disabled='disabled' title='Review Property'>Add Review</a>";
              }
            } else {
              echo "<a href='#' class='btn btn-warning inline-button' disabled='disabled' title='addTestimony'>Add Testimony</a>";
            }
            echo "</div>";
          }
        ?>

        <h1 class="text-center">Contact</h1>
        <div class="contact-details">
          <p>contactus@piedpiper.com.au</p>
          <p>Ph: 3333 3333</p>
          <p>Mob: 04 1234 5678</p>
        </div>
      </div>
      <div class="col-sm-4">
        <img src="img/david.png" alt="House 1" class="img-thumbnail" >
      </div>
    </div>
  </div>

      <!-- testimony Modal -->
  <div class="modal fade" id="testimonyModal" tabindex="-1" role="dialog" aria-labelledby="myModalLabel">
    <div class="modal-dialog" role="document">
      <div class="modal-content">
        <div class="modal-header">
          <button type="button" class="close" data-dismiss="modal" aria-label="Close"><span aria-hidden="true">&times;</span></button>
          <h4 class="modal-title" id="myModalLabel">Testimony</h4>
        </div>
        <div class="account-wall">
          <!-- testimony Form -->
          <?php echo "<form class='form-testimony' action='about.php' method='post'>"; ?>
            <textarea required name="testimony"></textarea>
            <select name="rating" class="form-control">
             <?php 
             for ($i=1; $i <= 5; $i++){
                echo "<option value=",$i,">",$i,"</option>";                
             }  
             ?>
          </select>
            <button type="submit" name="testimonySubmit" class="btn btn-lg btn-primary btn-block">Submit Testimony</button>
          </form>
        </div>
      </div>
    </div>
  </div>

  <script>
    $("#testimonyButton").click(function(){
      $('#testimonyModal').modal('show');
    });
    </script>
</div>