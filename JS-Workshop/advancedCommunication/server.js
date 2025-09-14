const WebSocket = require("ws");

function startServer() {
  const server = new WebSocket.Server({ port: 8080 });
  console.log(`Websocket server is running on port 8080.`);

  let ID = 0;
  let allUsers = [];
  server.on("connection", (ws, request) => {
    let userName = request.url.split("=")[1];
    let userId = ID + 1;
    ID++;
    ws.on('close', (code, reason) => {
      let tmp = null;
      let toRemove = 0
      for (user of allUsers) {
        if (user.id == userId) {
          tmp = user;
          break;
        }
        toRemove++;
      }
      console.log(`[${userId}] Disconnected: [${code}] ${reason}`);
      allUsers.splice(toRemove, 1);
      if (code == 1008) {
        return;
      }
      for (user of allUsers) {
        user.userSocket.send(`${userName} disconnected`);
      }
    });
    ws.on("message", (message) => {
      console.log(`[${userId}] ${message}`)
    });
    for (user of allUsers) {
      if (user.name == userName) {
        ws.close(1008, `Username: "${userName}" is already taken`);
        return;
      }
    }
    let currentUser = { name: userName, id: userId, userSocket: ws };
    allUsers.push(currentUser);
    ws.send(`Welcome ${userName}`);
    let totalPlayers = allUsers.length;
    if (totalPlayers == 1) {
      ws.send(`${userName}, you are the only player connected`);
    }
    else {
      ws.send(`${totalPlayers} players are connected`);
      for (user of allUsers) {
        if (user.name != userName)
          user.userSocket.send(`${userName} connected`);
      }
    }
    if (allUsers.length < 4) {
      for (user of allUsers) {
        user.userSocket.send(`Waiting for ${4 - totalPlayers} other players to start the game`);
      }
    }
    else if (allUsers.length == 4) {
      for (user of allUsers) {
        user.userSocket.send(`Match will start soon, disconnecting ${user.name} from the lobby`);
        user.userSocket.close(1000, `Match is starting`);
      }
    }
  });
  return server;
}

module.exports = {
  startServer,
}
