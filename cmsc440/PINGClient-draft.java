import java.io.*;
import java.net.*;
import java.util.Date;
import java.util.Random;

class PINGClient-draft {

	public static void main(String argv[]) throws Exception
    {
	// socket variables
	DatagramSocket clientSocket;
	DatagramPacket receivePacket;
	byte[] receiveData = new byte[1024];
	byte[] sendData = new byte[1024];
	InetAddress IPAddress = null;

	// client variables
	String clientSentence, serverSentence;
	BufferedReader inFromUser;

	// command-line arguments
	String hostName; // name of ping server
	int port; // port number that server is running on
	int numPackets; // request packet to send to server
	int waitTime; // seconds that client will wait
	String clientID;
	String server;

	// initialization
	hostName = argv[0];
	port = Integer.parseInt(argv[1]);
	numPackets = Integer.parseInt(argv[3]);
	waitTime = Integer.parseInt(argv[4]);
	clientID = argv[2];
	server = argv[0];

	// process command-line arguments
	if (argv.length < 5) {
	    System.out.println ("ERR - arg missing:\n" );
	    System.exit (-1);
	}

	// starting statement
	System.out.println("PINGClient started with server IP: " + IPAddress.getHostAddress()
			+ ", port: " + port + ", client ID: " + clientID
			+ ", packets: " + numPackets + ", wait: " + waitTime);

	IPAddress = InetAddress.getByName (server);
	// Create client socket to receive packets through port
	clientSocket = new DatagramSocket(port);

	// datagram paket to send as a packet
	DatagramPacket sendPacket = new DatagramPacket(sendData, sendData.length, InetAddress.getByName(server), port);
	clientSocket.send(sendPacket); // send datagram to server

	// Create (buffered) input stream using standard input
	inFromUser = new BufferedReader(new InputStreamReader(System.in));

	Random rand = new Random();

	// send multiple packets
	for (int i = 1; i <= numPackets; i++){
		int size = rand.nextInt(151) + 150;
		byte[] payload = new byte[size]; // PING payload
		rand.nextBytes(payload);
	}

	System.out.println("Host: " + hostName + "Class-name: VCU-CMSC440-SPRING-2023" + "User-name: Hanif, Javeria" + "Rest: " + rand);

	// PING header
	byte[] version = new byte[1];
	int client = Integer.parseInt(clientID);
	int numSeq = 1;

	Date now = new Date();
	float timestamp = now.getTime();

	// Get input from user
	System.out.println("Client ready for input");
	clientSentence = inFromUser.readLine();
	sendData = clientSentence.getBytes();

	// Create packet and send to server
	sendPacket = new DatagramPacket(sendData, sendData.length,  
					IPAddress, port);
	clientSocket.send(sendPacket);
	System.out.println ("TO SERVER: " + clientSentence);

	// Create receiving packet and receive from server
	receivePacket = new DatagramPacket(receiveData,
					   receiveData.length); 
	clientSocket.receive(receivePacket);
	serverSentence = new String(receivePacket.getData(), 0,
				    receivePacket.getLength());

	System.out.println("FROM SERVER: " + serverSentence);

	// close the socket
	clientSocket.close();

    } // end main

} // end class
