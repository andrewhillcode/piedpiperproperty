<?php

//grab list of owners
  try {
    $ownerList = $pdo->prepare('SELECT first_name, last_name, owner_id FROM owners, user_information WHERE owners.email = user_information.email');
    $ownerList->bindValue(':email', $_SESSION['email']);
    $ownerList->execute();
  }
  catch (PDOException $e) {
    echo $e->getMessage();
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

?>

<div id="writeToPage"></div>

<div class="container content-padding">
  <div>
    <div class="col-lg-12 text-center">
      <h1>Add new property</h1>
      <form name="addProperty" action='addProperty.php' method="post" enctype="multipart/form-data">
        <table>
            <tr>
              <td>
                <span>Address:</span>
              </td>
              <td>
                <input required class="inlineInput form-control" type="text" name="address" placeholder="Address" value=""></input>
              </td>
            </tr>
            <tr>
              <td>
                <img src='img/bed.png' alt='Beds'>
              </td>
              <td>
                <input required class="inlineInput form-control" type="number" min="1" max="10" name="beds" placeholder="Beds" value=""></input>
              </td>
            </tr>
            <tr>
              <td>
                <img src='img/bath.png' alt='baths'>
              </td>
              <td>
                <input required class="inlineInput form-control " type="number" min="1" max="10" name="baths" placeholder="Baths" value=""></input>
              </td>
            </tr>
            <tr>
              <td>
                <img src='img/car.png' alt='cars'>
              </td>
              <td>
                <input required class="inlineInput form-control" type="number" min="0" max="10" name="cars" placeholder="Carports" value=""></input>
              </td>
            </tr>           
            <tr>
              <td>
               <span>Owner:</span>
              </td>
              <td>
                <select name="owner_id" class="form-control ">
                <?php
                  $i = 0;
                  foreach ($ownerList as $owner){
                    if ($i == 0){
                      echo "<option selected='selected' value=",$owner['owner_id'],">",$owner['first_name']," ",$owner['last_name'],"</option>";
                    } else {
                      echo "<option value=",$owner['owner_id'],">",$owner['first_name']," ",$owner['last_name'],"</option>";
                    }
                  
                  $i++;
                  }
                ?>
                </select> 
              </td> 
            </tr> 
            <tr> 
              <td>
                <span>Staff:</span>
              </td>
              <td>
                <select name="staff_id" class="form-control ">
                  <?php
                    $i = 0;
                    foreach ($staffList as $staff){
                      if ($i == 0){
                        echo "<option selected='selected' value=",$staff['staff_id'],">",$staff['first_name']," ",$staff['last_name'],"</option>";
                      } else {
                        echo "<option value=",$staff['staff_id'],">",$staff['first_name']," ",$staff['last_name'],"</option>";
                      }
                    
                    $i++;
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
                <input required class="inlineInput form-control description" type="text" name="houseDescription" placeholder="Description" value=""></input>
              </td>
            </tr>              
            <tr>
              <td>
                <span>Price per week:</span>
              </td>
              <td>
                <input required class="inlineInput form-control " type="number" min="1" max="10000" name="price" placeholder="Price per week" value=""></input>
              </td>
            </tr>  
            <tr>
              <td>
                <span>Furnished:</span>
              </td>
              <td>
                <select name="furnished" class="form-control ">
                  <option selected="selected" value="1">Yes</option>
                  <option value="0">No</option>
                </select>
              </td>
            </tr>              
            <tr>
              <td>
                <span>House type:</span>
              </td>
              <td>
                <select name="type" class="form-control ">
                  <option selected="selected" value="House">House</option>
                  <option value="Apartment">Apartment</option>
                  <option value="Townhouse">Townhouse</option>
                </select>
              </td>
            </tr> 
            <tr>
              <td>
                <span>Image:</span>
              </td>
              <td>
                <input required class="form-control" type="file" name="file">
              </td>
            </tr>                
            <tr>
            <tr>
              <td>
                <span>Viewing Time:</span>
              </td>
              <td>
                <select name="viewingDay" class="form-control viewing">
                  <option selected="selected" value="Monday">Monday</option>
                  <option value="Tuesday">Tuesday</option>
                  <option value="Wednesday">Wednesday</option>
                  <option value="Thursday">Thursday</option>
                  <option value="Friday">Friday</option>
                  <option value="Saturday">Saturday</option>
                  <option value="Sunday">Sunday</option>
                </select>
                <select name="viewingTime" class="form-control viewing">
                  <option selected="selected" value="10:00">10:00am</option>
                  <option value="10:30">10:30am</option>
                  <option value="11:00">11:00am</option>
                  <option value="11:30">11:30am</option>
                  <option value="12:00">12:00pm</option>
                  <option value="12:30">12:30pm</option>
                  <option value="13:00">1:00pm</option>
                  <option value="13:30">1:30pm</option>
                  <option value="14:00">2:00pm</option>
                  <option value="14:30">2:30pm</option>
                  <option value="15:00">3:00pm</option>
                </select>
              </td>
            </tr>                
            <tr>  
              <td>
                <span>List on website?</span>
              </td>
              <td>
                <select name="available" class="form-control ">
                  <option selected="selected" value="1">Yes</option>
                  <option value="0">No</option>
                </select>
              </td>
            </tr>            
          </table>
          <input type="submit" name="submit" class="btn btn-success profileForm inlineInput" value="Confirm">
          <a name="cancel" class="btn btn-danger profileForm inlineInput" href="manage.php">Cancel</a>
        </form>
    </div>
  </div>
</div>