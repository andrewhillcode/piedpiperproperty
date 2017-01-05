function fixMain() {
    var navbar = document.getElementById("navbar");
    var jumbo = document.getElementById("jumbo");
    var bgdiv = document.getElementById("bg-img");
    if (jumbo == null){
    	var totalHeight = navbar.offsetHeight;
    } else {
	    var totalHeight = navbar.offsetHeight + jumbo.offsetHeight;
	}
      		bgdiv.style.height = totalHeight + 'px';
}

window.addEventListener("load", fixMain, false);
window.addEventListener("resize", fixMain, false);

$('#bs-example-navbar-collapse-1').on('hidden.bs.collapse', function () {
  fixMain();
})

$('#bs-example-navbar-collapse-1').on('shown.bs.collapse', function () {
  fixMain();
})