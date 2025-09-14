const fs = require('fs');
const path = require('path');

function extract(directoryPath) {
  if (!fs.existsSync(directoryPath) || !fs.lstatSync(directoryPath).isDirectory()) {
    throw new Error('The directory does not exist');
  }

  const emailRegex = /[\w.+%-]+@[\w.-]+\.[A-Za-z]{2,}/g;
  const emailAddresses = [];
  const files = fs.readdirSync(directoryPath);

  files.forEach(file => {
    const filePath = path.join(directoryPath, file);
    const fileContent = fs.readFileSync(filePath, 'utf8');
    const matches = fileContent.match(emailRegex);
    if (matches) {
      emailAddresses.push(...matches);
    }
  });

  return emailAddresses;
}

module.exports = {
  extract
};
