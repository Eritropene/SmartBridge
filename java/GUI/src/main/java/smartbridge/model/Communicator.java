package smartbridge.model;

import smartbridge.GUI.MainController;

/**
 * Rappresenta un comunicatore, che scambia informazioni attraverso un apposito protocollo
 * */
public interface Communicator {
	
	public void init(MainController controller);
	
	public void listen();
	
	public void sendData(String data);
	
}
