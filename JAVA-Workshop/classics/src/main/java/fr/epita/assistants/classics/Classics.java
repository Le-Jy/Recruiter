package fr.epita.assistants.classics;

public class Classics {
    /**
     * Computes the factorial of n.
     *
     * @param n the nth value to compute, negative values should return -1
     * @return the long value of n!
     */
    public static long factorial(int n) {
        if (n < 0)
            return -1;
        if (n == 0)
            return 1;
        long res = 1;
        while (n > 0) {
            res *= n;
            n--;
        }
        return res;
    }

    /**
     * Computes the nth value of the tribonacci suite.
     * f(0) = 0, f(1) = 1, f(2) = 1, f(n+3) = f(n) + f(n+1) + f(n+2)
     *
     * @param n the nth sequence to compute
     */
    public static long tribonacci(int n) {
        if (n < 0)
            return -1;
        if (n == 0)
            return 0;
        if (n == 1 || n == 2)
            return 1;
        long first = 0;
        long second = 1;
        long third = 1;
        long curr = 0;
        for (int i = 3; i <= n; i++) {
            curr = first + second + third;
            first = second;
            second = third;
            third = curr;
        }
        return curr;
    }

    /**
     * Checks if a word is a palindrome.
     *
     * @param word the string to check
     * @return true if the word is a palindrome, false otherwise.
     */
    public static boolean isPalindrome(String word) {
        if (word == null)
            return false;
        if (word.contentEquals(""))
            return true;

        for (int i = 0, j = word.length() - 1; i < j; i++, j--) {
            while (Character.toLowerCase(word.charAt(i)) == ' ') {
                i++;
            }
            while (Character.toLowerCase(word.charAt(j))== ' ') {

                j--;
            }
            if (Character.toLowerCase(word.charAt(i)) != Character.toLowerCase(word.charAt(j))) {
                return false;
            }
        }
        return true;
    }

    /**
     * Sorts an array using an insertion sort.
     *
     * @param array the array to sort in place
     */
    public static void insertionSort(int[] array) {
        int n = array.length;
        for (int i = 1; i < n; i++) {
            int key = array[i];
            int j = i - 1;
            while (j >= 0 && array[j] > key) {
                array[j + 1] = array[j];
                j = j - 1;
            }
            array[j + 1] = key;
        }
    }

    /**
     * Combines two strings by alternating their characters. Must use a StringBuilder.
     * If the strings do not have the same length, appends the remaining characters at the end of the result.
     * For instance, combine("abc", "def") returns "adbecf"
     */
    public static String combine(String a, String b) {
        var result = new StringBuilder();
        int i = 0;
        while (i < a.length() && i < b.length()) {
            result.append(a.charAt(i));
            result.append(b.charAt(i));
            i++;
        }
        while (i >= a.length() && i < b.length()) {
            result.append(b.charAt(i));
            i++;
        }
        while (i < a.length() && i >= b.length()) {
            result.append(a.charAt(i));
            i++;
        }
        return String.valueOf(result);
    }
}
