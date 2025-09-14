window.LOGIN_URL = `https://cri.epita.fr/authorize?client_id=assistants-atelier-js&scope=epita profile picture&redirect_uri=http://localhost:8080/complete/epita/&response_type=code`;

let button = document.getElementById("redirectBtn");

button.addEventListener("click", function() {
  window.location.href = window.LOGIN_URL;
});
