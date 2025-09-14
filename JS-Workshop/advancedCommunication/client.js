const WebSocket = require("ws");

function addClient(userName) {
  const socket = new WebSocket(`ws://localhost:8080?username=${userName}`);
  socket.on("open", () => {
    socket.send(`${userName}: trying to establish connection`);
  });

  socket.on("close", (code, reason) => {
    console.log(`<server to ${userName}>: Connection has been closed: [${code}] ${reason}`);
  });

  socket.on("message", (message) => {
    console.log(`<server to ${userName}>: ${message}`);
  });
  socket.on('error', (error) => {
    console.error(`Error with ${userName}`, error);
  }); // In case an error happens

  return socket;
}

module.exports = {
  addClient,
}
