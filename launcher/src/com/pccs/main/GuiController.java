package com.pccs.main;

import com.pccs.models.BuildsTable;
import com.pccs.views.DebugTab;
import com.pccs.views.BuildsTab;
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
    private DebugTab debugTab;
    private BuildsTab buildsTab;
    
    public GuiController() {
        loadLookAndFeel();
        setupComponents();
    }
        
    private void loadLookAndFeel() {
        try {
            UIManager.setLookAndFeel(UIManager.getSystemLookAndFeelClassName());
        } catch (Exception pokeball) {
            System.out.println(pokeball);
        }
    }
    
    private void setupComponents() {
        debugTab     = new DebugTab();
        buildsTab    = new BuildsTab();
        buildsTable  = new BuildsTable();
        tabContainer = new TabContainer();
        mainWindow   = new MainWindow();
        
        mainWindow.getContentPane().add(tabContainer);
        
        tabContainer.getTabbedPane().addTab("Debug Log", debugTab);
        tabContainer.getTabbedPane().addTab("Downloads", buildsTab);
        
        buildsTab.getTable().setModel(buildsTable);
    }
    
    public void addDebugLog(String string) {
        debugTab.addDebugLog(string);
    }
}
