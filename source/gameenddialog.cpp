#include "../headers/gameenddialog.h"

GameEndDialog::GameEndDialog()
{}

void GameEndDialog::win(PieceColor currentcolor)
{
    setWindowTitle("Game Over");
    setFixedSize(300, 150);
    QLabel *label = nullptr;

    if(currentcolor == PieceColor::White)
    {
        label = new QLabel("Black wins!", this);
    }
    else
    {
        label = new QLabel("White wins!", this);
    }

    label->setAlignment(Qt::AlignCenter);
    restartButton = new QPushButton("Restart", this);
    exitButton = new QPushButton("Exit", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(restartButton);
    layout->addWidget(exitButton);

    setLayout(layout);
}

void GameEndDialog::draw()
{
    setWindowTitle("Game Over");
    setFixedSize(300, 150);

    QLabel *label = nullptr;
    label = new QLabel("Draw!", this);
    label->setAlignment(Qt::AlignCenter);

    restartButton = new QPushButton("Restart", this);
    exitButton = new QPushButton("Exit", this);

    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addWidget(label);
    layout->addWidget(restartButton);
    layout->addWidget(exitButton);

    setLayout(layout);
}
