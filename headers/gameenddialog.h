#ifndef GAMEENDDIALOG_H
#define GAMEENDDIALOG_H

#include <QDialog>
#include <QPushButton>
#include <QLabel>
#include <QVBoxLayout>
#include "chesspiece.h"

class GameEndDialog : public QDialog {
    Q_OBJECT

public:
    explicit GameEndDialog();

    void win(PieceColor currentcolor);
    void draw();
    QPushButton* getRestartButton() const { return restartButton; }
    QPushButton* getExitButton() const { return exitButton; }

private:
    QPushButton *restartButton;
    QPushButton *exitButton;
};

#endif // GAMEENDDIALOG_H
