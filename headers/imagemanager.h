#ifndef IMAGEMANAGER_H
#define IMAGEMANAGER_H

#include <QPixmap>
#include <QSize>
#include "globals.h"

/* Holds all images from the game */
struct ImageManager
{
    // ChessPiece images
    static const QPixmap& Pawn_White()
    {
        static QPixmap pixmap = QPixmap(":/img/pawn_white.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Pawn_Black()
    {
        static QPixmap pixmap = QPixmap(":/img/pawn_black.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Knight_White()
    {
        static QPixmap pixmap = QPixmap(":/img/knight_white.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Knight_Black()
    {
        static QPixmap pixmap = QPixmap(":/img/knight_black.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Bishop_White()
    {
        static QPixmap pixmap = QPixmap(":/img/bishop_white.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Bishop_Black()
    {
        static QPixmap pixmap = QPixmap(":/img/bishop_black.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Rook_White()
    {
        static QPixmap pixmap = QPixmap(":/img/rook_white.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Rook_Black()
    {
        static QPixmap pixmap = QPixmap(":/img/rook_black.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Queen_White()
    {
        static QPixmap pixmap = QPixmap(":/img/queen_white.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Queen_Black()
    {
        static QPixmap pixmap = QPixmap(":/img/queen_black.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& King_White()
    {
        static QPixmap pixmap = QPixmap(":/img/king_white.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& King_White_Danger()
    {
        static QPixmap pixmap = QPixmap(":/img/king_white_danger.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& King_Black()
    {
        static QPixmap pixmap = QPixmap(":/img/king_black.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& King_Black_Danger()
    {
        static QPixmap pixmap = QPixmap(":/img/king_black_danger.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }

    // Other images
    static const QPixmap& Undo()
    {
        static QPixmap pixmap = QPixmap(":/img/left_arrow.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Redo()
    {
        static QPixmap pixmap = QPixmap(":/img/right_arrow.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Undo_Blocked()
    {
        static QPixmap pixmap = QPixmap(":/img/left_arrow_blocked.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Redo_Blocked()
    {
        static QPixmap pixmap = QPixmap(":/img/right_arrow_blocked.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Move()
    {
        static QPixmap pixmap = QPixmap(":/img/dot.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
    static const QPixmap& Capture()
    {
        static QPixmap pixmap = QPixmap(":/img/kill.png").scaled(QSize(GLOB::BoxSize, GLOB::BoxSize), Qt::KeepAspectRatio, Qt::SmoothTransformation);
        return pixmap;
    }
};

#endif // IMAGEMANAGER_H
