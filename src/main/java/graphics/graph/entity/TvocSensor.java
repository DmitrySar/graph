package graphics.graph.entity;

import java.time.LocalDateTime;

public class TvocSensor implements ISensor {

    private double value;
    private LocalDateTime time;

    public TvocSensor() {
    }

    public TvocSensor(double value) {
        this.value = value;
        this.time = LocalDateTime.now();
    }

    @Override
    public double getValue() {
        return this.value;
    }

    @Override
    public LocalDateTime getTime() {
        return this.time;
    }

    public void setValue(double value) {
        this.value = value;
    }

    public void setTime(LocalDateTime time) {
        this.time = time;
    }
}