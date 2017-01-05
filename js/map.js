var map;
var locations = [];

function createMap() {
    var mapOptions = {
        center: new google.maps.LatLng(-27.4712909,153.0244888),
        zoom: 10,
        mapTypeId: google.maps.MapTypeId.ROADMAP
    }
    var mapCanvas = document.getElementById("map-canvas");
    map = new google.maps.Map(mapCanvas, mapOptions);
}

function addMarker(id, name, longitude, latitude) {
    locations.push(new google.maps.Marker({
        position: new google.maps.LatLng(longitude, latitude),
        title: name,
        url: "property.php?house_id=" + id
    }));
    var bounds = new google.maps.LatLngBounds ();

    for (var i = 0; i < locations.length; i++) {
        var marker = locations[i];
        marker.setMap(map);
        google.maps.event.addListener(marker, "click", function() {
            window.location.href = this.url;
        });
        bounds.extend (marker.position);
    }

    //map.fitBounds(bounds);
    map.setCenter(bounds.getCenter());
}

function addCurrentPosition(latitude, longitude) {
    var marker = new google.maps.Marker({
        position:new google.maps.LatLng(latitude, longitude),
        icon: "http://maps.google.com/mapfiles/ms/icons/blue-dot.png",
        title: "My Position, click to zoom"
    });
    marker.setMap(map);

    google.maps.event.addListener(marker, "click", function() {
        map.setZoom(18);
        map.setCenter(marker.getPosition());
    });
    var myLatLng = new google.maps.LatLng(latitude, longitude);
    //map.setCenter(myLatLng);
}

getLocation();
