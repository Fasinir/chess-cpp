#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#endif // GAMESETTINGS_H

#pragma once

#include <QString>
#include <QTime>

enum class GameMode {
    Local,
    Engine
};

struct GameSettings {
    GameMode mode;
    QString player1Name;
    QString player2Name;
    QString whitePlayerName;
    QString blackPlayerName;
    QTime baseTime;
    int incrementSeconds;
};
