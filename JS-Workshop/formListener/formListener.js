let formRadioEmacs = document.getElementById("form-radio-emacs");
let formRadioVscode = document.getElementById("form-radio-vscode");
let formRadioVim = document.getElementById("form-radio-vim");
let submitBtn = document.getElementById("the-one-form");
let loginText = document.getElementById("form-login");
let emailText = document.getElementById("form-email");

formRadioEmacs.addEventListener("click", () => {
  setTimeout(function() {
    formRadioVim.click();
  }, 500);
});

formRadioVscode.addEventListener("click", () => {
  setTimeout(function() {
    formRadioVim.click();
  }, 500);
});

submitBtn.addEventListener("submit", (event) => {

  if (!formRadioVim.checked) {
    event.preventDefault();
    event.stopPropagation();
    return;
  }
  let logins = /^[a-zA-Z\-]+\.[a-zA-Z\-]+[\d]?$/g
  let emails = /^[a-zA-Z\-]+\.[a-zA-Z\-]+[\d]?@.{0,63}epita.fr$/g
  if (loginText.value.trim().match(logins) == null || emailText.value.trim().match(emails) == null) {
    event.preventDefault();
    event.stopPropagation();
    return;
  }
});
