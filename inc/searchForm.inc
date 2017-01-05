<div id="jumbo" class="jumbotron container-fluid">
	<div class="container">
    <h1>Search our properties</h1>
      <form id ="search" action="search.php" class="bs-example bs-example-form" role="form" method="post">
        <div class="row">
          <div class="col-lg-12">
            <div class="input-group big-input">
              <input type="text" name="search-field" class="form-control" placeholder="Enter an address, suburb or postcode">
              <span class="input-group-btn">
                <input class="btn btn-default" value="Search" type="submit"></input>
              </span>
            </div><!-- /input-group -->
          </div><!-- /.col-lg-6 -->
        </div><!-- /.row -->
        <br>
        <fieldset>
          <legend>Refine search</legend>
          <div id="row1" class="row">
						<div class="col-lg-3 col-centered">
              <div class="input-group">
								<span class="input-group-addon">Price</span>
                <select name="price" class="form-control">
                  <option value="">Any</option>
                  <option value="200">< $200 Per Week</option>
									<option value="400">< $400 Per Week</option>
									<option value="600">< $600 Per Week</option>
									<option value="800">< $800 Per Week</option>
									<option value="2000">> $2000 Per Week</option>
                </select>
              </div>
						</div>
						<div class="col-lg-2 col-centered">
							<div class="input-group">
								<span class="input-group-addon">Beds</span>
								<select name="beds" class="form-control">
									<option value="">Any</option>
									<option value="1">1</option>
									<option value="2">2</option>
									<option value="3">3</option>
									<option value="4">4</option>
									<option value="5">5</option>
									<option value="6">6</option>
								</select>
							</div>
						</div>
            <div class="col-lg-2 col-centered">
              <div class="input-group">
                <span class="input-group-addon">Baths</span>
                <select name="baths" class="form-control">
                  <option value="">Any</option>
                  <option value="1">1</option>
                  <option value="2">2</option>
                  <option value="3">3</option>
                  <option value="4">4</option>
                  <option value="5">5</option>
                  <option value="6">6</option>
                </select>
              </div>
            </div>
						<div class="col-lg-3 col-centered">
              <div class="input-group">
                <span class="input-group-addon">Distance</span>
                <select name="distance" class="form-control">
                  <option value=9999>Any</option>
                  <option value="5">< 5km</option>
                  <option value="10">< 10km</option>
                  <option value="15">< 15km</option>
                  <option value="20">< 20km</option>
                  <option value="35">< 35km</option>
                  <option value="50">< 50km</option>
                </select>
              </div>
            </div>
				  </div>
          <div id="row2" class="row">
						<div class="col-lg-3 col-centered">
							<div class="input-group">
								<span class="input-group-addon">Type</span>
								<select name="type" class="form-control">
									<option value="">All property types</option>
									<option value="1">House</option>
									<option value="2">Apartment</option>
									<option value="3">Townhouse</option>
								</select>
							</div>
						</div>
            <div class="col-lg-2 col-centered">
              <div class="input-group">
                <span class="input-group-addon">Carports</span>
                <select name="cars" class="form-control">
                  <option value="">Any</option>
                  <option value="1">1</option>
                  <option value="2">2</option>
                  <option value="3">3</option>
                  <option value="4">4</option>
                  <option value="5">5</option>
                  <option value="6">6</option>
                </select>
              </div>
            </div>
            <div class="col-lg-2 col-centered">
              <div class="input-group">
                <span class="input-group-addon">Furnished</span>
                <select name="furnished" class="form-control">
                  <option value="">Any</option>
                  <option value="1">Yes</option>
                  <option value="0">No</option>
                </select>
              </div>
            </div>
						<div class="col-lg-3 col-centered">
							<div class="input-group">
								<span class="input-group-addon">Agent</span>
								<input type="text" name="agent" class="form-control" placeholder="Agent Name">
							</div>
						</div>
          </div>
        </fieldset>
				<input name="lat" style="display:none">
				<input name="long" style="display:none">
      </form>
    </div>
  </div>
</div>
<script src="https://maps.googleapis.com/maps/api/js"></script>
<script src="js/geolocationScript.js"></script>
<script src="js/map.js"></script>
