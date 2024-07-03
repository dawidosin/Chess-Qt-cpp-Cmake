#include "headers/game.h"

Game* game;

    int main(int argc, char *argv[]) {

        QApplication app(argc, argv);

        game = new Game(nullptr, PieceColor::White);
        game->show();
        game->start();

        return app.exec();
}
