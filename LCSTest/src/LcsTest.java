// Javeria Hanif
// CMSC 425
// Test cases implementation for LCS
// Feb 26 2022

import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;

import static org.junit.jupiter.api.Assertions.assertEquals;
import static org.junit.jupiter.api.Assertions.assertNotEquals;

public class LcsTest {
    private String x;
    private String y;

    @BeforeEach
    public void setupFixture() {
        x = "GGCACCACG";
        y = "ACGGCGGATACG";
    }

    @Test
    public void testSubsequenceExact() {
        String z = LCS.lcs(x, y);
        assertEquals("GGCAACG", z);
    }

    @Test
    public void testSubsequenceFail() {
        String z = LCS.lcs(x, y);
        assertNotEquals("GGCAAC", z);
    }

    @Test
    public void testSubsequenceLength() {
        String z = LCS.lcs(x, y);
        assertEquals(7, z.length());
    }

    @Test
    public void testSubsequenceEmpty1() {
        x = "BKKB";
        String z = LCS.lcs(x, y);
        assertEquals("", z);
    }

    @Test
    public void testSubsequenceEmpty2() {
        y = "FRFRFR";
        String z = LCS.lcs(x, y);
        assertEquals("", z);
    }

    @Test
    public void testSubsequenceEmpty() {
        String z = LCS.lcs(x, y);
        assertEquals("", z);
    }

    @Test
    public void testNoSubsequence() {
        x = "BKKB";
        y = "FRFRFR";
        String z = LCS.lcs(x, y);
        assertEquals("", z);
    }

    @Test
    public void testSameSubsequence() {
        x = "DETSY";
        y = "DETSY";
        String z = LCS.lcs(x, y);
        assertEquals("DETSY", z);
    }
}
