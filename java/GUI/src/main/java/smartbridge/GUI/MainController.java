package smartbridge.GUI;

import java.io.IOException;
import java.net.URL;
import java.util.ResourceBundle;

import javafx.fxml.FXML;
import javafx.fxml.Initializable;
import javafx.scene.chart.AreaChart;
import javafx.scene.chart.Chart;
import javafx.scene.chart.NumberAxis;
import javafx.scene.chart.XYChart;
import javafx.scene.chart.XYChart.Data;
import javafx.scene.control.Label;
import javafx.scene.control.Slider;

public class MainController implements Initializable{

	private static final int MAX_CHART_POINTS = 10;
	
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
	private AreaChart<Number, Number> chart;
	@FXML
	private NumberAxis xAxis;
	@FXML
	private NumberAxis yAxis;
	
	private AreaChart.Series<Number, Number> series = new AreaChart.Series<>();
	
	@Override
	public void initialize(URL location, ResourceBundle resources) {
		initChart();
		addPointToChart(0,0);
		addPointToChart(1,1);
		ledLabel.setText("LED: off");
		lsLabel.setText("LS: 98239");
	}
	
	@FXML
    private void setMotorToManual() throws IOException {
        // roba
    }
	
	@FXML
    private void setMotorToAuto() throws IOException {
        // roba
    }
	
	public void setLedLabelText(String txt) {
		ledLabel.setText(txt);
	}
	public void setLightSensorLabelText(String txt) {
		lsLabel.setText(txt);
	}
	public void setTHLabelText(String txt) {
		thLabel.setText(txt);
	}
	public void setPirLabelText(String txt) {
		pirLabel.setText(txt);
	}
	public void setStateLabelText(String txt) {
		stateLabel.setText(txt);
	}
	public void setWaterLevelLabelText(String txt) {
		wlLabel.setText(txt);
	}
	public void setWL1LabelText(String txt) {
		wl1Label.setText(txt);
	}
	public void setWL2LabelText(String txt) {
		wl2Label.setText(txt);
	}
	public void setMotorLabelText(String txt) {
		motorLabel.setText(txt);
	}
	
	private void initChart() {
        yAxis.setAutoRanging(false); //prevent automatic resizing for simplicity

        xAxis.setLowerBound(0);
        
        yAxis.setUpperBound(10);
        yAxis.setLowerBound(0);
        yAxis.setTickUnit(0.5);
        chart.getData().add(series);
	}
	
	public void addPointToChart(Number value, Number seconds) {
		series.getData().add(new Data<Number, Number>(seconds, value));
	}
}
