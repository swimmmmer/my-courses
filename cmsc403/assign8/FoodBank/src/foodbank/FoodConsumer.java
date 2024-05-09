/*
 * Javeria Hanif 
 * Apr 22, 2024
 * CMSC 403 Spring 2024 
 * FoodConsumer is a thread class that generates a random number from 1-100 and takes that much amount from the 
 * FoodBank object. Then the thread goes to sleep for some time 
 */

package foodbank;

// import statement 
import java.util.Random;

public class FoodConsumer extends Thread {
    private final FoodBank bank; // FoodBank object

    // this constructor initialized the FoodBank object
    public FoodConsumer(FoodBank bank) {
        this.bank = bank;
    }

    // thread starts
    @Override
    public void run() {

        while (true) {
            Random random = new Random(); // initialized the random number generator
            int amount = random.nextInt(100)+1; // generates a random number between 1 to 100
            bank.takeFood(amount); // takes the food based on the random amount generated

            try {
                Thread.sleep(100); // thread goes to sleep for 100 milliseconds
                // breaks the thread at interruption
                if (Thread.currentThread().isInterrupted()) {
                    break;
                }
            // catches any interruptions
            } catch (InterruptedException e) {
                return;
            }
        }
    }
}
