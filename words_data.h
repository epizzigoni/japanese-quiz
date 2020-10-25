#ifndef WORDS_DATA_H
#define WORDS_DATA_H


QMap<QString, QStringList> groupMap {
    {"01 - The Body", {"mouth", "eye", "ear", "nose"}},
    {"02 - Bed and Bath", {"pillow", "bed", "futon", "blanket"}}
};

QMap<QString, QStringList> ansMap {
    {"mouth", {"kuchi", "くち", "口"}},
    {"eye", {"me", "め", "目"}},
    {"ear",	{"mimi", "みみ", "耳"}},
    {"nose", {"hana", "はな", "鼻"}},

    {"pillow", {"makura", "まくら", "枕"}},
    {"bed", {"beddo", "ベッド", "ベッド"}},
    {"futon", {"futon", "ふとん", "布団"}},
    {"blanket", {"moufu", "もうふ", "毛布"}}
};




#endif // WORDS_DATA_H
