package com.pccs.main;

import com.pccs.models.BuildsTable;
import com.pccs.views.DebugLog;
import com.pccs.views.Download;
import com.pccs.views.MainWindow;
import com.pccs.views.TabContainer;
import java.net.Socket;
import javax.swing.JFrame;
import javax.swing.UIManager;

public class GuiController {
    private JFrame mainWindow;
    private TabContainer tabContainer;
    private BuildsTable buildsTable;

    // These are tabs:
    private DebugLog debugLog;
    private Download download;
    
    public GuiController() {
        loadLookAndFeel();
        setupComponents();
        
    }
        
    private void loadLookAndFeel() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception ex) {
            System.out.println(ex);
        }
    }
    
    private void setupComponents() {
        debugLog     = new DebugLog();
        download     = new Download();
        buildsTable  = new BuildsTable();
        tabContainer = new TabContainer();
        mainWindow   = new MainWindow();
        
        mainWindow.getContentPane().add(tabContainer);
        
        tabContainer.getTabbedPane().addTab("Debug Log", debugLog);
        tabContainer.getTabbedPane().addTab("Downloads", download);
    }
    
    public void addDebugLog(String string) {
        debugLog.addDebugLog(string);
    }
}
