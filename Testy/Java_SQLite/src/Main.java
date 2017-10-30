import java.sql.*;

public class Main {

	public static void main(String[] args) {
		
		System.out.println("Czytaj dane z bazy danych :-)");
		
		Connection connection = null;
		
		try {
			// Połącz z bazą danych i wykonaj zapytania:
			connection = DriverManager.getConnection("jdbc:sqlite:baza.db");
			Statement statement = connection.createStatement();
			statement.setQueryTimeout(30);
			
			ResultSet rs = statement.executeQuery("select * from Pracownicy");
			
			while(rs.next())
			{
				System.out.println("Dane na temat twojego pracownika: " + rs.getString("ID") + ", " + rs.getString("Imie") + ", " + rs.getString("Nazwisko"));
			}
		}
		catch (SQLException e) {
			System.err.println(e.getMessage());
		}
	}

}
