package com.pccs.views;

import javax.swing.JFrame;

public class MainWindow extends JFrame {
    public MainWindow() {
        super("Guerrilla Tactics Launcher");
        
        setSize(500, 350);
        setResizable(false);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
