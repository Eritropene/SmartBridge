package smartbridge.model;

/**
 * Rappresenta un comunicatore, che scambia informazioni attraverso un apposito protocollo
 * */
public interface Communicator {
	
	public void listen();
	
	public void sendData(String data);
	
}
