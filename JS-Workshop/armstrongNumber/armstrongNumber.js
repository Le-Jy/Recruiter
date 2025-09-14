function armstrongNumber(number) {
    if (number < 0 || !Number.isInteger(number)) {
        return false;
    }

    const numStr = number.toString();
    const numDigits = numStr.length;
    let sum = 0;
    for (let digit of numStr) {
        sum += Math.pow(parseInt(digit), numDigits);
    }

    return sum === number;
}

module.exports = {
    armstrongNumber,
};