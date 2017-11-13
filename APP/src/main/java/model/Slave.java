package model;

/**
 * Created by Alicja on 2017-10-28.
 */
public class Slave {

    private int idSlave;
    private String flower;

    public int getIdSlave() {
        return idSlave;
    }
    public void setIdSlave(int id) {
        this.idSlave = id;
    }

    public String getFlower() {
        return flower;
    }

    public void setFlower (String flower) {
        this.flower = flower;
    }

    public Slave() {}
    public Slave (int id, String flower) {
        this.idSlave = id;
        this.flower = flower;
    }

    @Override
    public String toString() {
        return "Slave nr: " +
                idSlave +
                ", kwiatek: " +
                flower;
    }
}
