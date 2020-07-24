# ------------------------------------------------- ----- 
# -------------------- mplwidget.py -------------------- 
# -------------------------------------------------- ---- 
from  PyQt5.QtWidgets  import * 
from  matplotlib.backends.backend_qt5agg  import  FigureCanvas 
from  matplotlib.figure  import  Figure 
from PyQt5 import QtCore, QtGui, QtWidgets #works for pyqt5
class  MplWidget ( QWidget ): 
    
    def  __init__ ( self ,  parent  =  None ): 

        QWidget . __init__ ( self ,  parent )
        self.fig=Figure ()
        self . canvas  =  FigureCanvas (self.fig ) 
        vertical_layout  =  QVBoxLayout () 
        vertical_layout . addWidget ( self . canvas ) 

        self . fig  .subplots_adjust(wspace=0.6, hspace=0.6, left=0.20, bottom=0.20, right=0.96, top=0.90)

 

        self . canvas . axes  =  self . canvas . figure . add_subplot ( 111 ) 
        self . setLayout ( vertical_layout )
