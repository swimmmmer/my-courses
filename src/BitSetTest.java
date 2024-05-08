// Javeria Hanif
// CMSC 425
// Test cases implementation for BitSet
// Feb 11 2022

import static org.junit.jupiter.api.Assertions.*;

import org.junit.Rule;
import org.junit.jupiter.api.Test;
import org.junit.jupiter.api.BeforeEach;
import org.junit.rules.ExpectedException;

import java.util.BitSet;



public class BitSetTest {
    private int nbits;
    private int negBits;
    private int index;

    public void setupFixture() {
        nbits = 8;
        index = 2;
    }

    // Creates a bit set whose initial size is large enough to explicitly
    // represent bits with indices in the range 0 through nbits-1.
    // All bits are initially false.
    // Parameters: nbits - the initial size of the bit set
    public void testBitSet1() {
        BitSet bit = new BitSet(nbits);
        assertEquals(8, bit.length());

    }

    //Throws NegativeArraySizeException if the specified initial size is negative
    public void testBitSet2() {
        negBits = -1;
        assertThrows(NegativeArraySizeException.class, () -> {
            BitSet bit = new BitSet(negBits);
        });
    }

    public void testBitSet3() {
        BitSet bit = new BitSet(nbits);
        for (int i = 0; i < nbits; i++) {
            assertFalse(bit.get(i));
        }
    }

    // Returns the value of the bit with the specified index.
    // The value is true if the bit with the index bitIndex is
    // currently set in this BitSet; otherwise, the result is false.
    // bitIndex - the bit index
    public void testSetGet1() {
        BitSet bit = new BitSet(nbits);
        assertEquals(false, bit.get(index));
        bit.set(index);
        assertEquals(true, bit.get(index));
    }

    // Throws IndexOutOfBoundsException if the specified index is negative
    public void testSet2() {
        BitSet bit = new BitSet(nbits);
        assertThrows(IndexOutOfBoundsException.class, () -> {
            bit.set(negBits);
        });
    }

    // Returns the value of the bit with the specified index
    // Throws IndexOutOfBoundsException if the specified index is negative
    public void testGet2() {
        BitSet bit = new BitSet(nbits);
        assertThrows(IndexOutOfBoundsException.class, () -> {
            bit.get(negBits);
        });
    }


    // sets the bit at specified index to the complement of its current value
    // bitIndex - the index of the bit to flip
    //Throws IndexOutOfBoundsException if the specified index is negative
    public void testFlip1() {
        BitSet bit = new BitSet(nbits);
        bit.flip(index);
        assertEquals(true, bit.get(index));
    }

    public void testFlip2() {
        BitSet bit = new BitSet(nbits);
        bit.set(index);
        bit.flip(index);
        assertEquals(false, bit.get(index));
    }

    public void testFlip3() {
        BitSet bit = new BitSet(nbits);
        assertThrows(IndexOutOfBoundsException.class, () -> {
            bit.flip(negBits);
        });
    }



}
