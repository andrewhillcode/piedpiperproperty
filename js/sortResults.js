function sortResults(selection) {
  var resultsContainer = document.getElementById("resultsContainer");
  var results = document.getElementById("results");
  resultsContainer.removeChild(results);
  document.getElementById("sortSelection").innerHTML =  "<?php echo postResults($result, $usersLat, $usersLong, $pdo);?>";
  //var newSelection = <?php echo $order=selection;?>;
}
