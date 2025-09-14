const axios = require('axios').default;
const { load } = require('cheerio');

async function scrape(url) {
  const pageData = (await axios.get(url)).data;
  const $ = load(pageData);
  res = {};
  res["title"] = $('title').text();
  res["meta"] = {};
  res["meta"]["description"] = $('meta[name="description"]').attr('content');
  res["meta"]["keywords"] = $('meta[name="keywords"]').attr('content');
  if (res.meta.keywords.indexOf("Quotes")) {
    res["content"] = [];
    let quoteText = $('.quote-text').map((index, element) => $(element).text().trim()).get();
    for (let i = 0; i < quoteText.length; i++) {
      quoteText[i] = quoteText[i].trim();
    }
    let quoteAuthor = $('.quote-author').map((index, element) => $(element).text().trim()).get();
    for (let i = 0; i < quoteAuthor.length; i++) {
      quoteAuthor[i] = quoteAuthor[i].trim();
    }
    let quoteTags = $('.quote-tags').map((index, element) => $(element).text().trim()).get();
    for (let i = 0; i < quoteTags.length; i++) {
      let quotes = [];
      for (let tag of quoteTags[i].split('\n')) {
        quotes.push(tag.trim());
      }
      quoteTags[i] = quotes;
    }
    for (let i = 0; i < quoteText.length; i++)
      res["content"].push({quote: quoteText[i], author: quoteAuthor[i], tags: quoteTags[i]});
  }
  return res;
}

module.exports = {
  scrape,
}
