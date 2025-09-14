function debounce(func, n) {
  let timer;
  return (...args) => {
    clearTimeout(timer);
    timer = setTimeout(() => {
      func.apply(this, args);
    }, n);
  };
}

function throttle(func, n) {
  let lastArgs;
  let timeout = null;
  return (...args) => {
    if (timeout) {
      lastArgs = args;
      return;
    }
    func(...args);
    timeout = setTimeout(() => {
      timeout = null;
      if (lastArgs == undefined)
        return;
      func(...lastArgs);
    }, n);
  };
}

module.exports = {
  debounce,
  throttle,
}
