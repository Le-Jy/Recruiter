const { stocks, recipes } = require("./data");
const { sleep } = require("./sleep");

async function delivering(recipeName) {
  await sleep(2);
  console.log(`Delivering ${recipeName}`);
}

async function end_of_order(recipeName) {
  console.log("All ingredients have been prepared");
  await sleep(2);
  console.log(`Cooking ${recipeName}`);
  await sleep(3);
  delivering(recipeName);
}

function check_and_update_ingredient(recipeName, ingredient, quantity) {
  if (stocks[ingredient] < quantity) {
    console.log(
      `Not enough ingredients for ${recipeName} because there is no more ${ingredient}`,
    );
    return false;
  }
  stocks[ingredient] -= quantity;
  return true;
}

function check_and_update_ingredients(recipeName, ingredients) {
  for (const ingredient in ingredients) {
    const quantity = ingredients[ingredient];
    if (!check_and_update_ingredient(recipeName, ingredient, quantity)) {
      return false;
    }
  }
  return true;
}

async function prepare_pizza(recipeName) {
  const pizza = recipes.pizza[recipeName];
  console.log(`Preparing ${pizza.sauce}`);
  if (!check_and_update_ingredient(recipeName, pizza.sauce, 1)) {
    return;
  }
  await sleep(1);
  console.log(`Preparing ${Object.keys(pizza.toppings).join(", ")}`);
  if (!check_and_update_ingredients(recipeName, pizza.toppings)) {
    return;
  }
  await sleep(1);
  console.log(`Preparing ${Object.keys(pizza.cheese).join(", ")}`);
  if (!check_and_update_ingredients(recipeName, pizza.cheese)) {
    return;
  }
  await sleep(1);
  end_of_order(recipeName);
}

async function prepare_burger(recipeName) {
  const burger = recipes.burger[recipeName];

  for (let ingredient in burger) {
    console.log(`Preparing ${ingredient}`);
    if (!check_and_update_ingredient(recipeName, ingredient, burger[ingredient])) {
      return;
    }
    await sleep(1);
  }
  end_of_order(recipeName);
}

async function order(recipeName) {
  console.log(`Ordering ${recipeName}`);

  if (!(recipeName in recipes.pizza) && !(recipeName in recipes.burger)) {
    console.log(`Recipe ${recipeName} does not exist`);
    return;
  }
  await sleep(1);
  console.log(`Production has started for ${recipeName}`);
  await sleep(2);

  if (recipeName in recipes.pizza) {
    prepare_pizza(recipeName);
  }
  if (recipeName in recipes.burger) {
    prepare_burger(recipeName);
  }
}

module.exports = {
  order,
}
