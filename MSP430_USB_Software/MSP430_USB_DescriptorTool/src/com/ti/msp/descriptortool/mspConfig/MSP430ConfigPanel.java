/*
 * To change this template, choose Tools | Templates
 * and open the template in the editor.
 */
package com.ti.msp.descriptortool.mspConfig;

import com.ti.msp.common.StaticInfo;
import com.ti.msp.descriptortool.DescriptorToolMainPanel;
import com.ti.msp.descriptortool.USBinterfaces.MSCPanelInterfacePanel430;
import java.awt.event.MouseEvent;
import java.io.File;
import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;
import java.util.logging.Level;
import java.util.logging.Logger;
import javax.swing.JCheckBox;
import javax.swing.JComboBox;
import javax.swing.JEditorPane;
import javax.swing.JPanel;

/**
 *
 * @author a0272979
 */
public class MSP430ConfigPanel extends javax.swing.JPanel {
    DescriptorToolMainPanel descToolPanel;
    MSP430Config mspConf;
    JEditorPane editorPane;

    /**
     * Creates new form MSPConfigPanel
     */
    public MSP430ConfigPanel(DescriptorToolMainPanel descToolPanel, JEditorPane editorPane, MSP430Config mspConf) {
        this.descToolPanel = descToolPanel;
        this.editorPane = editorPane;
        this.mspConf = mspConf;
        initComponents();
    }

    /**
     * This method is called from within the constructor to initialize the form.
     * WARNING: Do NOT modify this code. The content of this method is always
     * regenerated by the Form Editor.
     */
    @SuppressWarnings("unchecked")
    // <editor-fold defaultstate="collapsed" desc="Generated Code">//GEN-BEGIN:initComponents
    private void initComponents() {

        jPanel1 = new javax.swing.JPanel();
        jComboBox1 = new javax.swing.JComboBox();
        jComboBox2 = new javax.swing.JComboBox();
        jLabel2 = new javax.swing.JLabel();
        jLabel3 = new javax.swing.JLabel();
        jCheckBox1 = new javax.swing.JCheckBox();
        jCheckBox2 = new javax.swing.JCheckBox();
        jCheckBox3 = new javax.swing.JCheckBox();
        jCheckBox4 = new javax.swing.JCheckBox();
        jPanel2 = new javax.swing.JPanel();
        jLabel1 = new javax.swing.JLabel();
        jComboBox3 = new javax.swing.JComboBox();

        setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "MSP Configuration"));

        jPanel1.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "MSP Configuration"));

        jComboBox1.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "SEE NOTE", "1.5 MHz", "1.6 MHz", "1.7778 MHz", "1.8432 MHz", "1.8461 MHz", "1.92 MHz", "2.0 MHz", "2.4 MHz", "2.66667 MHz", "3.0 MHz", "3.2 MHz", "3.5556 MHz", "3.579546 MHz", "3.84 MHz", "4 MHz", "4.1739 MHz", "4.1943 MHz", "4.332 MHz", "4.3636 MHz", "4.5 MHz", "4.8 MHz", "5.33 MHz", "5.76 MHz", "6.0 MHz", "6.4 MHz", "7.2 MHz", "7.68 MHz", "8.0 MHz", "9.0 MHz", "9.6 MHz", "10.66 MHz", "12.0 MHz", "12.8 MHz", "14.4 MHz", "16.0 MHz", "16.9344 MHz", "16.94118 MHz", "18.0 MHz", "19.2 MHz", "24.0 MHz", "25.6 MHz", "26.0 MHz", "32 MHz" }));
        jComboBox1.setSelectedIndex(0);
		//jComboBox1.setSelectedIndex(mspConf.getCrystOScSel());
        jComboBox1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jComboBox1MouseClicked(evt);
            }
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jComboBox1MouseEntered(evt);
            }
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jComboBox1MousePressed(evt);
            }
        });
        jComboBox1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBox1ActionPerformed(evt);
            }
        });
		
		// Disable jComboBox1
		jComboBox1.setEnabled(false);

        jComboBox2.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "No DMA", "0", "1", "2", "3", "4", "5", "6", "7" }));
        jComboBox2.setSelectedIndex(mspConf.getDamChannel());
        jComboBox2.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseClicked(java.awt.event.MouseEvent evt) {
                jComboBox2MouseClicked(evt);
            }
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jComboBox2MouseEntered(evt);
            }
            public void mousePressed(java.awt.event.MouseEvent evt) {
                jComboBox2MousePressed(evt);
            }
        });
        jComboBox2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jComboBox2ActionPerformed(evt);
            }
        });

        jLabel2.setText("XT2 Oscillation Frequency:");

        jLabel3.setText("DMA Channel:");

        jCheckBox1.setSelected(mspConf.isDisCrysOnSus());
        jCheckBox1.setText("Disable Crystal on Suspend");
        jCheckBox1.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jCheckBox1MouseEntered(evt);
            }
        });
        jCheckBox1.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox1ActionPerformed(evt);
            }
        });

        jCheckBox2.setSelected(mspConf.isSysBIOS());
        jCheckBox2.setText("Using SYSBIOS");
        jCheckBox2.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jCheckBox2MouseEntered(evt);
            }
        });
        jCheckBox2.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox2ActionPerformed(evt);
            }
        });

        jCheckBox3.setSelected(mspConf.isDriveVBUSExt());
        jCheckBox3.setText("Drive VBUS from External Supply");
        jCheckBox3.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jCheckBox3MouseEntered(evt);
            }
        });
        jCheckBox3.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox3ActionPerformed(evt);
            }
        });

        jCheckBox4.setSelected(mspConf.isBypass());
        jCheckBox4.setText("BYPASS XT2 Oscillator");
        jCheckBox4.addMouseListener(new java.awt.event.MouseAdapter() {
            public void mouseEntered(java.awt.event.MouseEvent evt) {
                jCheckBox4MouseEntered(evt);
            }
        });
        jCheckBox4.addActionListener(new java.awt.event.ActionListener() {
            public void actionPerformed(java.awt.event.ActionEvent evt) {
                jCheckBox4ActionPerformed(evt);
            }
        });

        javax.swing.GroupLayout jPanel1Layout = new javax.swing.GroupLayout(jPanel1);
        jPanel1.setLayout(jPanel1Layout);
        jPanel1Layout.setHorizontalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                    .addComponent(jCheckBox4)
                    .addComponent(jCheckBox3)
                    .addComponent(jCheckBox1)
                    .addComponent(jCheckBox2)
                    .addGroup(jPanel1Layout.createSequentialGroup()
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jLabel2)
                            .addComponent(jLabel3))
                        .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                        .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
                            .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                            .addComponent(jComboBox2, javax.swing.GroupLayout.PREFERRED_SIZE, 64, javax.swing.GroupLayout.PREFERRED_SIZE))))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        jPanel1Layout.setVerticalGroup(
            jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel1Layout.createSequentialGroup()
                .addComponent(jCheckBox1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jCheckBox4)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel2)
                    .addComponent(jComboBox1, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addGroup(jPanel1Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel3)
                    .addComponent(jComboBox2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jCheckBox2)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.UNRELATED)
                .addComponent(jCheckBox3)
                .addContainerGap(8, Short.MAX_VALUE))
        );

        jComboBox1.getAccessibleContext().setAccessibleName("XT2 Oscillation");
        jComboBox2.getAccessibleContext().setAccessibleName("DMA");

        jPanel2.setBorder(javax.swing.BorderFactory.createTitledBorder(javax.swing.BorderFactory.createEtchedBorder(), "MSP device Selection "));

        jLabel1.setText("Select Device:");

        jComboBox3.setModel(new javax.swing.DefaultComboBoxModel(new String[] { "MSP430F5xx/F6xx", "MSP432" }));
        jComboBox3.setSelectedIndex(0);
        jComboBox3.setEnabled(false);

        javax.swing.GroupLayout jPanel2Layout = new javax.swing.GroupLayout(jPanel2);
        jPanel2.setLayout(jPanel2Layout);
        jPanel2Layout.setHorizontalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jLabel1)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jComboBox3, 0, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
        jPanel2Layout.setVerticalGroup(
            jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(jPanel2Layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(jPanel2Layout.createParallelGroup(javax.swing.GroupLayout.Alignment.BASELINE)
                    .addComponent(jLabel1)
                    .addComponent(jComboBox3, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );

        javax.swing.GroupLayout layout = new javax.swing.GroupLayout(this);
        this.setLayout(layout);
        layout.setHorizontalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(layout.createSequentialGroup()
                .addContainerGap()
                .addGroup(layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING, false)
                    .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                    .addComponent(jPanel2, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
                .addContainerGap(javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE))
        );
        layout.setVerticalGroup(
            layout.createParallelGroup(javax.swing.GroupLayout.Alignment.LEADING)
            .addGroup(javax.swing.GroupLayout.Alignment.TRAILING, layout.createSequentialGroup()
                .addContainerGap()
                .addComponent(jPanel2, javax.swing.GroupLayout.PREFERRED_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.PREFERRED_SIZE)
                .addPreferredGap(javax.swing.LayoutStyle.ComponentPlacement.RELATED)
                .addComponent(jPanel1, javax.swing.GroupLayout.DEFAULT_SIZE, javax.swing.GroupLayout.DEFAULT_SIZE, Short.MAX_VALUE)
                .addContainerGap())
        );
    }// </editor-fold>//GEN-END:initComponents

    private void jCheckBox1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox1ActionPerformed
        StaticInfo.debug("Disable Crystal updated: " + jCheckBox1.isSelected());
        mspConf.setDisCrysOnSus(jCheckBox1.isSelected());
    }//GEN-LAST:event_jCheckBox1ActionPerformed

    private void jComboBox1ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBox1ActionPerformed
        StaticInfo.debug("XT2 frequency set to: " + jComboBox1.getSelectedItem());
        mspConf.setCrystOScSel(jComboBox1.getSelectedIndex());
    }//GEN-LAST:event_jComboBox1ActionPerformed

    private void jComboBox2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jComboBox2ActionPerformed
        StaticInfo.debug("DMA channel set to: " + jComboBox2.getSelectedItem());
        mspConf.setDamChannel(jComboBox2.getSelectedIndex());
    }//GEN-LAST:event_jComboBox2ActionPerformed

    private void jCheckBox2ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox2ActionPerformed
        StaticInfo.debug("Use SYSBIOS set to: " + jCheckBox2.isSelected());
        mspConf.setSysBIOS(jCheckBox2.isSelected());
    }//GEN-LAST:event_jCheckBox2ActionPerformed

    private void jCheckBox3ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox3ActionPerformed
        StaticInfo.debug("Drive VBUS from External Supply set to: " + jCheckBox2.isSelected());
        mspConf.setDriveVBUSExt(jCheckBox3.isSelected());
    }//GEN-LAST:event_jCheckBox3ActionPerformed

    private void jCheckBox4ActionPerformed(java.awt.event.ActionEvent evt) {//GEN-FIRST:event_jCheckBox4ActionPerformed
        StaticInfo.debug("BYPASS XT2 Oscillator set to: " + jCheckBox4.isSelected());
        mspConf.setBypass(jCheckBox4.isSelected());
    }//GEN-LAST:event_jCheckBox4ActionPerformed

    private void jCheckBox1MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jCheckBox1MouseEntered
        updateEditorPane(evt);
    }//GEN-LAST:event_jCheckBox1MouseEntered

    private void jCheckBox4MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jCheckBox4MouseEntered
        updateEditorPane(evt);
    }//GEN-LAST:event_jCheckBox4MouseEntered

    private void jCheckBox2MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jCheckBox2MouseEntered
        updateEditorPane(evt);
    }//GEN-LAST:event_jCheckBox2MouseEntered

    private void jCheckBox3MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jCheckBox3MouseEntered
        updateEditorPane(evt);
    }//GEN-LAST:event_jCheckBox3MouseEntered

    private void jComboBox1MousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jComboBox1MousePressed
        updateEditorPaneCombo(evt);
    }//GEN-LAST:event_jComboBox1MousePressed

    private void jComboBox2MousePressed(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jComboBox2MousePressed
        updateEditorPaneCombo(evt);
    }//GEN-LAST:event_jComboBox2MousePressed

    private void jComboBox1MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jComboBox1MouseClicked
        updateEditorPaneCombo(evt);
    }//GEN-LAST:event_jComboBox1MouseClicked

    private void jComboBox2MouseClicked(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jComboBox2MouseClicked
        updateEditorPaneCombo(evt);
    }//GEN-LAST:event_jComboBox2MouseClicked

    private void jComboBox1MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jComboBox1MouseEntered
        updateEditorPaneCombo(evt);
    }//GEN-LAST:event_jComboBox1MouseEntered

    private void jComboBox2MouseEntered(java.awt.event.MouseEvent evt) {//GEN-FIRST:event_jComboBox2MouseEntered
        updateEditorPaneCombo(evt);
    }//GEN-LAST:event_jComboBox2MouseEntered

    // Variables declaration - do not modify//GEN-BEGIN:variables
    private javax.swing.JCheckBox jCheckBox1;
    private javax.swing.JCheckBox jCheckBox2;
    private javax.swing.JCheckBox jCheckBox3;
    private javax.swing.JCheckBox jCheckBox4;
    private javax.swing.JComboBox jComboBox1;
    private javax.swing.JComboBox jComboBox2;
    private javax.swing.JComboBox jComboBox3;
    private javax.swing.JLabel jLabel1;
    private javax.swing.JLabel jLabel2;
    private javax.swing.JLabel jLabel3;
    private javax.swing.JPanel jPanel1;
    private javax.swing.JPanel jPanel2;
    // End of variables declaration//GEN-END:variables

    
    private void updateEditorPane(MouseEvent evt) {
        // Determine Panel which generated the MouseEvent
        JCheckBox source = (JCheckBox) evt.getSource();
        String accessName = source.getAccessibleContext().getAccessibleName();
        String htmlFileToDisplay;
        
        // Determine File to be displayed in InfoPanel
        if(accessName.contentEquals("Disable Crystal on Suspend")){
            htmlFileToDisplay = "infoPanelText/MSP430/DisableXtal.html";
        }else if(accessName.contentEquals("BYPASS XT2 Oscillator")){
            htmlFileToDisplay = "infoPanelText/MSP430/XT2InBypass.html";
        }else if(accessName.contentEquals("Using SYSBIOS")){
            htmlFileToDisplay = "infoPanelText/MSP430/UsingSYSBIOS.html";
        }else if(accessName.contentEquals("Drive VBUS from External Supply")){
            htmlFileToDisplay = "infoPanelText/MSP430/DriveVBUSEXT.html";
        }else {
            return;
        }
        
        
        
        // If Panel has valid HTML description remove current content in 
        // infoPane
        editorPane.removeAll();
        
        // Display page in infoPane 
        try {
            URL url = new File(htmlFileToDisplay).toURI()
                    .toURL();
            editorPane.setPage(url);
        } catch (MalformedURLException ex) {
            Logger.getLogger(MSCPanelInterfacePanel430.class.getName()).log(
                    Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(MSCPanelInterfacePanel430.class.getName()).log(
                    Level.SEVERE, null, ex);
        }
        
        
        
        
    }
    
    
    private void updateEditorPaneCombo(MouseEvent evt) {
        // Determine Panel which generated the MouseEvent
        JComboBox sourcePanel = (JComboBox) evt.getSource();
        String accessName = sourcePanel.getAccessibleContext().getAccessibleName();
        String htmlFileToDisplay;
        
        // Determine File to be displayed in InfoPanel
        if(accessName.contentEquals("XT2 Oscillation")){
            htmlFileToDisplay = "infoPanelText/MSP430/XTALOSCFreq.html";
        }else if(accessName.contentEquals("DMA")){
            htmlFileToDisplay = "infoPanelText/MSP430/DMAChannel.html";
        }else {
            return;
        }
        
        // If Panel has valid HTML description remove current content in 
        // infoPane
        editorPane.removeAll();
        
        // Display page in infoPane 
        try {
            URL url = new File(htmlFileToDisplay).toURI()
                    .toURL();
            editorPane.setPage(url);
        } catch (MalformedURLException ex) {
            Logger.getLogger(MSCPanelInterfacePanel430.class.getName()).log(
                    Level.SEVERE, null, ex);
        } catch (IOException ex) {
            Logger.getLogger(MSCPanelInterfacePanel430.class.getName()).log(
                    Level.SEVERE, null, ex);
        }
    }
    
}
//Released_Version_5_20_06_02
