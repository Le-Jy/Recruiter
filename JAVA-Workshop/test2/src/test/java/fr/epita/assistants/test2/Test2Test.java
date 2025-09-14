package fr.epita.assistants.test2;

import fr.epita.assistants.server.MyServer;
import fr.epita.assistants.test2.Test2;
import org.junit.jupiter.api.Assertions;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.Timeout;

import java.io.IOException;

public class Test2Test {
    @Test
    void testValidDivision() {
        Assertions.assertEquals(2, Test2.division(6, 3));
    }

    @Test
    void testDivisionByZero() {
        Assertions.assertThrows(ArithmeticException.class, () -> {
            Test2.division(1, 0);
        });
    }

    @Test
    void testZeroDivision() {
        Assertions.assertEquals(0, Test2.division(0, 1));
    }

    @Test
    void testNegativeDivision() {
        Assertions.assertEquals(-2, Test2.division(-6, 3));
    }

    @Test
    void testBothNegativeDiv() {
        Assertions.assertEquals(2, Test2.division(-6, -3));
    }

    @Test
    void testInvalidTribo() {
        Assertions.assertThrows(IllegalArgumentException.class, () -> {
            Test2.tribonacci(-1);
        });
    }

    @Test
    void testValidTribo() {
        Assertions.assertEquals(0, Test2.tribonacci(0));
        Assertions.assertEquals(1, Test2.tribonacci(1));
        Assertions.assertEquals(1, Test2.tribonacci(2));
        Assertions.assertEquals(2, Test2.tribonacci(3));
        Assertions.assertEquals(4, Test2.tribonacci(4));
        Assertions.assertEquals(7, Test2.tribonacci(5));
        Assertions.assertEquals(13, Test2.tribonacci(6));
        Assertions.assertEquals(24, Test2.tribonacci(7));
    }
    @Test
    @Timeout(1)
    void testTimeoutTribo() {
        Test2.tribonacci(999999999);
    }


    @Test
    void testServerGetResponseCode() {
        try {
            MyServer.launchServer();
        } catch (IOException e) {
            Assertions.fail("Failed to launch server: " + e.getMessage());
        }

        try {
            long responseCode = Test2.serverGetResponseCode();
            Assertions.assertEquals(200, responseCode, "Unexpected response code from server");
        } catch (IOException e) {
            Assertions.fail("Failed to get response code from server: " + e.getMessage());
        }

        MyServer.stopServer();
    }

    @Test
    void testDoubleServerLaunch() {
        try {
            MyServer.launchServer();
            MyServer.launchServer();
        } catch (IOException e) {
            Assertions.assertEquals("Address already in use", e.getMessage());
        }
        MyServer.stopServer();
    }

    @Test
    @Timeout(1)
    void testServerGetResponseCodeWithTimeout() {
        try {
            MyServer.launchServer();
        } catch (IOException e) {
            Assertions.fail("Failed to launch server: " + e.getMessage());
        }

        try {
            long responseCode = Test2.serverGetResponseCode();
            Assertions.assertEquals(200, responseCode, "Unexpected response code from server");
        } catch (IOException e) {
            Assertions.fail("Failed to get response code from server: " + e.getMessage());
        }

        MyServer.stopServer();
    }
}
