"use strict";

const {
  InvalidUsernameError,
  InvalidPasswordError,
  InvalidYearOfBirthError,
} = require("./accountError");

class Account {
  constructor(username, password, yearOfBirth) {
    if (
      typeof username !== "string" ||
      !/^[a-zA-Z0-9-_]+$/.test(username) ||
      username.length === 0
    ) {
      throw new InvalidUsernameError("Invalid username");
    }

    if (
      typeof password !== "string" ||
      password.length < 8 ||
      password.length > 100 ||
      !/[a-z]/.test(password) ||
      !/[A-Z]/.test(password) ||
      !/\d/.test(password)
    ) {
      throw new InvalidPasswordError("Invalid password");
    }

    const currentYear = new Date().getFullYear();
    if (
      !Number.isInteger(yearOfBirth) ||
      yearOfBirth <= 1800 ||
      yearOfBirth > currentYear
    ) {
      throw new InvalidYearOfBirthError("Invalid year of birth");
    }

    this.username = username;
    this.password = password;
    this.yearOfBirth = yearOfBirth;
  }
}

global.Account = Account;
module.exports = {
  Account,
};