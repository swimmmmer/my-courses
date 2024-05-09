/*
 * Javeria Hanif 
 * Apr 22, 2024
 * RaceTrack extends the JavaFX application  
 */

package hellofx;

// import statements 
import javafx.application.Application;
import javafx.application.Platform;
import javafx.geometry.Insets;
import javafx.geometry.Pos;
import javafx.scene.Scene;
import javafx.scene.control.Alert;
import javafx.scene.control.Button;
import javafx.scene.control.ButtonType;
import javafx.scene.control.Alert.AlertType;
import javafx.scene.image.Image;
import javafx.scene.layout.HBox;
import javafx.scene.layout.VBox;
import javafx.scene.paint.Color;
import javafx.stage.Stage;
import javafx.scene.shape.*;

import java.io.FileInputStream;
import java.io.InputStream;
import java.util.Random;

public class RaceTrack extends Application {

    // defines thread objects
    private Thread thread1;
    private Thread thread2;
    private Thread thread3;

    // defines rectangle objects 
    private Rectangle rect1;
    private Rectangle rect2;
    private Rectangle rect3;

    // defines imageView objects from javaFX library
    private javafx.scene.image.ImageView imageView1;
    private javafx.scene.image.ImageView imageView2;
    private javafx.scene.image.ImageView imageView3;

    // start method sets up the primary stage
    @Override
    public void start(Stage primaryStage) throws Exception{

        // creates the button objects 
        Button button1 = new Button("Start");
        Button button2 = new Button("Pause");
        Button button3 = new Button("Reset");

        // button styling
        button1.setWrapText(true);
        button2.setWrapText(true);
        button3.setWrapText(true);
        button1.setStyle("-fx-background-color: GREEN;");
        button2.setStyle("-fx-background-color: ORANGE;");
        button3.setStyle("-fx-background-color: RED;");

        // sets up the buttons layout 
        HBox hbox = new HBox(50, button1, button2, button3);
        HBox.setMargin(button1, new Insets(10, 10, 10, 10));
        HBox.setMargin(button2, new Insets(10, 10, 10, 10));
        HBox.setMargin(button3, new Insets(10, 10, 10, 10));
        hbox.setAlignment(Pos.BASELINE_CENTER);

        // initializes the rectangle ojects to represent the tracks
        rect1 = new Rectangle(400, 25);
        rect2 = new Rectangle(400, 25);
        rect3 = new Rectangle(400, 25);

        // sets up the rectangle layout
        VBox vbox = new VBox(10, rect1, rect2, rect3);
        VBox.setMargin(rect1, new Insets(10, 10, 10, 10));
        VBox.setMargin(rect2, new Insets(10, 10, 10, 10));
        VBox.setMargin(rect3, new Insets(10, 10, 10, 10));
        vbox.setAlignment(Pos.CENTER);
        
        // rectangles styling 
        rect1.setFill(Color.BISQUE);
        rect2.setFill(Color.BISQUE);
        rect3.setFill(Color.BISQUE);

        // images filepaths
        InputStream path1 = new FileInputStream("/Users/javeriahanif/spr2024/cmsc403/assign8/RaceTrack/src/hellofx/images/miffyoncycle.png");
        InputStream path2 = new FileInputStream("/Users/javeriahanif/spr2024/cmsc403/assign8/RaceTrack/src/hellofx/images/miffyonscooter.png");
        InputStream path3 = new FileInputStream("/Users/javeriahanif/spr2024/cmsc403/assign8/RaceTrack/src/hellofx/images/miffywalks.png");

        // loads the images from the filepaths
        Image image1 = new Image(path1);
        Image image2 = new Image(path2);
        Image image3 = new Image(path3);

        // initializes the imageView objects to display the images
        imageView1 = new javafx.scene.image.ImageView(image1);
        imageView2 = new javafx.scene.image.ImageView(image2);
        imageView3 = new javafx.scene.image.ImageView(image3);

        // image styling 
        imageView1.setFitWidth(30);
        imageView2.setFitWidth(20);
        imageView3.setFitWidth(30);
        imageView1.setPreserveRatio(true);
        imageView2.setPreserveRatio(true);
        imageView3.setPreserveRatio(true);

        // sets up the image and retangle layout horizontally
        HBox imageBox1 = new HBox(10, imageView1, rect1);
        HBox imageBox2 = new HBox(20, imageView2, rect2);
        HBox imageBox3 = new HBox(10, imageView3, rect3);

        // gets the horizontal position of the imageView object
        double startPoint1 = imageView1.getTranslateX();
        double startPoint2 = imageView2.getTranslateX();
        double startPoint3 = imageView3.getTranslateX();

        // sets up the imageBox layout
        imageBox1.setAlignment(Pos.CENTER_LEFT);
        imageBox2.setAlignment(Pos.CENTER_LEFT);
        imageBox3.setAlignment(Pos.CENTER_LEFT);

        // sets up the general layout of the application vedrtically
        VBox mainVBox = new VBox(10, hbox, imageBox1, imageBox2, imageBox3, vbox);
        mainVBox.setAlignment(Pos.CENTER);
        mainVBox.setPadding(new Insets(20));
        mainVBox.setStyle("-fx-background-color: blue;");

        // scene styling
        Scene scene = new Scene(mainVBox, 500, 200,Color.BLUE);

        // initializes random number generator
        Random random = new Random();

        // defines action on button1 click event 
        button1.setOnAction(e -> {
            // initalizes the first thread and starts it
            thread1 = new Thread(() -> {
                // runs the imageView object until it reaches the finish line of the track 
                while (imageView1.getTranslateX() + imageView1.getFitWidth() < rect1.getWidth() + rect1.getLayoutX()) {
                    // generates a random number between 1-10
                    int moveAmount = random.nextInt(11);
                    // updates the imageView object's position on the thread 
                    Platform.runLater(() -> {
                        imageView1.setTranslateX(imageView1.getTranslateX() + moveAmount);
                    });
                    try {
                        // thread sleeps for 50 milliseconds
                        Thread.sleep(50);
                    } catch (InterruptedException ex) { // catches any interruption
                        return;
                    }
                }
                // interrupts other threads when first candidate wins
                thread2.interrupt();
                thread3.interrupt();
                Platform.runLater(() -> {
                    // displays the winner alert
                    Alert raceAlert = new Alert(AlertType.INFORMATION, "Cyclist (1) Miffy Wins!", ButtonType.OK);
                    raceAlert.show();
                });

            });
        
            // initalizes the second thread and starts it
            thread2 = new Thread(() -> {
                // runs the imageView object until it reaches the finish line of the track 
                while (imageView2.getTranslateX() + imageView2.getFitWidth() < rect2.getWidth() + rect2.getLayoutX()) {
                    int moveAmount = random.nextInt(11); // generates a random number between 1-10
                    // updates the imageView object's position on the thread 
                    Platform.runLater(() -> {
                        imageView2.setTranslateX(imageView2.getTranslateX() + moveAmount);
                    });      
                    try {
                        // thread sleeps for 50 milliseconds
                        Thread.sleep(50);
                    } catch (InterruptedException ex) { // catches any interruption
                        return;
                    }
                }
                // interrupts other threads when second candidate wins
                thread1.interrupt();
                thread3.interrupt();
                Platform.runLater(() -> {
                    // displays the winner alert
                    Alert raceAlert = new Alert(AlertType.INFORMATION, "Miffy (2) on the Scooter Wins!", ButtonType.OK);
                    raceAlert.show();
                });
            });
            // initalizes the third thread and starts it
            thread3 = new Thread(() -> {;
                // runs the imageView object until it reaches the finish line of the track 
                while (imageView3.getTranslateX() + imageView3.getFitWidth() < rect3.getWidth() + rect3.getLayoutX()) {
                    int moveAmount = random.nextInt(11); // generates a random number between 1-10
                    // updates the imageView object's position on the thread 
                    Platform.runLater(() -> {
                        imageView3.setTranslateX(imageView3.getTranslateX() + moveAmount);
                    });
                    try { // thread sleeps for 50 milliseconds
                        Thread.sleep(50);
                    } catch (InterruptedException ex) { // catches any interruption
                        return; 
                    }
                }
                // interrupts other threads when third candidate wins
                thread1.interrupt();
                thread2.interrupt();
                Platform.runLater(() -> {
                    // displays the winner alert
                    Alert raceAlert = new Alert(AlertType.INFORMATION, "Walking Miffy (3) Wins! :D", ButtonType.OK);
                    raceAlert.show();
                });
            });
        
            // startes the threads
            thread1.start();
            thread2.start();
            thread3.start();
        });
        
        // defines action on button2 click event 
        button2.setOnAction(e -> {
            // pauses all threads 
            if (thread1 != null) thread1.interrupt();
            if (thread2 != null) thread2.interrupt();
            if (thread3 != null) thread3.interrupt();
        });
        
        // defines action on button3 click event 
        button3.setOnAction(e -> {
            // resets the positions of the candidates to their starting points 
            imageView1.setTranslateX(startPoint1);
            imageView2.setTranslateX(startPoint2);
            imageView3.setTranslateX(startPoint3);
            // interrupts the threads 
            if (thread1 != null) thread1.interrupt();
            if (thread2 != null) thread2.interrupt();
            if (thread3 != null) thread3.interrupt();
        });

        // sets up the stage and displays it
        primaryStage.setTitle("Miffy's Race Track");
        primaryStage.setScene(scene);
        primaryStage.setResizable(false);
        primaryStage.show();
    }

    // main method
    public static void main(String[] args) {
        launch(args);
    }
}