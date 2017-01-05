function getLocation() {
	if (navigator.geolocation) {
		navigator.geolocation.getCurrentPosition(showPosition, showError);
	} else {
		//document.getElementById("status").innerHTML="Geolocation is not supported by this browser.";
		alert("Geolocation is not supported by this browser.");
	}
}

function showPosition(position) {
  addCurrentPosition(position.coords.latitude, position.coords.longitude);
  if (document.getElementById("search") != null)
  {
		//window.alert("lat = "+position.coords.latitude+", long= "+position.coords.longitude);
	  //window.alert(document.forms[3].length);
	  document.forms[3].elements['lat'].value = position.coords.latitude;
	  document.forms[3].elements['long'].value = position.coords.longitude;
  }
}

function showError(error) {
	var message = "";
	switch(error.code) {
		case error.PERMISSION_DENIED:
      message = "User denied the request for Geolocation."
			break;
		case error.POSITION_UNAVAILABLE:
      message = "Location information is unavailable."
			break;
		case error.TIMEOUT:
      message = "The request to get user location timed out."
			break;
		case error.UNKNOWN_ERROR:
      message = "An unknown error occurred."
			break;
	}

	//document.getElementById("status").innerHTML = message;
	alert(message);
}
