const axios = require("axios");

function sleep(s) {
  return new Promise((resolve) => setTimeout(resolve, s));
}
async function notSoFast(host, port) {
  let webSite = `http://${host}:${port}/`;
  let nb_articles = 0;
  let articles_list = [];
  let response1 = await axios.get(webSite + `articles`)
  nb_articles = response1.data.message;
  let counter = 0;
  for (let index = 0; index < nb_articles; index++) {
    let response = await axios.get(webSite + `articles/${index}`)
    counter++;
    if (counter == response.headers['x-ratelimit-limit'] && nb_articles > 1) {
      await sleep(response.headers['x-ratelimit-reset'] * 1000 - Date.now() + 10);
      counter = 0;
    }
    articles_list.push(response.data);
  }
  return articles_list;
}

module.exports = {
  notSoFast,
}
