function validateInput() {
  const username = document.loginForm.username.value;
  const password = document.loginForm.password.value;
  if (username == "") {
    alert("Username cannot be empty!");
    return false;
  } else if (password == "") {
    alert("Password cannot be empty!");
    return false;
  }
}
