//import statements
import java.io.*;
import java.net.*;
import java.nio.charset.StandardCharsets;
import java.util.Date;
import java.util.Random;
import java.util.Scanner;
import java.util.Base64;
import java.util.UUID;

/*  this code sets up the necessary variables for a UDP client socket to communicate with a server over the
network. It processes command-line arguments to determine the IP address and port number of the server, and
sets up data structures for sending and receiving data over the socket.
 */
public class PINGClient {
	// static main method throws exception
    public static void main(String[] args) throws Exception
    {
	// UDP socket variables to send/receive packets of data
	DatagramSocket clientSocket = null; // creates DatagramSocket that represents UDP socket
	// creates DatagramPacket that represents UDP packet
	DatagramPacket sendPacket;
	DatagramPacket receivePacket;
	// byte[] array to store data being sent/received
	byte[] receiveData = new byte[1024];
	byte[] sendData = new byte[1024];
	InetAddress IPAddress = null; // creates InetAddress object that used to store IP address of server

	// client variables to send/receive data from client and server
	String clientSentence = "";
	String serverSentence = "";

	// command-line arguments stores server's port and IP address on which server is listening
	String hostname; // host or ip of ping server
	int port = 0; // port number server is running on
	int clientID;
	int numPackets; // number of ping request packets to send to server
	int waitTime; // time that client has to wait to get a response for each request packet

	// process command-line arguments
	if (args.length < 5) { // if not at least 5 arguments
		System.out.println ("Usage: java PINGClient hostname port clientID numPackets waitTime\n"); // program prints an error message
		System.exit (-1); // program exits
	}

	/*
	* tries to convert string into integer,
	* if it cannot be done then throws an exception */
	try {
		port = Integer.parseInt(args[1]); // parsing port into integer value
	}
	catch (NumberFormatException e) { // catch block catches the NumberFormatException that is thrown
		System.out.println ("ERR - arg 2"); // program prints an error message
		System.exit (-1); // program exits
	}

	/* if successfully parsed then checks if port is <= 10000 and >= 11000 */
	if (port <= 10000 || port >= 11000) {
		System.out.println ("ERR - arg 2"); // program prints error message if port is outside range
		System.exit (-1); // program exits
	}
	// initialization
	hostname = args[0];
	// int parse method used to convert from string to int
	clientID = Integer.parseInt(args[2]);
	numPackets = Integer.parseInt(args[3]);
	waitTime = Integer.parseInt(args[4]);

	try {
		clientSocket = new DatagramSocket(); // creates DatagramSocket object
	} catch (SocketException e) { // catch block catches SocketException that is thrown
		System.out.println("ERR - Cannot create UDPServer socket using port number " + port); // program prints error message
		System.exit(-1); // program exits
	}

	try {
		/*
	InetAddress object is obtained by calling static getByName method
	and passing it to hostname of server */
		IPAddress = InetAddress.getByName (hostname);
	}
	catch (UnknownHostException ex) { // catch block catches UnknownHostException that is thrown
		System.out.println ("ERR - arg 1"); // program prints error message
		System.exit (-1); // program exits
	}

	// print statement
	System.out.println ("PINGClient started with server IP: " + hostname + " port: " + port + " client ID: " + clientID + " packets: " + numPackets + " wait: " + waitTime);

	// initialization
	double minRtt = 1000000;
	double maxRtt = -1;
	double avgRtt = 0;
	double sumRtt = 0;
	int avgPayload = 0;
	int sumPayload = 0;
	int packetsRcv = 0;
	int numPacketsLoss = 0;
	double packetLossRt = 0;
	int totalPackets = numPackets;

	/*
	* for loop runs numPackets times */
	for (int i = 1; i <= numPackets; i++) {
		clientSentence = "";
		Random rand = new Random(); // creates an instance of Random class
		// PING header
		int numSeq = i; // stores sequence number of the packet being sent
		long timestamp = System.currentTimeMillis(); // stores current system time when the packet is being sent

		// PING payload
		int payload = 150 + rand.nextInt(150); // generates a random payload size between 150 and 300 bytes
		sumPayload += payload; // adds current payload to the sumPayload
		/* clientSentence contains the PING header and payload information for the packet being sent*/
		clientSentence += "Version: 1\n" + "ClientID: " + clientID + "\nSequence No.: " + numSeq + "\nTime: " + timestamp + "\nPayload Size: " + payload + "\n";
		String clientHost = InetAddress.getLocalHost().getHostAddress(); // gets the IP address of local machine where program is running
		/* contains info for packet being sent */
		String host = ("Host: " + clientHost + "\n");
		String classname = ("Class-name: VCU-CMSC440-SPRING-2023\n");
		String username = ("User-name: Hanif, Javeria\n");
		String data = host + classname + username + "Rest: ";
		clientSentence += data; // concatenates data to clientSentence
		/*// gets byte array representation of data in UTF-8 character
		encoding to get random alphanumeric chars then gets its length in bytes */
		int size = data.getBytes(StandardCharsets.UTF_8).length;
		int remaining = payload - size; // calculates the remaining amount of bytes to be added to clientSentence

		String rest = randString(remaining); // assigns randomly generated String with a length of remaining to rest
		clientSentence += rest; // // concatenates rest to clientSentence

		// ping request packet-print statements
		System.out.println("\n---------- Ping Request Packet Header ----------");
		System.out.println("Version: 1");
		System.out.println("Client ID: " + clientID);
		System.out.println("Sequence No.: " + numSeq);
		System.out.println("Time: " + timestamp);
		System.out.println("Payload Size: " + payload);
		System.out.println("--------- Ping Request Packet Payload ------------");
		System.out.println(host + classname + username + "Rest: " + rest);
		System.out.println("---------------------------------------");

		sendData = clientSentence.getBytes(); // gets byte array representation of clientSentence and assigns it to sendData

		// DatagramPacket object contains data to be sent to server
		sendPacket = new DatagramPacket(sendData, sendData.length, IPAddress, port); // Create packet and send to server
		clientSocket.send(sendPacket); // sends packet to server
		clientSocket.setSoTimeout(waitTime * 1000); // sets a timeout to waitTime seconds * 1000 (for milliseconds) for clientSocket object

		// try catch block
		try {
			receivePacket = new DatagramPacket(receiveData, receiveData.length); // DatagramPacket object contains data received from server

			// waits for data to be received from server
			clientSocket.receive(receivePacket);
			packetsRcv++; // number of packets received from the server
			serverSentence = new String(receivePacket.getData(), 0, receivePacket.getLength()); // gets data and assigns it to serverSentence
			Scanner input = new Scanner(serverSentence); // Scanner object to parse serverSentence
			long timestamp1 = System.currentTimeMillis(); // get current time in milliseconds and stores it
			// print received statements
			System.out.println("\n----------- Received Ping Response Packet Header ----------");
			System.out.println(input.nextLine()); // version
			System.out.println(input.nextLine()); // client ID
			System.out.println(input.nextLine()); // sequence number
			System.out.println(input.nextLine()); // timestamp
			System.out.println(input.nextLine()); // payload
			System.out.println("--------- Received Ping Response Packet Payload ------------");
			System.out.println(input.nextLine()); // host name
			System.out.println(input.nextLine()); // class name
			System.out.println(input.nextLine()); // user name
			System.out.println(input.nextLine()); // rest
			System.out.println("---------------------------------------");

			// calculates rtt
			double rtt = (double)timestamp1 - timestamp;

			// if rtt is less than min rtt then it is updated to rtt
			if (rtt < minRtt) {
				minRtt = rtt;
			}

			// if rtt is greater than max rtt then it is updated to rtt
			if (rtt > maxRtt) {
				maxRtt = rtt;
			}
			sumRtt += rtt; // adds rtt to sumRtt

			// prints rtt
			System.out.printf("RTT: %.2f seconds\n", rtt);

		} catch (SocketTimeoutException ex) { // catch block catches SocketTimeoutExceptio that is thrown
			// prints timeout message
			System.out.println("--------------- Ping Response Packet Timed-Out ------------------");
			// increments num packets lost
			numPacketsLoss++;
		}
	}
		// calculates average Rtt
		avgRtt = sumRtt / packetsRcv;
		// calculates average Payload
		avgPayload = sumPayload / totalPackets;
		// calculates packet loss rate as a percentage and multiplies the result by 100
		packetLossRt = ((double)numPacketsLoss / numPackets) * 100;

		// prints summary
		System.out.printf("...\n");
		System.out.printf("...\n");
		System.out.printf("\nSummary: %d :: %d :: %.0f%% :: %.2f :: %.2f :: %.2f :: %d\n", totalPackets, packetsRcv, packetLossRt, minRtt, maxRtt, avgRtt, avgPayload);

	// close the socket to free up resources
	clientSocket.close();
    } // end main

	public static String randString(int remaining) { // public random string that takes int remaining as argument method

		// instances of Random class
		Random random1 = new Random();
		Random random2 = new Random();
		StringBuilder randString = new StringBuilder(); // StringBuilder object to build random string

		// for loop runs remaining times
		for (int i = 0; i < remaining; i++) {
			int whatChar = 1 + random2.nextInt(4); // generates random integer between 1-4
			if (whatChar == 1) { // if equal to 1
				int randomInt = 48 + random1.nextInt(9); // generates random digit char by adding a random integer between 0 and 8 to the ASCII code for the digit 0-9
				randString.append((char) randomInt);
			}
			else if (whatChar == 2 || whatChar == 3){ // if equal to 2 or 3
				// generates random uppercase letter by adding a random integer between 0 and 24 to the ASCII code for the uppercase letter A-Z
				int randomInt = 65 + random1.nextInt(25);
				randString.append((char) randomInt);
			}
			else {
				// generates random lowercase letter character by adding a random integer between 0 and 24 to the ASCII code for the lowercase letter a-z
				int randomInt = 97 + random1.nextInt(25);
				randString.append((char) randomInt);
			}
		}
		return randString.toString();
	}
} // end class
