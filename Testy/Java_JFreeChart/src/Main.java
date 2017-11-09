// Przykład użycia JFreeChart
// Jest to lekko przerobiona wersja przykładu:
// https://www.caveofprogramming.com/java/charts-in-java-swing-with-jfreechart.html

import javax.swing.JFrame;

import org.jfree.chart.ChartFactory;
import org.jfree.chart.ChartPanel;
import org.jfree.chart.JFreeChart;
import org.jfree.data.xy.DefaultXYDataset;
import org.jfree.data.xy.XYDataset;

// Główna klasa programu:
public class Main {

	// Metody statyczne są związane z klasą a nie obiektem.
	// Metoda do kreowania danych wykresu:
	private static XYDataset createDataset() {
		
		DefaultXYDataset ds = new DefaultXYDataset();
		
		// Wartości danych - macierz:
		// Pierwsza "linia" -> wartości na osi X, druga "linia" -> wartości na osi Y:
		double[][] data1 = { {10, 20, 30}, {70, 55, 45} };
		double[][] data2 = { {10, 20, 30}, {60, 55, 50} };
		
		// Dodaj serie do zbioru danych:
		ds.addSeries("Kwiat Pustyni 1", data1);
		ds.addSeries("Kwiat Paproci 2", data2);
		
		return ds;
	}
	
	public static void main(String[] args) {
		
		// Stwórz nowe okno i je skonfiguruj:
		JFrame window = new JFrame("Wilgotność gleby :-)");
		window.setSize(800, 600);
		window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		
		// Stwórz dane oraz obiekt wykresu:
		XYDataset ds = createDataset();
		JFreeChart chart = ChartFactory.createXYLineChart("Wilgotność gleby w kwiatkach", "Czas", "Procent wilgotności", ds);

		// Stwórz panel wykresu i dodaj do niego wykres:
		ChartPanel cp = new ChartPanel(chart);
		
		// Dodaj do okna panel wykresu:
		window.getContentPane().add(cp);
		
		// Pokaż okno:
		window.setVisible(true);
	}

}
