package com.pccs.main;

import com.pccs.gui.Panel;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JFrame;
import javax.swing.UIManager;
import javax.swing.UnsupportedLookAndFeelException;


public class Main {
    public static void main(String[] args) {
        System.out.println("Master server works.");
        try {
            UIManager.setLookAndFeel(
                UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ex) {
            System.out.println(ex);
        }
        
        JFrame window = new JFrame("Guerrilla Tactics downloader.");
        window.setSize(400, 350);
        window.setResizable(false);
        window.setVisible(true);
        window.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);    
        window.getContentPane().add(new Panel());
        
    }
}
