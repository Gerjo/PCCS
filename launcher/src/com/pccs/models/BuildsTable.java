package com.pccs.models;

import javax.swing.table.AbstractTableModel;

public class BuildsTable extends AbstractTableModel {
    private String[] columnNames;
    
    public BuildsTable() {
        columnNames = new String[] {"Name", "Size", "Age"};
    }
    
    //public void loadJson(JSONOb)
    
    @Override
    public int getRowCount() {
        return 0;
    }

    @Override
    public int getColumnCount() {
        return columnNames.length;
    }

    @Override
    public Object getValueAt(int rowIndex, int columnIndex) {
        return "";
    }
    
    @Override
    public String getColumnName(int column) {
        return columnNames[column];
    }
}
