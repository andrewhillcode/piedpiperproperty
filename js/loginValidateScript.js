function loginValidate() {
  if (!checkUsername()) return false;
  return true;
}

/*
/ Checks the validation of the username field.
/ Returns false if username is empty otherwise returns true.
*/
function checkUsername() {
  var email = document.forms["loginForm"]["email"];
  if (email.value == "") {
    email.focus();
    document.getElementById("usernameRequired").style.visibility = "visible";
    return false;
  }
  return true;
}
