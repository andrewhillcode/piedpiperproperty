<?php
  function GetRandFloat($min, $max) {
    return $min + (($max - $min) * rand() / getrandmax());
  }

  for ($i = 0; $i < 10; $i++) {
    $longitude = GetRandFloat(-27.700, -27.300);
    $latitude = GetRandFloat(152.900, 153.150);
    echo '<p>'.$i.' - longitude: '.number_format($longitude, 3).'<br>';
    echo ''.$i.' - latitude: '.number_format($latitude, 3).'</p>';
  }
?>
