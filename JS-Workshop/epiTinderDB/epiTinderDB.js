const { Sequelize, DataTypes, Op } = require('sequelize');

let User = null;

async function connectToDB() {
  const sequelize = new Sequelize(
    `postgres://${process.env.USERNAME}:${process.env.PASSWORD}@localhost:5432/postgres`
  );
  User = sequelize.define(
    'epitinder_users',
    {
      name: {
        type: DataTypes.STRING,
        allowNull: false,
      },
      age: {
        type: DataTypes.INTEGER,
        allowNull: false,
      },
      description: {
        type: DataTypes.STRING,
        allowNull: false,
      },
    },
    {

      timestamps: false,

      createdAt: false,

      updatedAt: false,
    }
  );
  return sequelize;
}

async function getAllUsers() {
  const users = await User.findAll({ raw: true });
  return users;
}

async function getUser(id) {
  const user = await User.findByPk(id, { raw: true });
  return user;
}

async function addUser(newUser) {
  if (newUser["id"] !== undefined)
    return null;
  if (newUser.name === undefined || newUser.name === null ||
    newUser.age === undefined || newUser.age === null ||
    newUser.description === undefined || newUser.description === null) {
    return null;
  }
  const created = await User.create(newUser, { raw: true });
  return created.toJSON();
}

async function updateUser(user) {

  if (user.id === undefined || user.name === undefined || user.age === undefined || user.description === undefined || Object.keys(user).length != 4) {
    return null;
  }

  let toUpdate = await getUser(user.id);
  if (!toUpdate) {
    return null;
  }

  User.update({
    age: user.age,
    name: user.name,
    description: user.description
  }, {
    where: {
      id: user.id
    }
  });

  return toUpdate;
}

async function deleteUser(id) {
  const toDelete = await getUser(id);
  if (toDelete == null)
    return null;
  await User.destroy({
    where: {
      id: id
    }
  });
  return toDelete;
}

async function getAllUsersName() {
  const names = await User.findAll({
    attributes: ['name'],
    raw: true
  });
  return names;
}

async function getAllYoungAdults() {
  const users = await User.findAll({
    where: {
      age: {
        [Op.gt]: 18,
        [Op.lt]: 30,
      },
    },
    raw: true
  });
  return users;
}

module.exports = {
  connectToDB,
  getAllUsers,
  getUser,
  addUser,
  updateUser,
  deleteUser,
  getAllUsersName,
  getAllYoungAdults,
}
