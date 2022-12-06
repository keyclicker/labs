#include "player.h"

#include "playercontrols.h"
#include "videowidget.h"

#include <QMediaMetaData>
#include <QMediaDevices>
#include <QAudioDevice>
#include <QAudioOutput>
#include <QMediaFormat>
#include <QtWidgets>

Player::Player(QWidget *parent)
    : QWidget(parent)
{

    // Creating Player
    m_player = new QMediaPlayer(this);
    m_audioOutput = new QAudioOutput(this);
    m_player->setAudioOutput(m_audioOutput);

    // Video Widget
    m_videoWidget = new VideoWidget(this);
    m_player->setVideoOutput(m_videoWidget);

    // Slider
    m_slider = new QSlider(Qt::Horizontal, this);
    m_slider->setRange(0, 1);
    connect(m_slider, &QSlider::sliderMoved, this, &Player::seek);

    // Duration Label
    m_labelDuration = new QLabel();
    m_labelDuration->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

    // Player Controls
    PlayerControls *controls = new PlayerControls();
    controls->setState(m_player->playbackState());
    controls->setVolume(m_audioOutput->volume());
    controls->setMuted(controls->isMuted());

    // Open button
    QPushButton *openButton = new QPushButton(tr("Open"), this);
    m_fullScreenButton = new QPushButton(tr("FullScreen"), this);
    m_fullScreenButton->setCheckable(true);

    // Connecting
    connect(m_player, &QMediaPlayer::durationChanged, this, &Player::durationChanged);
    connect(m_player, &QMediaPlayer::positionChanged, this, &Player::positionChanged);

    connect(controls, &PlayerControls::forward, this, &Player::seekForward);
    connect(controls, &PlayerControls::backward, this, &Player::seekBackward);

    connect(controls, &PlayerControls::play, m_player, &QMediaPlayer::play);
    connect(controls, &PlayerControls::pause, m_player, &QMediaPlayer::pause);
    connect(controls, &PlayerControls::stop, m_player, &QMediaPlayer::stop);
    connect(controls, &PlayerControls::changeVolume, m_audioOutput, &QAudioOutput::setVolume);
    connect(controls, &PlayerControls::changeMuting, m_audioOutput, &QAudioOutput::setMuted);
    connect(controls, &PlayerControls::changeRate, m_player, &QMediaPlayer::setPlaybackRate);
    connect(controls, &PlayerControls::stop, m_videoWidget, QOverload<>::of(&QVideoWidget::update));

    connect(m_player, &QMediaPlayer::playbackStateChanged, controls, &PlayerControls::setState);
    connect(m_audioOutput, &QAudioOutput::volumeChanged, controls, &PlayerControls::setVolume);
    connect(m_audioOutput, &QAudioOutput::mutedChanged, controls, &PlayerControls::setMuted);

    connect(m_fullScreenButton, &QPushButton::clicked, m_videoWidget, &QVideoWidget::setFullScreen);
    connect(m_videoWidget, &QVideoWidget::fullScreenChanged, m_fullScreenButton, &QPushButton::setChecked);

    connect(openButton, &QPushButton::clicked, this, &Player::open);

    // Duration slider and label layout
    QHBoxLayout *hLayout = new QHBoxLayout;
    hLayout->addWidget(m_slider);
    hLayout->addWidget(m_labelDuration);

    // Controls layout
    QBoxLayout *controlLayout = new QHBoxLayout;
    controlLayout->setContentsMargins(0, 0, 0, 0);
    controlLayout->addWidget(openButton);
    controlLayout->addStretch(1);
    controlLayout->addWidget(controls);
    controlLayout->addStretch(1);
    controlLayout->addWidget(m_fullScreenButton);

    // Player layout
    QBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(m_videoWidget);
    layout->addLayout(controlLayout);
    layout->addLayout(hLayout);

    setLayout(layout);
    resize(1280, 720);
}

bool Player::isPlayerAvailable() const
{
    return m_player->isAvailable();
}

void Player::open()
{
    QFileDialog fileDialog(this);
    fileDialog.setAcceptMode(QFileDialog::AcceptOpen);
    fileDialog.setWindowTitle(tr("Open Files"));
    fileDialog.setDirectory(QStandardPaths::standardLocations(QStandardPaths::MoviesLocation).value(0, QDir::homePath()));
    if (fileDialog.exec() == QDialog::Accepted)
        m_player->setSource(fileDialog.selectedUrls()[0]);
}

void Player::durationChanged(qint64 duration)
{
    m_duration = duration / 1000;
    m_slider->setMaximum(duration);
}

void Player::positionChanged(qint64 progress)
{
    if (!m_slider->isSliderDown())
        m_slider->setValue(progress);

    updateDurationInfo(progress / 1000);
}

void Player::seek(int mseconds)
{
    m_player->setPosition(mseconds);
}

void Player::seekForward()
{
    m_player->setPosition(m_player->position() + 10000);
}

void Player::seekBackward()
{
    m_player->setPosition(m_player->position() - 10000);
}


void Player::updateDurationInfo(qint64 currentInfo)
{
    QString tStr;
    if (currentInfo || m_duration) {
        QTime currentTime((currentInfo / 3600) % 60, (currentInfo / 60) % 60,
            currentInfo % 60, (currentInfo * 1000) % 1000);
        QTime totalTime((m_duration / 3600) % 60, (m_duration / 60) % 60,
            m_duration % 60, (m_duration * 1000) % 1000);
        QString format = "mm:ss";
        if (m_duration > 3600)
            format = "hh:mm:ss";
        tStr = currentTime.toString(format) + " / " + totalTime.toString(format);
    }
    m_labelDuration->setText(tStr);
}
