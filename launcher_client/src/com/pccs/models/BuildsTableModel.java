package com.pccs.models;

import java.util.ArrayList;
import javax.swing.JButton;
import javax.swing.table.AbstractTableModel;
import org.json.simple.JSONArray;
import org.json.simple.JSONObject;

public class BuildsTableModel extends AbstractTableModel {
    private String[] columnNames;
    private ArrayList<BuildModel> builds;
    
    public BuildsTableModel() {
        builds      = new ArrayList<>();
        columnNames = new String[] {"Name", "Size", "Installed", "Age"};
    }
    
    public void loadJson(JSONArray json) {
        for(Object object : json) {
            builds.add(new BuildModel((JSONObject) object));
        }
        
        fireTableDataChanged();
    }
    
    @Override
    public int getRowCount() {
        return builds.size();
    }

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        BuildModel handle = builds.get(rowIndex);
        
        switch(columnIndex) {
            case 0:  return handle.getName();
            case 1:  return handle.getSizeFormated();
            case 2:  return handle.isInstalled();
            case 3:  return handle.getAgeFormatted();
            default: return "null";
        }
    }
    
    @Override
    public Class getColumnClass(int column) {
        return getValueAt(0, column).getClass();
    }
    
    @Override
    public String getColumnName(int column) {
        return columnNames[column];
    }
}
