/*
 * Javeria Hanif 
 * Apr 22, 2024
 * CMSC 403 Spring 2024 
 * FoodBank is a class that keeps track of the food available and adds and takes food and updates the food count. 
 */

package foodbank;

// FoodBank class 
public class FoodBank {
    private int food; // variable defined to store the food available

    // this constructor initializes the food to 0 
    public FoodBank() { 
        food = 0;
    }

    // giveFood adds food to the food bank and updates the food count 
    public synchronized void giveFood(int amount) {
        food += amount; // increments the food count by the given amount 
        // prints information about the amount added and the food count 
        System.out.println("Added " + amount + " items of food. The total food count is now: " + food); 
        notify(); // notifies threads that waiting to take food
    }

    // takeFood takes food from the food bank and updates the food count 
    public synchronized void takeFood(int amount) {
        if (amount > food) { // if amount is more than the available food 
            try {
                wait(); // waits for more food to be added
            } catch (InterruptedException e) { // handles any interruptions
            }
        }
        else {
            food -= amount; // decrements the food count by the given amount 
             // prints information about the amount taken and the food count 
            System.out.println("Took " + amount + " items of food. The total food count is now: " + food);
        }
    }
}
