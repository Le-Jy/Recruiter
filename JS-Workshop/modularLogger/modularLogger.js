function loggerFactory() {
  let logs = [];
  let nameLogLevelsVerify = ["ERROR", "WARN", "INFO", "DEBUG"];
  let nameLogLevels = [["ERROR"], ["ERROR", "WARN"], ["ERROR", "WARN", "INFO"], ["ERROR", "WARN", "INFO", "DEBUG"]]
  return function newLogger(...param) {
    if (param.length > 1 || (param.length == 1 && typeof param[0] != "number") || param[0] < 0) {
      console.log("Bad argument.");
      return;
    }
    if (param.length == 1) {
      let index = param[0] < 4 ? param[0] : 3;
      for (let log of logs) {
        if (nameLogLevels[index].indexOf(log[1]) != -1) {
          console.log(`[${log[0]}][${log[1]}] - ${log[2]}`);
        }
      }
      return;
    }
    return function addLog(date, nameLogLevel, message) {
      if (nameLogLevelsVerify.indexOf(nameLogLevel) == -1) {
        console.log(`${nameLogLevel} is an invalid log level. Please use one of the following: DEBUG, INFO, WARN, ERROR.`)
        return;
      }
      logs.push([`${date.toTimeString().substring(0,8)}`].concat([`${nameLogLevel}`], [`${message}`]));
    }
  }
}

module.exports = {
  loggerFactory,
}

let newLogger = loggerFactory();
let addLog = newLogger();
let date = new Date();
addLog(date, "INFO", "This is an info message");
addLog(date, "DEBUG", "This is a debug message");
addLog(date, "ERROR", "This is an error message");
addLog(date, "WARN", "This is a warn message");
newLogger("INFO");
