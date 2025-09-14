function sortInt(arr) {
  for (let j = 0; j < arr.length; j++) {
    for (let k = j + 1; k < arr.length; k++) {
      if (arr[j] > arr[k]) {
        [arr[j], arr[k]] = [arr[k], arr[j]];
      }
    }
  }
}

function sortElement(left, right) {
  if (typeof left == "number" && typeof right == "number") {
    return right - left;
  }

  if (typeof left == "string" && typeof right == "string") {
    return right.localeCompare(left);
  }

  if (Array.isArray(left) && Array.isArray(right)) {
    sortInt(left);
    sortInt(right);
    if (right.length == 0 && left.length != 0)
      return -1;
    if (left[0] > right[0]) {
      return -1;
    }
  }

  if (typeof left == "string" && typeof right == "number") {
    return -1;
  }

  if (Array.isArray(left) && !Array.isArray(right)) {
    return -1;
  }
  return 1
}

function sortArray(array) {
  if (array.length == 1 && Array.isArray(array[0]))
    sortInt(array[0]);
  for (let j = 0; j < array.length; j++) {
    for (let k = j + 1; k < array.length; k++) {
      if (sortElement(array[j], array[k]) < 0)
        [array[j], array[k]] = [array[k], array[j]];
    }
  }
}

function activate(array) {
  let act = array.indexOf("activate");
  let loop = array.indexOf("activate");
  while (loop != -1) {
    array.splice(loop, 1);
    loop = array.indexOf("activate");
  }

  if (act != -1) {
    let call_disp = false;
    for (let i = 0; i < array.length; i++) {
      if (typeof array[i] == "number") {
        array[i] *= array[i];
      }
      else if (typeof array[i] == "string" && array[i] != "disperse") {
        array[i] = "super " + array[i];
      }
      else if (array[i] == "disperse") {
        call_disp = true;

      }
      else if (Array.isArray(array[i])) {
        array[i] = activate(array[i]);
      }
    }
    array = disperse(array);
  }
  return array;
}

function disperse(array) {
  let disp = array.indexOf("disperse");
  let loop = array.indexOf("disperse");
  while (loop != -1) {
    array.splice(loop, 1);
    loop = array.indexOf("disperse");
  }
  if (disp != -1) {
    let int = [];
    let string = [];
    let arr = []
    let call_activate = false;
    for (let i = 0; i < array.length; i++) {
      let tmp = array[i];
      if (typeof array[i] == "number" || typeof array[i] == "bigint") {
        array.splice(array.indexOf(array[i]), 1);
        int.push(tmp);
      }

      else if (typeof array[i] == "string" && array[i] != "activate") {
        array.splice(array.indexOf(array[i]), 1);
        string.push(tmp);
      }

      else if (array[i] == "activate") {
        call_activate = true;
      }

      else {
        tmp = disperse(array[i]);
        array.splice(array.indexOf(array[i]), 1);
        arr.push(tmp)
      }
      i--;
    }
    if (arr.length > 0) {
      array.unshift(arr);
    }
    if (string.length > 0) {
      array.unshift(string);
    }
    if (int.length > 0) {
      array.unshift(int);
    }
    if (call_activate) {
      activate(array);
    }
  }

  return array;
}

function changeArray(array) {
  array = activate(array);
  array = disperse(array);
  return array;
}

module.exports = {
  sortArray,
  changeArray,
};
