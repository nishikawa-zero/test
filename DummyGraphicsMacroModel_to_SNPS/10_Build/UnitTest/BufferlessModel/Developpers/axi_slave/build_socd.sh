#!/bin/sh

 VHM=VHM
 VHMLIB=libdesign
 PROJ=Project2
 BACKUP=CMS_backup

 [ -d $PROJ ] && rm -rf $PROJ
 
 mkdir -p $PROJ/Linux/Default
 cp -p $BACKUP/$PROJ.carbon $PROJ
 cp -p $VHM/$VHMLIB.a               $PROJ/Linux/Default
 cp -p $VHM/$VHMLIB.h               $PROJ/Linux/Default
 cp -p $VHM/$VHMLIB.symtab.db       $PROJ/Linux/Default
 cp -p $VHM/$VHMLIB.designHierarchy $PROJ/Linux/Default

 mkdir -p $PROJ/Linux/Default/SoCDesigner
 cp -p $BACKUP/$VHMLIB.ccfg $PROJ/Linux/Default/SoCDesigner

#modelstudio $PROJ/$PROJ.carbon

