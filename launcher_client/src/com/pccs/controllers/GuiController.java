package com.pccs.controllers;

import com.pccs.models.BuildsTableModel;
import com.pccs.views.BuildsTab;
import com.pccs.views.DebugTab;
import com.pccs.views.MainWindow;
import com.pccs.views.TabContainer;
import javax.swing.UIManager;

public class GuiController {
    private MainWindow mainWindow;
    private TabContainer tabContainer;
    private BuildsTableModel buildsTable;
    private DebugTab debugTab;
    private BuildsTab buildsTab;
    private LauncherClient launcherClient;
    
    
    public GuiController(LauncherClient launcherClient) {
        this.launcherClient = launcherClient;
        
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
        buildsTable  = new BuildsTableModel();
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
    
    public BuildsTableModel getBuildsTable() {
        return buildsTable;
    }
}
