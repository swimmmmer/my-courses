import java.net.*;
import java.util.Random;
import java.util.Scanner;

public class PINGServer {

    public static void main(String[] args) throws Exception
    {
	// socket variables
	DatagramSocket serverSocket = null; //DatagramSocket object
	// byte[] array to store data being sent/received
	byte[] receiveData = new byte[1024];
	byte[] sendData = new byte[1024];
	InetAddress IPAddress;
	int clientPort;

	// server variables
	String serverSentence = "";

	// command-line arguments
	int port = 0;
	int loss = 0;

	// process command-line arguments
	if (args.length < 2) { // if not at least 2 arguments
	    System.out.println ("Usage: java PINGServer port loss\n"); // program prints an error message
	    System.exit (-1); // program exits
	}

	try {
		port = Integer.parseInt(args[0]); // parsing port into integer value
	}
	catch (NumberFormatException e) { // catch block catches the NumberFormatException that is thrown
		System.out.println ("ERR - arg 1"); // program prints an error message
		System.exit (-1); // program exits
	}

	/* if successfully parsed then checks if port is <= 10000 and >= 11000 */
	if (port <= 10000 || port >= 11000) {
		System.out.println ("ERR - arg 1"); // program prints error message if port is outside range
		System.exit (-1); // program exits
	}

	try {
		loss = Integer.parseInt(args[1]); // parsing loss into integer value
	}
	catch (NumberFormatException e) { // catch block catches the NumberFormatException that is thrown
		System.out.println ("ERR - arg 2"); // program prints an error message
		System.exit (-1); // program exits
	}

	if (loss < 0 || loss > 100) { // if loss is less than 0 or greater than 100
		System.out.println ("ERR - arg 2"); // program prints an error message
		System.exit (-1); // program exits
	}

	try {
		serverSocket = new DatagramSocket(port);  // creates DatagramSocket object
	} catch (SocketException e) { // catch block catches SocketException that is thrown
		System.out.println("ERR - Cannot create UDPServer socket using port number " + port); // program prints an error message
		System.exit(-1); // program exits
	}
	// print statement
	System.out.println("PINGServer started with server IP: " + InetAddress.getLocalHost().getHostAddress() + ", port: " + port + "...");

	// prints a message indicating that the server is now listening on the specified port
	System.out.println("Listening on port " + port + "...");

		// While loop to handle arbitrary sequence of clients making requests
			//  enters an infinite loop to continuously listen for client requests
		while (true) {
			serverSentence = "";
			// Waits for some client to send a packet
			DatagramPacket receivePacket = new DatagramPacket // packet to receive data from a client
			(receiveData,receiveData.length);
			serverSocket.receive(receivePacket);

			/* the server will generates a random integer number in the range of [1,
			100]. If the randomized integer is less than or equal to <loss>, the server ignores
			the received packet (simulating a packet drop). If the randomized integer is greater
			than <loss>, the server resumes normally and handle the received packet as describe
			earlier */

			Random rand = new Random();
			int lossRt = 1 + rand.nextInt(100);

			// converts the received data to a String and prints it to the console
			String clientSentence = new String(receivePacket.getData(), 0, receivePacket.getLength()); // add UTF-8 to handle ASCII chars
			Scanner input = new Scanner(clientSentence);

			// Write output line to socket
			IPAddress = receivePacket.getAddress();
			clientPort = receivePacket.getPort();
			String version = input.nextLine();
			String clientID = input.nextLine();
			String numSeq = input.nextLine();
			String payload = input.nextLine();
			String timestamp = input.nextLine();

			if (lossRt <= loss) {
				System.out.println("IP:" + IPAddress + " :: Port:" + port + " : Client ID:" + clientID + " :: Seq#:" + numSeq + " :: DROPPED");
			} else {
				System.out.println("IP:" + IPAddress + " :: Port:" + port + " : Client ID:" + clientID + " :: Seq#:" + numSeq + " :: RECEIVED");

				String hostname = input.nextLine().split(":")[1];
				String classname = input.nextLine().split(":")[1];
				String username = input.nextLine().split(":")[1];
				String rest = input.nextLine().split(":")[1];

				System.out.println("----------- Received Ping Response Packet Header ----------");
				System.out.println(version); // this will print "Version: 1"
				System.out.println(clientID); // client ID
				System.out.println(numSeq); // sequence number
				System.out.println(payload); // timestamp
				System.out.println(timestamp); // payload
				System.out.println("--------- Received Ping Response Packet Payload ------------");
				System.out.println("Host: " + hostname); // host name
				System.out.println("Class-name: " + classname); // class name
				System.out.println("User-name: " + username); // user name
				System.out.println("Rest: " + rest); // rest
				System.out.println("---------------------------------------");

				serverSentence += version + "\n" + clientID + "\n" + numSeq + "\n" + payload + "\n" + timestamp + "\n";
				serverSentence += "Host-name: " + hostname.toUpperCase() + "\n";
				serverSentence += "Class-name: " + classname.toUpperCase() + "\n";
				serverSentence += "User-name: " + username.toUpperCase() + "\n";
				serverSentence += "Rest: " + rest.toUpperCase();

				System.out.println("---------- Ping Request Packet Header ----------\n");
				System.out.println(version); // this will print "Version: 1"
				System.out.println(clientID); // client ID
				System.out.println(numSeq); // sequence number
				System.out.println(payload); // timestamp
				System.out.println(timestamp); // payload
				System.out.println("--------- Ping Request Packet Payload ------------\n");
				System.out.println("Host-name: " + hostname.toUpperCase());
				System.out.println("Class-name: " + classname.toUpperCase()); // class name
				System.out.println("User-name: " + username.toUpperCase()); // user name
				System.out.println("Rest: " + rest.toUpperCase()); // rest
				System.out.println("---------------------------------------");

				sendData = serverSentence.getBytes();
				DatagramPacket sendPacket = new DatagramPacket(sendData,
						sendData.length,
						IPAddress,
						clientPort); // new packet with server's response and sends it back to the client
				serverSocket.send(sendPacket);
			}
		} //  end while; loop back to accept a new client connection
	} // end main
} // end class
