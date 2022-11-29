import sys
import difflib
from PyQt5 import QtCore, QtGui, QtWidgets, QtWebEngineWidgets
from PyQt5.QtWidgets import QApplication, QMainWindow

all_pairs = list()
eq_pairs = list()
ineq_pairs = list()
abnormal_pairs = list()

now = 0
num = 0

def read_pairs():
    global num
    with open("./output/equal.csv", 'r') as f:
        tmp_pairs = f.readlines()
        f.close()
    for pair in tmp_pairs:
        all_pairs.append(pair.split(","));
    for pair in all_pairs:
        pair[1] = pair[1].replace('\n', '')
        pair[1] = pair[1].replace('\r', '')
    num = len(all_pairs)
    #print(all_pairs)


def throw_pair(result):
    if(result == 1):
        eq_pairs.append(all_pairs[now])
    if(result == 2):
        ineq_pairs.append(all_pairs[now])
    if(result == 3):
        abnormal_pairs.append(all_pairs[now])

def next_pair():
    global now
    now = now + 1

def read_file(filename):
    with open(filename, 'r') as f:
        return f.readlines()

def set_pair(ui):
    global num
    global now
    ui.textBrowser.setText(QtCore.QCoreApplication.translate("MainWindow", "当前进度： " + str(ui._over) + "/" + str(num)))
    ui.textBrowser_2.setText(QtCore.QCoreApplication.translate("MainWindow", "当前对比文件: " + all_pairs[now][0] + " 与 " + all_pairs[now][1]))
    d = difflib.HtmlDiff()
    f1 = read_file("./input/" + all_pairs[now][0])
    f2 = read_file("./input/" + all_pairs[now][1])
    res = d.make_file(f1, f2)
    ui.webView.setHtml(res)

class Ui_MainWindow(object):
    _over = 1
    _result = 0

    def setresult(self, x):
	    self._result = x

    def check_result(self, MainWindow):
        if(self._result == 0):
            return
        throw_pair(self._result)
        self._result = 0
        if(now == num - 1):
            MainWindow.close()
            return
        next_pair()
        self._over = self._over + 1
        set_pair(self)
        
            

    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(969, 636)
        MainWindow.setStyleSheet("background-color: rgb(255, 255, 255);")
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(40, 90, 150, 60))
        self.pushButton.setStyleSheet("background-color: rgb(115, 210, 22);\n" "")
        self.pushButton.setDefault(False)
        self.pushButton.setObjectName("pushButton")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(40, 160, 150, 60))
        self.pushButton_2.setStyleSheet("background-color: rgb(239, 41, 41);")
        self.pushButton_2.setObjectName("pushButton_2")
        self.pushButton_3 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_3.setGeometry(QtCore.QRect(40, 230, 150, 60))
        self.pushButton_3.setStyleSheet("background-color: rgb(245, 121, 0);")
        self.pushButton_3.setObjectName("pushButton_3")
        self.pushButton_4 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_4.setGeometry(QtCore.QRect(40, 300, 150, 60))
        self.pushButton_4.setCursor(QtGui.QCursor(QtCore.Qt.ArrowCursor))
        self.pushButton_4.setStyleSheet("background-color: rgb(186, 189, 182);")
        self.pushButton_4.setObjectName("pushButton_4")
        self.webView = QtWebEngineWidgets.QWebEngineView(self.centralwidget)
        self.webView.setGeometry(QtCore.QRect(220, 90, 711, 481))
        self.webView.setUrl(QtCore.QUrl("about:blank"))
        self.webView.setObjectName("webView")
        self.textBrowser = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser.setGeometry(QtCore.QRect(40, 30, 151, 41))
        self.textBrowser.setObjectName("textBrowser")
        self.textBrowser_2 = QtWidgets.QTextBrowser(self.centralwidget)
        self.textBrowser_2.setGeometry(QtCore.QRect(220, 30, 701, 41))
        self.textBrowser_2.setObjectName("textBrowser_2")
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1032, 28))
        self.menubar.setObjectName("menubar")
        self.menu = QtWidgets.QMenu(self.menubar)
        self.menu.setObjectName("menu")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)
        self.menubar.addAction(self.menu.menuAction())


        self.retranslateUi(MainWindow)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

        self.pushButton.clicked.connect(lambda:self.setresult(1));
        self.pushButton_2.clicked.connect(lambda:self.setresult(2));
        self.pushButton_3.clicked.connect(lambda:self.setresult(3));
        self.pushButton_4.clicked.connect(lambda:self.check_result(MainWindow));

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.pushButton.setText(_translate("MainWindow", "这是等价的"))
        self.pushButton_2.setText(_translate("MainWindow", "这不是等价的"))
        self.pushButton_3.setText(_translate("MainWindow", "对等价性存疑"))
        self.pushButton_4.setText(_translate("MainWindow", "确认（下一对）"))
        self.menu.setTitle(_translate("MainWindow", "人工确认程序"))

if __name__ == '__main__':
    app = QApplication(sys.argv)
    MainWindow = QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    
    # initliaze
    read_pairs()
    if(num == 0):
        sys.exit(0)
    print(num)
    set_pair(ui)

    MainWindow.show()
    app.exec_()

    with open("./output/equal.csv", 'w') as f:
        for pairs in eq_pairs:
            f.write(pairs[0] + "," + pairs[1] + "\n")
    f.close()

    with open("./output/inequal.csv", 'a') as f:
        for pairs in ineq_pairs:
            f.write(pairs[0] + "," + pairs[1] + "\n")
    f.close()
    
    with open("./output/abnormal.csv", 'a') as f:
        for pairs in abnormal_pairs:
            f.write(pairs[0] + "," + pairs[1] + "\n")
    f.close()

    sys.exit(0)
