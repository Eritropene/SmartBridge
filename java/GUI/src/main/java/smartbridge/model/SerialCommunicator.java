package smartbridge.model;

import smartbridge.GUI.MainController;

public class SerialCommunicator implements Communicator {

	private static final int RATE = 9600;
	private static final double MAX_WATER_LEVEL = 10;
	
	private CommChannel channel;
	private MainController controller;
	
	private double wl = 0.0;
	private boolean alarmState = false;
	private boolean canActivateManual = true;
	private Timer chartDataSender = new Timer(50, () -> controller.addPointToChart(wl));
	
	public SerialCommunicator(String port) throws Exception{
		this.channel = new Test2CommChannel(port, RATE);
	}
	
	public void init(MainController controller) {
		this.controller = controller;
	}
	
	@Override
	public void listen() {
		new Thread(() -> {
			
			while (true) {
				try {
					while (channel.isMsgAvailable()) {
						decode(channel.receiveMsg());
					}
					
					if (alarmState) {
						
					}
					
					//wait a bit
					Thread.sleep(10);
				} catch (Exception e) {}				
			}
		}).start();
		chartDataSender.start();
	}
	
	private void decode(String msg) {
		var t = msg.split(":");
		
		/* DECODE THE MSG */
		switch (t[0]) {
		case "LIGHT":
			controller.setLightImgVisible(t[1].equals("ON"));
			controller.setLedLabelText("LIGHT: "+t[1]);
			break;
		case "LIGHTSENSEOR":
			controller.setLightSensorLabelText("LIGHT SENSOR: "+t[1]);
			break;
		case "THRESHOLD":
			controller.setTHLabelText("THRESHOLD: "+t[1]);
			break;
		case "PIR":
			controller.setLightImgVisible(t[1].equals("detected"));
			controller.setPirLabelText("PIR: "+t[1]);
			break;
		case "STATE":
			controller.setStateLabelText("STATE: "+t[1]);
			this.alarmState = t[1].equals("ALARM");
			if (alarmState) {
				this.controller.enableAutoMotorPane();
			} else {
				this.controller.disableMotorPane();
			}
			break;
		case "WATERLEVEL":
			wl = MAX_WATER_LEVEL - Double.parseDouble(t[1]);
			controller.setWaterLevelLabelText("WATER LEVEL: "+ wl + "m");
			break;
		case "WL1":
			controller.setWL1LabelText("WL1: "+t[1]);
			break;
		case "WL2":
			controller.setWL2LabelText("WL2: "+t[1]);
			break;
		case "MOTOR":
			controller.setMotorLabelText("MOTOR: "+t[1]);
			break;
		case "BUTTON":
			this.canActivateManual = !canActivateManual;
			break;
		}
	}

	@Override
	public void sendData(String data) {
		this.channel.sendMsg(data);
		System.out.println(data);
	}
	
	public void changeMotorValue(int val) {
		if (alarmState) {
			sendData("MOTOR:"+val);
		}
	}
	
	public void setToManual() {
		if (this.canActivateManual) {
			this.channel.sendMsg("MANUAL");
			this.controller.enableManualMotorPane();
		}
	}
	
	public void setToAuto() {
		this.channel.sendMsg("AUTO");
		this.controller.enableAutoMotorPane();
	}
	
	private class Timer extends Thread {
		
		private final long period;
		private Runnable action;
		
		public Timer(final long period, Runnable action) {
			this.action = action;
			this.period = period;
		}
		@Override
		public void run() {
			while (true) {
				action.run();
				try {
					Thread.sleep(period);
				} catch (Exception e) {}
			}
		}
	}

}
