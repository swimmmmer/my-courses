/*
 * Javeria Hanif 
 * Apr 22, 2024
 * CMSC 403 Spring 2024 
 * FoodBankPatrons is a class that has the main method with FoodBank, FoodProducer, and FoodConsumer objects. 
 * This is where the FoodProducer and FoodConsumer threads will be started. 
 */

package foodbank;

public class FoodBankPatrons {

    // main method
    public static void main(String[] args) {

        // objects initialization
        FoodBank foodBank = new FoodBank(); 
        FoodProducer foodProducer = new FoodProducer(foodBank);
        FoodConsumer foodConsumer = new FoodConsumer(foodBank);

        // threads start
        foodProducer.start();
        foodConsumer.start();
    }
}