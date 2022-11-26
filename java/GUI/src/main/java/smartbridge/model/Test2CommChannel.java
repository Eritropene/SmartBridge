package smartbridge.model;

import java.util.LinkedList;
import java.util.Queue;
import java.util.Random;

public class Test2CommChannel implements CommChannel {

	private long t = 0;
	private Random r = new Random();
	private Queue<String> q = new LinkedList<>();
	
	public Test2CommChannel(String port, int rate) {
		q.add("MOTOR:" + r.nextInt(181));
		q.add("MOTOR:" + r.nextInt(181));
		q.add("MOTOR:" + r.nextInt(181));
		q.add("MOTOR:" + r.nextInt(181));
		q.add("STATE:ALARM");
		q.add("MOTOR:" + r.nextInt(181));
		q.add("MOTOR:" + r.nextInt(181));
		q.add("STATE:NORMAL");
		q.add("MOTOR:" + r.nextInt(181));
	}
	
	@Override
	public void sendMsg(String msg) {
		// TODO Auto-generated method stub

	}

	@Override
	public String receiveMsg() throws InterruptedException {
		var s = q.poll();
		q.add(s);
		return s;
	}

	@Override
	public boolean isMsgAvailable() {
		// TODO Auto-generated method stub
				if (System.currentTimeMillis() - t > 800) {
					t = System.currentTimeMillis();
					return true;
				}
				return false;
	}

}
