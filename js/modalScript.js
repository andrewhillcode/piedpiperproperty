$("#registerButton").click(function(){
  $('#loginModal').modal('hide');
  $('#registerModal').modal('show');
});

$("#loginButton").click(function(){
  $('#registerModal').modal('hide');
  $('#loginModal').modal('show');
});

$("#noAccountButton").click(function(){
  $('#loginModal').modal('hide');
  $('#registerModal').modal('show');
});

$("#haveLoginButton").click(function(){
  $('#registerModal').modal('hide');
  $('#loginModal').modal('show');
});

$(document).ready(function () {
  $('.modal').on('show.bs.modal', function () {
    if ($(document).height() > $(window).height()) {
	    // no-scroll
        $('body').addClass("modal-open-noscroll");
    }
    else {
        $('body').removeClass("modal-open-noscroll");
    }
})
$('.modal').on('hide.bs.modal', function () {
    $('body').removeClass("modal-open-noscroll");
    })
})