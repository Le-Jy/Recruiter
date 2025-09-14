const express = require("express");
const jwt = require('jsonwebtoken');

function logMeIn(host, port) {
  const server = express();
  server.use(express.json());
  server.listen(port, host, () => {
    console.log(`Server running at http://${host}:${port}/`);
  });
  server.get("/", (req, res) => {
    res.send({
      message: "Hello World!"
    });
  });

  server.post("/login", (req, res) => {
    if (req.body.username == "xavier.login" && req.body.password == "1234") {
      let token = jwt.sign(req.body, process.env.JWT_SECRET_KEY);
      res.send({jwt: token});
    }
    else {
      res.status(401).send({
        error: "Invalid username or password"
      });
    }
  });

  server.get("/secret", (req, res) => {
    try {
      let decoded = jwt.verify(req.headers.authorization.split(" ")[1], process.env.JWT_SECRET_KEY);
      res.send({
        message: "Access granted"
      });
    } catch (err) {
      res.status(401).send({
        error: "Unauthorized"
      });
      
    }

  });


  return server;
}

module.exports = {
  logMeIn,
}
