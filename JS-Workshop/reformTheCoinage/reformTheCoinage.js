function reformTheCoinage(amount) {
  return count([1,2,5,10], 4, amount)
}

function count(coins , n , amount) {
 
    if (amount == 0)
        return 1;
    if (amount < 0)
        return 0;
    if (n <=0)
        return 0;
    return count( coins, n - 1, amount ) +
           count( coins, n, amount - coins[n - 1] );
}

module.exports = {
  reformTheCoinage,
}
