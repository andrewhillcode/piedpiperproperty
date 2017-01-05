<?php
 $id = $_GET['house_id'];

 if (isset($_GET['remove'])){
     $username = 'piperadmin';
  $password = 'password';
  $adminPDO = new PDO('mysql:host=localhost;dbname=ifb299', $username, $password);
  $adminPDO->setAttribute(PDO::ATTR_ERRMODE, PDO::ERRMODE_EXCEPTION);

    $sql = "DELETE FROM house_images WHERE house_id = :house_id AND image_path = :image";
    $stmt = $adminPDO->prepare($sql);
    $stmt->bindValue(':house_id', $_GET['house_id'], PDO::PARAM_INT);
    $stmt->bindValue(':image', $_GET['remove'], PDO::PARAM_INT);    
    $stmt->execute();

    unlink("img/".$_GET['remove']);


 }

 if (isset($_POST['submit'])){

    try { //Grab filepath to all images for the house
    $images = $pdo->prepare('SELECT AUTO_INCREMENT FROM INFORMATION_SCHEMA.TABLES WHERE TABLE_SCHEMA = :dbName AND   TABLE_NAME = :tableName');
    $images->bindValue(':dbName', 'ifb299');
    $images->bindValue(':tableName', 'house_images');
    $images->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $imagenumber = $images->fetch();
  $imagenumber = $imagenumber[0];

    $newfilename = 'prop'.$imagenumber.".png";
  $target_dir = "img";  

  move_uploaded_file($_FILES["file"]["tmp_name"], "$target_dir/$newfilename");


    try {
       if ($_FILES['file']['error'] == UPLOAD_ERR_OK){
      $insertToHouseImages = $pdo->prepare('INSERT INTO house_images (house_id, image_path) VALUES (:house_id, :file)');
      $insertToHouseImages->bindValue(':house_id', $id);
      $insertToHouseImages->bindValue(':file', $newfilename);
      $insertToHouseImages->execute();
      }

      $updateInfo = $pdo->prepare('UPDATE house_information SET bed_number = :beds, bath_number = :baths, carport_number = :cars, price = :price, furnished = :furnished, house_description = :description, available = :available WHERE house_id = :house_id');
      $updateInfo->bindValue(':beds', $_POST['beds']);
      $updateInfo->bindValue(':baths', $_POST['baths']);
      $updateInfo->bindValue(':cars', $_POST['cars']);
      $updateInfo->bindValue(':price', $_POST['price']);
      $updateInfo->bindValue(':furnished', $_POST['furnished']);
      $updateInfo->bindValue(':description', $_POST['houseDescription']);
      $updateInfo->bindValue(':available', $_POST['available']);
      $updateInfo->bindValue(':house_id', $id);
      $updateInfo->execute();

      $updateStaff = $pdo->prepare('UPDATE houses SET staff_id = :staff_id WHERE house_id = :house_id');
      $updateStaff->bindValue(':staff_id', $_POST['staff_id']);
      $updateStaff->bindValue(':house_id', $id);
      $updateStaff->execute();

      $updateTimes = $pdo->prepare('UPDATE viewing_times SET day = :day, time = :time WHERE house_id = :house_id');
      $updateTimes->bindValue(':day', $_POST['viewingDay']);
      $updateTimes->bindValue(':time', $_POST['viewingTime']);      
      $updateTimes->bindValue(':house_id', $id);
      $updateTimes->execute();
    }
    catch (PDOException $e) {
      echo $e->getMessage();
    }
  }

  try {
    $query = $pdo->prepare('SELECT * '.
     'FROM house_information '.
     'JOIN houses ON house_information.house_id = houses.house_id '.
     'WHERE houses.house_id = :house_id ');
    $query->bindValue(':house_id', $id);
    $query->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  try {
    $images = $pdo->prepare('SELECT image_path '.
     'FROM house_images '.
     'WHERE house_id = :house_id ');
    $images->bindValue(':house_id', $id);
    $images->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $imagenumber = $images->rowCount();


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
  if (!isset($userID[0])){
 
  } else {
     $userID = $userID[0]; 

  }

  //grab list of staff
  try {
    $staffList = $pdo->prepare('SELECT first_name, last_name, staff_id FROM staff_members, user_information WHERE staff_members.email = user_information.email');
    $staffList->bindValue(':email', $_SESSION['email']);
    $staffList->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

    //grab viewing times
  try {
    $viewingTimes = $pdo->prepare('SELECT * FROM viewing_times WHERE house_id = :house_id');
    $viewingTimes->bindValue(':house_id', $id);
    $viewingTimes->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }

  $viewingTimes = $viewingTimes->fetch();
  $viewingDay = $viewingTimes[1];
  $viewingTime = $viewingTimes[2];

  //grab images
  try {
    $images = $pdo->prepare('SELECT * FROM house_images WHERE house_id = :house_id');
    $images->bindValue(':house_id', $id);
    $images->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
  }
?>



<div id="writeToPage"></div>

<div class="container content-padding">
  <div>
    <div class="col-lg-12 text-center">
      <h1>Editing Property</h1>
       <form name="updatePropDetails" action='<?php echo "editPropAdmin.php?house_id=$id" ?>' method="post"  enctype="multipart/form-data">
      <?php
        foreach($query as $detail) {
          ?>
 <!--  ///////////////////////////////////////////////////////////////////////////// -->   
         <table>
            <tr>
              <td>
                <span>Address:</span>
              </td>
              <td>
                <span><?php echo $detail['address']; ?></spam>
              </td>
            </tr>
            <tr>
              <td>
                <img src='img/bed.png' alt='Beds'>
              </td>
              <td>
                <input required class="inlineInput form-control" type="number" min="1" max="10" name="beds" placeholder="Beds" value="<?php echo $detail['bed_number'] ?>"></input>
              </td>
            </tr>
            <tr>
              <td>
                <img src='img/bath.png' alt='baths'>
              </td>
              <td>
                <input required class="inlineInput form-control" type="number" min="1" max="10" name="baths" placeholder="Baths" value="<?php echo $detail['bath_number'] ?>"></input>
              </td>
            </tr>
            <tr>
              <td>
                <img src='img/car.png' alt='cars'>
              </td>
              <td>
                <input required class="inlineInput form-control" type="number" min="0" max="10" name="cars" placeholder="Carports" value="<?php echo $detail['carport_number'] ?>"></input>
              </td>
            </tr>           
            <tr> 
              <td>
                <span>Staff:</span>
              </td>
              <td>
                <select name="staff_id" class="form-control ">
                   <?php
                    $i = $detail['staff_id'];
                    foreach ($staffList as $staff){
                      if ($i == $staff['staff_id']){
                        echo "<option selected='selected' value=",$staff['staff_id'],">",$staff['first_name']," ",$staff['last_name'],"</option>";
                      } else {
                        echo "<option value=",$staff['staff_id'],">",$staff['first_name']," ",$staff['last_name'],"</option>";
                      }
                    }
                  ?>
                </select> 
              </td> 
            </tr>
            <tr>
              <td>
                <span>Description:</span>
              </td>
              <td>
                <input required class="inlineInput form-control" type="text" name="houseDescription" placeholder="Description" value="<?php echo $detail['house_description'] ?>"></input>
              </td>
            </tr>              
            <tr>
              <td>
                <span>Price per week:</span>
              </td>
              <td>
                <input required class="inlineInput form-control" type="number" min="1" max="10000" name="price" placeholder="Price per week" value="<?php echo $detail['price'] ?>">
              </td>
            </tr>  
            <tr>
              <td>
                <span>Furnished:</span>
              </td>
              <td>
                <select name="furnished" class="form-control ">
                   <?php 
                   if ($detail['furnished'] == 1){
                    echo '<option selected="selected" value="1">Yes</option>';
                    echo '<option value="0">No</option>';
                   } else {
                    echo '<option value="1">Yes</option>';
                    echo '<option selected="selected" value="0">No</option>';
                  }
                  ?>
                </select>
              </td>
            </tr>              
            <tr>
              <td>
                <span>House type:</span>
              </td>
              <td>
                <span><?php echo $detail['type']; ?></spam>
              </td>
            </tr> 
            <tr>
              <td>
                <span>Add Image:</span>
              </td>
              <td>
                <input class="form-control" type="file" name="file">
              </td>
            </tr>                
            <tr>
            <tr>
              <td>
                <span>Viewing Time</span>
              </td>
              <td> 
                <select name="viewingDay" class="form-control viewing">
                  <option <?php if ($viewingDay == 'Monday') echo "selected='selected'"; ?> value="Monday">Monday</option>
                  <option <?php if ($viewingDay == 'Tuesday') echo "selected='selected'"; ?> value="Tuesday">Tuesday</option>
                  <option <?php if ($viewingDay == 'Wednesday') echo "selected='selected'"; ?> value="Wednesday">Wednesday</option>
                  <option <?php if ($viewingDay == 'Thursday') echo "selected='selected'"; ?> value="Thursday">Thursday</option>
                  <option <?php if ($viewingDay == 'Friday') echo "selected='selected'"; ?> value="Friday">Friday</option>
                  <option <?php if ($viewingDay == 'Saturday') echo "selected='selected'"; ?> value="Saturday">Saturday</option>
                  <option <?php if ($viewingDay == 'Sunday') echo "selected='selected'"; ?> value="Sunday">Sunday</option>
                </select>
                <select name="viewingTime" class="form-control viewing">
                  <option <?php if ($viewingTime == '10:00:00') echo "selected='selected'"; ?> value="10:00">10:00am</option>
                  <option <?php if ($viewingTime == '10:30:00') echo "selected='selected'"; ?> value="10:30">10:30am</option>
                  <option <?php if ($viewingTime == '11:00:00') echo "selected='selected'"; ?> value="11:00">11:00am</option>
                  <option <?php if ($viewingTime == '11:30:00') echo "selected='selected'"; ?> value="11:30">11:30am</option>
                  <option <?php if ($viewingTime == '12:00:00') echo "selected='selected'"; ?> value="12:00">12:00pm</option>
                  <option <?php if ($viewingTime == '12:30:00') echo "selected='selected'"; ?> value="12:30">12:30pm</option>
                  <option <?php if ($viewingTime == '13:00:00') echo "selected='selected'"; ?> value="13:00">1:00pm</option>
                  <option <?php if ($viewingTime == '13:30:00') echo "selected='selected'"; ?> value="13:30">1:30pm</option>
                  <option <?php if ($viewingTime == '14:00:00') echo "selected='selected'"; ?> value="14:00">2:00pm</option>
                  <option <?php if ($viewingTime == '14:30:00') echo "selected='selected'"; ?> value="14:30">2:30pm</option>
                  <option <?php if ($viewingTime == '15:00:00') echo "selected='selected'"; ?> value="15:00">3:00pm</option>
                </select>
              </td>
            </tr>         
            <tr>  
              <td>
                <span>List on website?</span>
              </td>
              <td>
                <select name="available" class="form-control ">
                   <?php 
                   if ($detail['available'] == 1){
                    echo '<option selected="selected" value="1">Yes</option>';
                    echo '<option value="0">No</option>';
                   } else {
                    echo '<option value="1">Yes</option>';
                    echo '<option selected="selected" value="0">No</option>';
                  }
                  ?>
                </select>
              </td>
            </tr>            
          </table>      
          <input type="submit" name="submit" class="btn btn-success profileForm inlineInput" value="Confirm">
          <a name="cancel" class="btn btn-danger profileForm inlineInput" href="manage.php">Cancel</a>
        </form>
          <?php
        }
      ?>

      <h1>Remove Images</h1>
       <table class='removeButton'>
        <?php 
          foreach ($images as $image) {
            $img = $image['image_path'];
          echo "<tr>";
            echo "<td>";
              echo "<img src='img/$img' alt='House' class='img-thumbnail'>";
            echo "</td>"; 
            echo "<td>"; ?>
              <a name="cancel" class="btn btn-danger profileForm inlineInput" href='<?php echo "editPropAdmin.php?house_id=$id&remove=$img" ?>'>Remove Image</a> 
     <?php  echo "</td>";
          echo "</tr>";
        } ?>
      </table>
      <br>
    </div>
  </div>
</div>