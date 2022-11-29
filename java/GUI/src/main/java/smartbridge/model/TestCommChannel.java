package smartbridge.model;

import java.util.Random;

public class TestCommChannel implements CommChannel {

	private long t = 0;
	private Random r = new Random();
	
	public TestCommChannel(String port, int rate) {
		
	}

	@Override
	public void sendMsg(String msg) {
		// TODO Auto-generated method stub

	}

	@Override
	public String receiveMsg() throws InterruptedException {
		return "WATERLEVEL:"+ (r.nextDouble()%10);
	}

	@Override
	public boolean isMsgAvailable() {
		// TODO Auto-generated method stub
		if (System.currentTimeMillis() - t > 1000) {
			t = System.currentTimeMillis();
			return true;
		}
		return false;
	}

}
