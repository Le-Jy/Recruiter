const { fibo } = require('./fibo');

describe('fibo', () => {
    test('invalid', () => {
        expect(fibo(-5)).toBe(-1);
        expect(fibo("abc")).toBe(-1);
        expect(fibo(NaN)).toBe(-1);
        expect(fibo(null)).toBe(-1);
        expect(fibo(undefined)).toBe(-1);
    });

    test('valid', () => {
        expect(fibo(0)).toBe(0);
        expect(fibo(1)).toBe(1);
        expect(fibo(2)).toBe(1);
        expect(fibo(5)).toBe(5);
        expect(fibo(10)).toBe(55);
        expect(fibo(15)).toBe(610);
    });
});