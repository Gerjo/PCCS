package com.pccs.views.tabbed;

import javax.swing.JFrame;

public class MainWindow extends JFrame {
    public MainWindow() {
        super("Guerrilla Tactics Launcher");
        
        setSize(500, 380);
        setResizable(false);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }
}
