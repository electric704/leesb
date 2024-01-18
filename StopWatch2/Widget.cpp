#include "Widget.h"

Widget::Widget(QWidget* parent)
    : QWidget(parent),m_nSeconds(0)
{
    m_pTimelable = new QLabel();
    m_pTimelable->setAlignment(Qt::AlignCenter);
    // QLCDNumber 생성
    m_pLcdNumber = new QLCDNumber();  
    m_pLcdNumber->setSegmentStyle(QLCDNumber::Flat);

    m_pTimer = new QTimer(this);
    connect(m_pTimer, SIGNAL(timeout()), this, SLOT(UpdateTimer()));

    QVBoxLayout* vBoxLayout = new QVBoxLayout();
 
    vBoxLayout->addWidget(m_pLcdNumber);

    //Start,Stop,ResetTimer 버튼
    QHBoxLayout* hboxLayout = new QHBoxLayout();
    QPushButton* btn[3];

    QString btnStr[3] = { "Start", "Stop", "ResetTimer" };
    int nSize = (sizeof(btnStr) / sizeof(*btnStr));

    for (int i = 0; i < nSize; ++i)
    {
        btn[i] = new QPushButton(btnStr[i]);
        hboxLayout->addWidget(btn[i]);
    }
    //start아이콘 적용,사이즈 설정
    btn[0]->setIcon(QIcon(":/new/prefix1/start.png"));
    btn[0]->setIconSize(QSize(30, 30));
    //stop 아이콘 적용,사이즈 설정
    btn[1]->setIcon(QIcon(":/new/prefix1/stop.png"));
    btn[1]->setIconSize(QSize(30, 30));
    //reset 아이콘 적용,사이즈 설정
    btn[2]->setIcon(QIcon(":/new/prefix1/reset.png"));
    btn[2]->setIconSize(QSize(30, 30));
    vBoxLayout->addLayout(hboxLayout);


    //Record버튼
    QPushButton* RecordButton = new QPushButton("Record");
    //record아이콘 적용,사이즈 설정
    RecordButton->setIcon(QIcon(":/new/prefix1/record.png"));
    RecordButton->setIconSize(QSize(30, 30));

    //ResetRecord버튼
    QPushButton* ResetRecordButton = new QPushButton("ResetRecord");
    //reset아이콘 적용,사이즈 설정
    ResetRecordButton->setIcon(QIcon(":/new/prefix1/reset.png"));
    ResetRecordButton->setIconSize(QSize(30, 30));
    QHBoxLayout* bottomLayout = new QHBoxLayout();
    
    bottomLayout->addWidget(RecordButton);
    bottomLayout->addWidget(ResetRecordButton);
    vBoxLayout->addLayout(bottomLayout);
    vBoxLayout->addLayout(hboxLayout);

    m_pTextEdit = new QTextEdit();
    m_pTextEdit->setReadOnly(true);
    m_pTextEdit->clear();
    vBoxLayout->addWidget(m_pTextEdit);
    //Save 버튼
    QPushButton* SaveButton = new QPushButton("Save");
    //save아이콘 적용
    SaveButton->setIcon(QIcon(":/new/prefix1/save.png"));
    SaveButton->setIconSize(QSize(30, 30));
    //load버튼
    QPushButton* LoadButton = new QPushButton("Load");
    //load아이콘 적용
    LoadButton->setIcon(QIcon(":/new/prefix1/load.png"));
    LoadButton->setIconSize(QSize(30, 30));
    QHBoxLayout* saveLoadLayout = new QHBoxLayout();
    saveLoadLayout->addWidget(SaveButton);
    saveLoadLayout->addWidget(LoadButton);
    vBoxLayout->addLayout(saveLoadLayout);

    setLayout(vBoxLayout);

    connect(btn[0], SIGNAL(clicked()), this, SLOT(StartTimer()));
    connect(btn[1], SIGNAL(clicked()), this, SLOT(StopTimer()));
    connect(btn[2], SIGNAL(clicked()), this, SLOT(ResetTimer()));
    connect(RecordButton, SIGNAL(clicked()), this, SLOT(RecordTimer()));
    connect(ResetRecordButton, SIGNAL(clicked()), this, SLOT(ResetRecord()));
    connect(SaveButton, SIGNAL(clicked()), this, SLOT(Save()));
    connect(LoadButton, SIGNAL(clicked()), this, SLOT(Load()));

    m_textFile.setFileName("savedText.txt");
    if (m_textFile.open(QIODevice::ReadWrite | QIODevice::Text))
    {
        QTextStream in(&m_textFile);
    }
}

Widget::~Widget()
{

}

void Widget::UpdateTimer()
{

    QTime startTime(0, 0, 0);
    startTime = startTime.addMSecs(m_nSeconds);

    QString StartTimeString = startTime.toString("hh:mm:ss:zzz");
    m_pTimelable->setText(StartTimeString);

    // QTIME을 QLCDNumber로 표시
    m_pLcdNumber->display(StartTimeString);

    ++m_nSeconds;
}


void Widget::StartTimer()
{
    m_pTimer->start(1);
}

void Widget::StopTimer()
{
    m_pTimer->stop();
}

void Widget::ResetTimer()
{
    m_pTimer->stop();
    m_nSeconds = 0;
    m_pTimelable->setText("00:00:00:000");

    // QLCDNumber를 0으로 초기화
    m_pLcdNumber->display(0);
   
}

void Widget::RecordTimer()
{
    QString strRecordTime = m_pTimelable->text();
    m_pTextEdit->append(strRecordTime);
}

void Widget::ResetRecord()
{
    m_pTextEdit->clear();
}

    
void Widget::Save()
{
   m_textFile.resize(0); 

    QTextStream out(&m_textFile);
    out << m_pTextEdit->toPlainText();
    }

void Widget::Load()
{
    if (m_textFile.isOpen() && m_textFile.isReadable())
    {
        m_textFile.seek(0);
        QTextStream in(&m_textFile);
        m_pTextEdit->setPlainText(in.readAll());
    }
}

