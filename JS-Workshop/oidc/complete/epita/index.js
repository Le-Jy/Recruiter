let button = document.getElementById("RequestBtn");

function parseJwt(token) {
  return JSON.parse(atob(token));
}

button.addEventListener("click", async function() {
  const queryString = window.location.search;
  const urlParams = new URLSearchParams(queryString);
  const code = urlParams.get('code');
  const formdata = new FormData();
  formdata.append("client_id", "assistants-atelier-js");
  formdata.append("redirect_uri", "http://localhost:8080/complete/epita/");
  formdata.append("grant_type", "authorization_code");
  formdata.append("code", `${code}`);

  const response = await fetch(`http://localhost:8080/auth-api`, {
    method: 'POST',
    body: formdata,
  }).catch(err => {
    console.log(err)
  });
  const infos = await response.json();
  let id_token = infos.id_token;
  let decoded = parseJwt(id_token.split('.')[1]);
  let keys = ["name", "zoneinfo", "graduation_years", "picture_square"];
  let keys2 = ["name", "campus", "grad-year", "image"];
  for (let i = 0; i < keys.length; i++) {
    if (keys[i] != "image")
      document.getElementById(keys2[i]).innerHTML = decoded[keys[i]];
    else {
      document.getElementById(keys2[i]).src = decoded[keys[i]];
    }
  }
  let list = document.getElementById("list");
  for (let element of decoded.groups) {
    let listItem = document.createElement("li");
    listItem.innerHTML = `${element.slug} ${element.name}`;
    list.appendChild(listItem);
  }
});

let endButton = document.getElementById("EndBtn");

window.END_SESSION_URL = `https://cri.epita.fr/end-session`

endButton.addEventListener("click", function () {
  window.location.href = window.END_SESSION_URL;
})
