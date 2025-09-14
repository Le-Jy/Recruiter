function deepCopy(x) {
  if (typeof x == "undefined")
    return undefined;
  if (x == null)
    return null;
  if (Array.isArray(x)) {
    let new_arr = [];
    for (let element of x) {
      new_arr.push(deepCopy(element));
    }
    return new_arr;
  }
  if (typeof x == "object") {
    let new_obj = {};
    for (let element in x) {
      new_obj[element] = (deepCopy(x[element]));
    }
    return new_obj;
  }
  if (x instanceof Date)
    return { ...x };
  else
    return x;
}

function deepEquality(a, b) {
  if (a === b) {
    return true;
  }

  if (Array.isArray(a) && Array.isArray(b)) {

    if (a.length !== b.length) {
      return false;
    }

    return a.every((elem, index) => {
      return deepEquality(elem, b[index]);
    })
  }

  if (typeof a === "object" && typeof b === "object" && a !== null && b !== null) {
    if (Array.isArray(a) || Array.isArray(b)) {
      return false;
    }
    const keys1 = Object.keys(a)
    const keys2 = Object.keys(b)
    if (keys1.length !== keys2.length || !keys1.every(key => keys2.includes(key))) {
      return false;
    }
    for (let key in a) {
      let isEqual = deepEquality(a[key], b[key])
      if (!isEqual) {
        return false;
      }
    }
    return true;
  }
  return false;
}

module.exports = {
  deepCopy,
  deepEquality,
}
