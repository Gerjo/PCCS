package com.pccs.views;

import com.pccs.models.BuildModel;
import java.io.BufferedInputStream;
import java.io.FileOutputStream;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import javax.swing.JFrame;

public class DownloadFrame extends JFrame {
    private DownloadPanel downloader;
    private BuildModel buildModel;
    private Thread thread;
    
    public DownloadFrame(BuildModel buildModel) {
        super("Downloading");
        
        this.buildModel = buildModel;
        this.downloader = new DownloadPanel(this);
        
        setSize(400, 180);
        setResizable(false);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        getContentPane().add(downloader);
        
        startDownload();
    }
    
    private void startDownload() {
        if(thread != null) {
            return;
        }
        
        thread = new Thread(new Runnable() {
            @Override
            public void run() {
                try {
                    saveUrl("out", buildModel.getUrl());
                } catch(Exception ex) {
                    System.out.println(ex);
                }
            }
        });
        
        thread.start();
    }
    
    public void saveUrl(String filename, String urlString) throws MalformedURLException, IOException {
        BufferedInputStream in = null;
        FileOutputStream fout  = null;
        try {
            in   = new BufferedInputStream(new URL(urlString).openStream());
            fout = new FileOutputStream(filename);

            byte data[] = new byte[1024];
            int count;
            int total = 0;
            while ((count = in.read(data, 0, 1024)) != -1) {
                total += count;
                
                downloader.setProgressText(total + " of " + buildModel.getSize() + " bytes.");
                downloader.setProgressBar(total, (int) buildModel.getSize());
                
                fout.write(data, 0, count);
            }
        } finally {
            if (in != null) {
                in.close();
            }
            if (fout != null) {
                fout.close();
            }
        }
    }
    
    public void cancel() {
        dispose();
        thread.stop();
    }
}
