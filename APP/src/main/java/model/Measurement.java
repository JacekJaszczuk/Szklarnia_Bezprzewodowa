package model;

import java.sql.Time;
import java.util.Date;

/**
 * Created by Alicja on 2017-10-28.
 */
public class Measurement {

    private int idMeasurement;
    private int idSlave;
    private Date date;
    private Time time;
    private double measurement;

    public int getIdMeasurement () {
        return idMeasurement;
    }
    public void setIdMeasurement(int idMeasurement) {
        this.idMeasurement = idMeasurement;
    }

    public int getIdSlave () {
        return idSlave;
    }
    public void setIdSlave(int idSlave) {
        this.idSlave = idSlave;
    }

    public Date getDate () {
        return date;
    }
    public void setDate(Date  date) {
        this.date = date;
    }

    public Time getTime () {
        return time;
    }
    public void setTime(Time time) {
        this.time = time;
    }

    public double getMeasurement () {
        return measurement;
    }
    public void setMeasurement(double measurement) {
        this.measurement = measurement;
    }
}
