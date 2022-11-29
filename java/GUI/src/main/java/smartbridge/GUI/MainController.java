package smartbridge.GUI;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.application.Platform;
import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.AreaChart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.control.Button;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;
import javafx.scene.image.ImageView;
import javafx.scene.layout.AnchorPane;
import smartbridge.model.SerialCommunicator;

public class MainController implements Initializable{
	
	private static final int MAX_LENGHT_OF_CHART = 50;
	
	private SerialCommunicator comm;
	@FXML
	private Label ledLabel;
	@FXML
	private Label lsLabel;
	@FXML
	private Label thLabel;
	@FXML
	private Label pirLabel;
	@FXML
	private Label stateLabel;
	@FXML
	private Label wlLabel;
	@FXML
	private Label wl1Label;
	@FXML
	private Label wl2Label;
	@FXML
	private Label motorLabel;
	@FXML
	private Slider slider;
	@FXML
	private AnchorPane motorPane;
	@FXML
	private Button manualButton;
	@FXML
	private Button autoButton;
	@FXML
	private AreaChart<Double, Double> chart;
	@FXML
	private NumberAxis xAxis;
	@FXML
	private NumberAxis yAxis;
	@FXML
	private ImageView lightImage;
	@FXML
	private ImageView pirImage;
	
	private AreaChart.Series<Double, Double> series = new AreaChart.Series<>();
	
	public MainController(SerialCommunicator comm) {
		this.comm = comm;
	}
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		initChart();
		
		lightImage.setVisible(false);
		pirImage.setVisible(false);
		
		ledLabel.setText("LIGHT: OFF");
		
		disableMotorPane();
		
		slider.valueProperty().addListener((a0, a1, a2) -> {
			comm.changeMotorValue((int)slider.getValue());
		});
	}
	
	@FXML
    private void setMotorToManual() throws IOException {
		comm.setToManual();
    }
	
	@FXML
    private void setMotorToAuto() throws IOException {
		comm.setToAuto();
    }
	
	public void setLedLabelText(String txt) {
		Platform.runLater(() -> ledLabel.setText(txt));
	}
	public void setLightSensorLabelText(String txt) {
		Platform.runLater(() -> lsLabel.setText(txt));
	}
	public void setTHLabelText(String txt) {
		Platform.runLater(() -> thLabel.setText(txt));
	}
	public void setPirLabelText(String txt) {
		Platform.runLater(() -> pirLabel.setText(txt));
	}
	public void setStateLabelText(String txt) {
		Platform.runLater(() -> stateLabel.setText(txt));
	}
	public void setWaterLevelLabelText(String txt) {
		Platform.runLater(() -> wlLabel.setText(txt));
	}
	public void setWL1LabelText(String txt) {
		Platform.runLater(() -> wl1Label.setText(txt));
	}
	public void setWL2LabelText(String txt) {
		Platform.runLater(() -> wl2Label.setText(txt));
	}
	public void setMotorLabelText(String txt) {
		Platform.runLater(() -> motorLabel.setText(txt));
	}
	public void setLightImgVisible(boolean value) {
		Platform.runLater(() -> lightImage.setVisible(value));
	}
	public void setPirImgVisible(boolean value) {
		Platform.runLater(() -> pirImage.setVisible(value));
	}
	
	private void initChart() {
        yAxis.setAutoRanging(false); //prevent automatic resizing for simplicity
        
        xAxis.setTickLabelsVisible(false);
        xAxis.setLowerBound(0);
        xAxis.setUpperBound(MAX_LENGHT_OF_CHART - 1);
        
        yAxis.setUpperBound(SerialCommunicator.MAX_WATER_LEVEL);
        yAxis.setLowerBound(0);
        yAxis.setTickUnit(0.5);
        chart.getData().add(series);
        chart.setCreateSymbols(false);
        chart.setAnimated(false);
        
        for (int i = 0; i < MAX_LENGHT_OF_CHART; i++) {
        	series.getData().add(new Data<Double, Double>((double)i,0.0));
        }
	}
	
	public void addPointToChart(Double value) {
		Platform.runLater(() -> {
			var d = series.getData().get(0);
			for (int i = 1; i < MAX_LENGHT_OF_CHART; i++) {
				var e = series.getData().get(i);
				d.setYValue(e.getYValue());
				d = e;
			}
			d.setYValue(value);
		});
	}
	
	public void disableMotorPane() {
		this.slider.setDisable(true);
		this.autoButton.setDisable(true);
		this.manualButton.setDisable(true);
	}
	
	public void enableAutoMotorPane() {
		this.slider.setDisable(true);
		this.autoButton.setDisable(true);
		this.manualButton.setDisable(false);
	}
	public void enableManualMotorPane() {
		this.slider.setDisable(false);
		this.autoButton.setDisable(false);
		this.manualButton.setDisable(true);
	}
}
