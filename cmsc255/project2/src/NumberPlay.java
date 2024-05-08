import java.util.Scanner;  // Import the Scanner class
public class NumberPlay {
    public static void main(String[] args) {
        Scanner object = new Scanner(System.in); // user input
        int num1  = object.nextInt(); // initial input
        String sumNum = object.nextLine();

        System.out.println("Would you like to randomly generate a number (1) or enter it yourself (2)?");
        System.out.println(num1);

        System.out.println("Enter a 6-digit number");

        if(num1 == ){
                System.out.println("ok!");
        }
        else{
            System.out.println("Incorrect input");
        }

    }

    /* private static int isSixDigitInt(int sumNum) {
        int d1, d2, d3, d4, d5, d6 = 1;
        sumNum = d1 + d2 + d3 + d4 + d5 + d6;
    } */
}
