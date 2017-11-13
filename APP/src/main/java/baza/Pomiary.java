package baza;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.SQLException;
import java.sql.Statement;


/**
 * Created by Alicja on 2017-10-28.
 */
public class Pomiary {

    public static final String DRIVER = "com.sqlite.JDBC";
    public static final String DB_URL = "jdbc:sqlite:pomiary.db";

    private Connection conn;
    private Statement stat;

    public Pomiary() {
        try {
            Class.forName(Pomiary.DRIVER);
        } catch (ClassNotFoundException e) {
            System.err.println("Brak sterownika JDBC");
            e.printStackTrace();
        }

        try {
            conn = DriverManager.getConnection(DB_URL);
            stat = conn.createStatement();
        } catch (SQLException e) {
            System.err.println("Problem z otwarciem polaczenia");
            e.printStackTrace();
        }

        createTables();
    }

    public boolean createTables()  {
        String createSlave = "CREATE TABLE IF NOT EXISTS Slave (idSlave INTEGER PRIMARY KEY , flower varchar(255))";
        String createMeasurement = "CREATE TABLE IF NOT EXISTS Measurement (idMeasurement INTEGER PRIMARY KEY AUTOINCREMENT, idSlave INTEGER DEFAULT NULL, measurment DECIMAL(2,1) DEFAULT NULL, date DATE DEFAULT NULL, time TIME DEFAULT NULL)";

        try {
            stat.execute(createSlave);
            stat.execute(createMeasurement);
        } catch (SQLException e) {
            System.err.println("Blad przy tworzeniu tabeli");
            e.printStackTrace();
            return false;
        }
        return true;
    }
}