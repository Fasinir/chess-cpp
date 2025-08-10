#ifndef GAMESETTINGS_H
#define GAMESETTINGS_H

#endif // GAMESETTINGS_H

#pragma once

#include <QTime>

enum class GameMode {
    kLocal,
    kEngine
};

struct GameSettings {
    GameMode mode_;
    QString player1_name_;
    QString player2_name_;
    QString white_player_name_;
    QString black_player_name_;
    QTime base_time_;
    int increment_seconds_;
};
