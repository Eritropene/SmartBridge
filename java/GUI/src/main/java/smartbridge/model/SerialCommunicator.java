package smartbridge.model;

import smartbridge.GUI.MainController;

public class SerialCommunicator implements Communicator {

	static final int RATE = 9600;
	private CommChannel channel;
	private MainController controller;
	
	public SerialCommunicator(String port, MainController controller) throws Exception{
		//channel = new SerialCommChannel(port, RATE);
		controller = controller;
	}
	
	@Override
	public void listen() {
		new Thread(() -> {
			while (true) {
				/*
				 * superloop
				 * */
				System.out.println("i");
				System.out.println("a");
				System.out.println("4");
			}
		}).start();
	}

	@Override
	public void sendData(String data) {
		// TODO Auto-generated method stub

	}

}
