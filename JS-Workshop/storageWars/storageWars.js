const textBox = document.getElementById("inputJWT");
const error = document.getElementById("error");
const userInfo = document.getElementById("userInfo");

checkLocal();

function parseJwt(token) {
  return JSON.parse(atob(token));
}

function addToken() {
  const jwtText = textBox.value.trim();
  if (jwtText === "") {
    return;
  }

  let spl = jwtText.split(".");
  if (spl.length != 3) {
    // disp "Invalid Token" in the div error && hide div "userInfo"
    userInfo.style.display = "none";
    error.innerHTML = "Invalid token";
    error.style.display = "block";
    return;
  }
  let decoded = parseJwt(spl[1]);
  let keys = ["name", "age", "email"];
  localStorage.setItem("jwt", jwtText);
  for (let key of keys) {
    if (decoded[key] == undefined)
      document.getElementById(key).innerHTML = "No " + key;
    else
      document.getElementById(key).innerHTML = decoded[key];
  }
  userInfo.style.display = "block";
}

function checkLocal() {
  let stored = localStorage.getItem("jwt");
  if (stored == undefined)
    return;
  let keys = ["name", "age", "email"];
  let decoded = parseJwt(stored);
  for (let key of keys) {
    if (decoded[key] == undefined)
      document.getElementById(key).innerHTML = "No " + key;
    else
      document.getElementById(key).innerHTML = decoded[key];
  }
  userInfo.style.display = "block";
}
