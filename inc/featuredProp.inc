<?php 
  try {
    $result = $pdo->prepare('SELECT * FROM house_information WHERE available = 1 LIMIT 3');
    $result->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
?>


<div id="carouselContainer" class="container">
  <div class="page-header">
    <h1 class="text-center">Featured Properties</h1>
  </div>
  <div class="col-lg-12 carousel-col">
    <div id="carousel-example-generic" class="carousel slide" data-ride="carousel">
      <!-- Indicators -->
      <ol class="carousel-indicators">
        <li data-target="#carousel-example-generic" data-slide-to="0" class="active"></li>
        <li data-target="#carousel-example-generic" data-slide-to="1"></li>
        <li data-target="#carousel-example-generic" data-slide-to="2"></li>
      </ol>

      <!-- Wrapper for slides -->
      <div class="carousel-inner" role="listbox">
      <?php          
      $i = 0;
        foreach($result as $house){
            try {
              $imagequery = $pdo->prepare('SELECT image_path FROM house_images WHERE house_id = :house_id');
              $imagequery->bindValue(':house_id', $house['house_id']);
              $imagequery->execute();
            }
            catch (PDOException $e) {
              echo $e->getMessage();
            }
            $image = $imagequery->fetch();
            $image = $image[0];

          if ($i == 0) {
            echo "<div class='item active'>";
          } else {
            echo "<div class='item'>";
          }
            echo "<img src='img/$image' alt='House'>";
            echo "<div class='carousel-caption'>";
              echo "<h2>",$house['address'],"</h2>";
              echo "<h4>$",$house['price']," per week</h4>";
              echo "<a href='property.php?house_id=",$house['house_id'],"' class='btn btn-primary' title='See more'>More Details</a>";
              echo "<br><br>";
            echo "</div>";
          echo "</div>";
          $i++;
        }
      echo "</div>"; ?>

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
