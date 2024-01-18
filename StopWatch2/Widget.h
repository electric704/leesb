
#ifndef WIDGET_H
#define WIDGET_H

#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QTextEdit>
#include <QLabel>
#include <QTimer>
#include <QFile>
#include <QFiledialog>
#include <QLCDNumber>
#include <QDateTime>
#include <QIcon>



class Widget : public QWidget
{
    Q_OBJECT

public:
    Widget(QWidget* parent = nullptr);
    ~Widget();

private:
    QLabel* m_pTimelable{nullptr};
    QTimer* m_pTimer{nullptr};
    QTextEdit* m_pTextEdit{nullptr};
    QPushButton* m_pStartButton{ nullptr };
    QPushButton* m_pStopButton{ nullptr };
    QPushButton* m_pTimeResetButton{ nullptr };
    QPushButton* m_pRecordButton{ nullptr };
    QPushButton* m_pRecordResetButton{ nullptr };
    QPushButton* m_pSaveButton{ nullptr };
    QPushButton* m_pLoadButton{ nullptr };
    QLCDNumber* m_pLcdNumber{ nullptr }; 
    int m_nSeconds;
    QFile m_textFile;



private slots:
    void UpdateTimer();
    void StartTimer();
    void StopTimer();
    void ResetTimer();
    void RecordTimer();
    void ResetRecord();
    void Save();
    void Load();
};

#endif
