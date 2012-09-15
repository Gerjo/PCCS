package com.pccs.views;

import javax.swing.JFrame;
import javax.swing.JPanel;

public class MainWindow extends JFrame {
    public MainWindow() {
        super("Guerrilla Tactics Launcher");
        
        setSize(400, 350);
        setResizable(false);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
