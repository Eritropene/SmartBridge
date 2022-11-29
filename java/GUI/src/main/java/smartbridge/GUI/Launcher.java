package smartbridge.GUI;

import java.util.Scanner;

import javafx.application.Application;
import jssc.SerialPortList;

public class Launcher {

	public static String PORT;
	
	public static void main(String[] args) {
		
		Scanner in = new Scanner(System.in);
		
		System.out.println("Select the Serial Port:");
		System.out.print("  -  ");
		for (var port : SerialPortList.getPortNames()) {
			System.out.print(port + "  -  ");
		}
		System.out.println();
		
		PORT = in.nextLine();

		//PORT = args[0];
		//PORT = "COM1";
		Application.launch(App.class);
	}
	
}
