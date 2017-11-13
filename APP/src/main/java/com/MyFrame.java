package com;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;

/**
 * Created by Alicja on 2017-10-28.
 */

public class MyFrame {

    private JFrame mainFrame;
    private JLabel headerLabel;
    private JLabel statusLabel;
    private JPanel controlPanel;

    public MyFrame() {
        prepareGUI();
        showTextAreaDemo();
    }

    private void prepareGUI(){
        mainFrame = new JFrame("Bezprzewodowa Szklarnia");
        mainFrame.setSize(400,400);
        mainFrame.setLayout(new GridLayout(3, 1));

        mainFrame.addWindowListener(new WindowAdapter() {
            public void windowClosing(WindowEvent windowEvent){
                System.exit(0);
            }
        });
        JMenuBar menu = Menu();
        mainFrame.setJMenuBar(menu);
        headerLabel = new JLabel("", JLabel.CENTER);

        controlPanel = new JPanel();
        controlPanel.setLayout(new FlowLayout());
        controlPanel.setVisible(true);

        mainFrame.add(headerLabel);
        mainFrame.add(controlPanel);
        mainFrame.setVisible(true);
    }

    private void showTextAreaDemo(){
        headerLabel.setText("Wyniki ostatnich pomiarów:");

        final JTextArea commentTextArea =
                new JTextArea(5,20);

        JScrollPane scrollPane = new JScrollPane(commentTextArea);

        controlPanel.add(scrollPane);
        mainFrame.setVisible(true);
    }
   public JMenuBar Menu() {

        JMenuBar menu = new JMenuBar();

        JMenu SlaveMenu = new JMenu("Slave");
        JMenu InfoMenu = new JMenu("Informacje");
        menu.add(SlaveMenu);
        menu.add(InfoMenu);

        JMenuItem projekt = new JMenuItem("O projekcie");
        JMenuItem autorzy = new JMenuItem("O autorach");

        JMenuItem nowySlave = new JMenuItem("Dodaj nowy Slave");
        JMenuItem usunSlave = new JMenuItem("Usun Slave");
        JMenuItem wszystkieSlave = new JMenuItem("Wszystkie Slave'y");

        InfoMenu.add(projekt);
        InfoMenu.add(autorzy);

        SlaveMenu.add(nowySlave);
        SlaveMenu.add(usunSlave);
        SlaveMenu.add(wszystkieSlave);

        projekt.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                String a = "Projekt: Zastosowanie Systemów Wbudowanych\n" +
                        "Bezprzewodowa Szklarnia\n" +
                        "System monitorowania wilgotności gleby w doniczkach";
                JOptionPane.showMessageDialog(mainFrame, a);
             } });

        autorzy.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent arg0) {
                String a = "Autorzy: \n" +
                        "Magdalena Wajs\n" +
                        "Alicja Ciura\n" +
                        "Jacek Jaszczuk\n";
                JOptionPane.showMessageDialog(mainFrame, a);
            } });

       nowySlave.addActionListener(new ActionListener() {
           public void actionPerformed(ActionEvent e) {

               controlPanel.removeAll();
               controlPanel.validate();
               controlPanel.setVisible(true);

               JPanel p = new JPanel();
               Choice b = new Choice();
               b.setSize(50,10);
               for(int i =0; i< 16; i++) {
                   int a = i+1;
                   b.add(Integer.toString(a));
               }

               mainFrame.remove(controlPanel);
               mainFrame.remove(headerLabel);
               mainFrame.validate();

               JLabel nrSlave = new JLabel("Wybierz nr Slave'a: ");
               JLabel nameFlower = new JLabel("Podaj nazwe rosliny: ");
               JTextField name = new JTextField();
               name.setSize(50, 1);


               controlPanel.setLayout(new GridLayout(2,2));
               controlPanel.add(nrSlave);
               controlPanel.add(b);
               controlPanel.add(nameFlower);
               controlPanel.add(name);
               mainFrame.add(controlPanel);
               mainFrame.validate();
           }
       });

       return menu;
   }
}
