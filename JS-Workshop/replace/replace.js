function replace(str) {
const captureDateRegex = new RegExp("(?<month>\\d{2})\/(?<day>\\d{2})\/(?<year>\\d{4})");
  while(captureDateRegex.test(str)) {
    const matched = captureDateRegex.exec(str);
    str = str.replace(captureDateRegex,matched.groups.year + "-" + matched.groups.month + "-" + matched.groups.day );
  }
  return str;
}

module.exports = {
  replace,
}
