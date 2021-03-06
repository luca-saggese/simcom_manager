#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpSocket>
#include <QKeyEvent>

#define htonl(l) ((((l >> 24) & 0x000000ff)) | \
                  (((l >>  8) & 0x0000ff00)) | \
                  (((l) & 0x0000ff00) <<  8) | \
                  (((l) & 0x000000ff) << 24))
#define ntohl(l) htonl(l)

#define htons(s) ((((s) >> 8) & 0xff) | \
                  (((s) << 8) & 0xff00))
#define ntohs(s) htons(s)

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();
    void on_pushButton_GetImeiData_clicked();
    void on_pushButton_Get_Local_imeiData_clicked();
    void on_pushButton_UpdataImeiData_clicked();
    void on_tableWidget_cellDoubleClicked(int row, int column);

    void slotConnected();
    void slotDisconnected();
    void slotDataReceived();
    void slotHeaderClicked(int);
    void slotTableMenuAction(QAction *);

    void findInTableWidget(QString string);
    void UpdataImeiDataWithRow(int row);

    void openFile();

private:
    Ui::MainWindow *ui;
    QTcpSocket *tcpSocket;
    QMenu *pTableMenu;
    QAction *openAction;


    void keyPressEvent(QKeyEvent *event);

    int handle_manager_msg(void);
    int handle_one_msg(const void *m);
    int manager_login(const void *msg);
    int manager_imeiData(const void *msg);
    int manager_getLog(const void *msg);
    int manager_get433(const void *msg);
    int manager_getGSM(const void *msg);
    int manager_getGPS(const void *msg);
    int manager_getSetting(const void *msg);
    int manager_getBattery(const void *msg);
    int manager_getAT(const void *msg);
    int manager_getData(const void *msg);
    int manager_getDaily(const void *msg);
    int manager_setServerRsp(const void *msg);

    void uiShowConnectionStatus(bool connected);
    void uiShowImeiData(const char *imei, char online_offline, int version, int timestamp, float longitude, float latitude, char speed, short course);

signals:
    void send_daily2Eventdialog(QString data);
    void send_start2Eventdialog(void);
};

#endif // MAINWINDOW_H
