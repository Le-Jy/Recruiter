const fs = require("fs");
const express = require("express");

function readUsersFromJSONFile(JSON_filename) {
  /*
   ** Return the list of users stored in the JSON file
   ** JSON_filename: path to the JSON file
   */
  const content = fs.readFileSync(JSON_filename, (err) => {
    if (err) {
      console.error(err);
      return;
    }
  });
  return JSON.parse(content).users;
}

function writeUsersToJSONFile(JSON_filename, users) {
  /*
   ** Overwrite the given JSON_filename with the given
   ** list of users.
   ** JSON_filename: path to the JSON file
   ** users : list of users objects
   */
  const usersJSON = JSON.stringify({ users: users });
  fs.writeFileSync(JSON_filename, usersJSON, (err) => {
    if (err) {
      console.error(err);
      return;
    }
  });
}

function epiTinderWebServer(host, port, filename) {
  const tinder = express();
  tinder.use(express.json());
  tinder.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
  });
  tinder.get("/", (req, res) => {
    res.status(200).send({
      message: "Hello World!"
    });
  });

  tinder.get("/users", (req, res) => {
    res.status(200).send(readUsersFromJSONFile(filename))
  });

  tinder.post("/users", (req, res) => {
    let users = readUsersFromJSONFile(filename);
    let id = 0;
    if (users.length != 0) {
      for (let user of users) {
        if (user.id > id) {
          id = user.id;
        }
      }
    }
    let new_user = {}
    for (let key in req.body) {
      new_user[key] = req.body[key];
    }
    new_user.id = id + 1;
    users.push(new_user);

    writeUsersToJSONFile(filename, users);
    res.status(201).send(new_user);
  });

  tinder.get("/users/:id", (req, res) => {
    let users = readUsersFromJSONFile(filename);
    let target = null;
    for (let user of users) {
      if (user.id == req.params.id)
        target = user;
    }
    if (target == null) {
      res.status(404).send({ message: `No user with id: ${req.params.id} found` });
    }
    else {
      res.status(200).send(target);
    }
  });

  tinder.put("/users/:id", (req, res) => {
    let users = readUsersFromJSONFile(filename);
    let length = users.length;
    let target = 0;
    while (target < length && users[target].id != req.params.id) {
      target++;
    }
    if (target >= length) {
      res.status(404).send({ message: `No user with id: ${req.params.id} found` });
    }
    else {
      users[target].name = req.body.name;
      users[target].age = req.body.age;
      users[target].description = req.body.description;
      let toSend = users[target];
      writeUsersToJSONFile(filename, users);
      res.status(201).send(toSend);
    }
  });

  tinder.delete("/users/:id", (req, res) => {
    let users = readUsersFromJSONFile(filename);
    let target = 0;
    let length = users.length;
    while (target < length && users[target].id != req.params.id) {
      target++;
    }
    if (target >= length) {
      res.status(404).send({ message: `No user with id: ${req.params.id} found` });
    }
    else {
      let toSend = users[target];
      users.splice(target, 1);
      writeUsersToJSONFile(filename, users);
      res.status(200).send(toSend);
    }
  })

  tinder.get('*', (req, res) => {
    res.status(404).send({message:'Not found'});
  });
  return tinder;
}

module.exports = {
  epiTinderWebServer,
}
