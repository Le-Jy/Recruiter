package fr.epita.assistants.maths;

import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;

public class MatrixTests {

    @Test
    void testMatrixConstructorValid() {
        int[][] matrix = {{1, 2}, {3, 4}};
        Matrix mat = new Matrix(matrix);

        Assertions.assertArrayEquals(matrix, mat.getMatrix());
    }

    @Test
    void testMatrixConstructorNullInput() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Matrix(null);
        });
    }

    @Test
    void testMatrixConstructorEmptyInput() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Matrix(new int[][]{});
        });
    }

    @Test
    void testMatrixConstructorInvalidDimensions() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            new Matrix(new int[][]{{1, 2}, {3}});
        });
    }

    @Test
    void testEqualsSameMatrix() {
        int[][] matrix1 = {{1, 2}, {3, 4}};
        Matrix mat1 = new Matrix(matrix1);
        Matrix mat2 = new Matrix(matrix1);

        Assertions.assertEquals(mat1, mat2);
    }

    @Test
    void testEqualsDifferentMatrix() {
        int[][] matrix1 = {{1, 2}, {3, 4}};
        int[][] matrix2 = {{1, 2}, {3, 5}};

        Matrix mat1 = new Matrix(matrix1);
        Matrix mat2 = new Matrix(matrix2);

        Assertions.assertNotEquals(mat1, mat2);
    }

    @Test
    void testEqualsNull() {
        int[][] matrix1 = {{1, 2}, {3, 4}};
        Matrix mat1 = new Matrix(matrix1);

        Assertions.assertNotEquals(mat1, null);
    }

    @Test
    void testEqualsDifferentType() {
        int[][] matrix1 = {{1, 2}, {3, 4}};
        Matrix mat1 = new Matrix(matrix1);

        Assertions.assertNotEquals(mat1, "Not a matrix");
    }

    @Test
    void testMultiplyValid() {
        int[][] matrix1 = {{1, 2}, {3, 4}};
        int[][] matrix2 = {{2, 0}, {1, 2}};
        int[][] expectedResult = {{4, 4}, {10, 8}};

        Matrix mat1 = new Matrix(matrix1);
        Matrix mat2 = new Matrix(matrix2);
        Matrix result = mat1.multiply(mat2);

        Assertions.assertNotEquals(expectedResult, result.getMatrix());
    }

    @Test
    void testWrongMathematics() {
        int[][] matrix1 = {{1, 2, 3}, {4, 5, 6}, {1, 1, 1}};
        int[][] matrix2 = {{1, 2}, {3, 4}};

        Matrix mat1 = new Matrix(matrix1);
        Matrix mat2 = new Matrix(matrix2);

        Assertions.assertNull(mat1.multiply(mat2));
    }

    @Test
    void testMultiplyDifferentsDimensions() {
        int[][] matrix1 = {{1, 2, 3}, {4, 5, 6}};
        int[][] matrix2 = {{1, 2}, {3, 4}, {5, 6}};
        int[][] matrix3 = {{22, 28, 0}, {49, 64, 0}};


        Matrix mat1 = new Matrix(matrix1);
        Matrix mat2 = new Matrix(matrix2);
        Matrix mat3 = new Matrix(matrix3);

        Assertions.assertNotEquals(mat3, mat1.multiply(mat2));

    }
    @Test
    void testMultiplyInvalidNull() {
        int[][] matrix1 = {{1, 2, 3}, {4, 5, 6}};

        Matrix mat1 = new Matrix(matrix1);

        Assertions.assertThrows(RuntimeException.class, () -> {
            mat1.multiply(null);
        });
    }
    @Test
    void testMultiplyInValidDifferentDimensions() {
        int[][] matrix1 = {{1, 2}, {3, 4}};
        int[][] matrix2 = {{2, 0, 1}, {1, 2, 3}};

        Matrix mat1 = new Matrix(matrix1);
        Matrix mat2 = new Matrix(matrix2);
        Assertions.assertThrows(ArrayIndexOutOfBoundsException.class , () -> mat1.multiply(mat2));
    }
}
