#include "filedialog.h"

Dialog::Dialog(QWidget *parent, const QString &filename, int mode)
{
    QFileDialog *m_filedlg = new QFileDialog(parent,Qt::Dialog);
    m_filedlg->setOption(QFileDialog::DontUseNativeDialog,true);
    m_filedlg->setDirectory(filename);
    m_filedlg->setViewMode((QFileDialog::ViewMode)mode);
    m_filedlg->resize(800, 480);

    QStringList filters;
    filters << "Video files (*.3gp *.avi *.flv *.h264 *.m4v *.mkv *.mov *.mpeg *.mpeg2 *.mpeg4 *.mp4 *.mpg *.ts *.wmv)"
            << "Audio files (*.mp3 *.ogg)"
            << "Any files (*)";
    m_filedlg->setNameFilters(filters);

    QList<QUrl> urls;
    urls << QUrl::fromLocalFile("/media/mmcblk0p6")
         << QUrl::fromLocalFile("/media/mmcblk1p1");
    m_filedlg->setSidebarUrls(urls);

    m_mainLaout = new QGridLayout(this);
    m_mediainfo = new QTextEdit(parent);

    m_mediainfo->setReadOnly(true);

    m_mainLaout->addWidget(m_mediainfo,  0 , 0 , 2 , 1 );
    m_mainLaout->addWidget(m_filedlg,    0 , 1 , 2 , 1 );

    setSizePolicy(QSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding));

    m_fileinfo = new QFileInfo();

    QObject::connect(m_filedlg, SIGNAL(finished(int)), this, SLOT(dialogQuit()));
    QObject::connect(m_filedlg, SIGNAL(currentChanged(QString)), this, SLOT(currentFile(QString)));
    QObject::connect(m_filedlg, SIGNAL(fileSelected(QString)), this, SLOT(selectFile(QString)));
}

void Dialog::currentFile(QString file)
{
    m_fileinfo->setFile(file);
    if (m_fileinfo->isFile())
    {
        QString info;
        info = "FilePath: \n" + m_fileinfo->absoluteFilePath() + "\n" + "FileName: \n" + m_fileinfo->fileName();
        m_mediainfo->setFontPointSize(12);
        m_mediainfo->setText(info);
    }
}

void Dialog::selectFile(QString file)
{
    m_file = file;
}

void Dialog::dialogQuit()
{
    delete m_mediainfo;
    hide();
}
