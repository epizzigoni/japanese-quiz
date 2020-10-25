#ifndef WORDS_DATA_H
#define WORDS_DATA_H


QMap<QString, QStringList> groupMap {
    {"01 - The Body", {"mouth", "eye", "ear", "nose"}},
    {"02 - Bed and Bath", {"pillow", "bed", "futon", "blanket"}}
};

QMap<QString, QStringList> ansMap {
    {"mouth", {"mouth", "kuchi", "くち", "口"}},
    {"eye", {"eye", "me", "め", "目"}},
    {"ear",	{"ear", "mimi", "みみ", "耳"}},
    {"nose", {"nose", "hana", "はな", "鼻"}},

    {"pillow", {"pillow", "makura", "まくら", "枕"}},
    {"bed", {"bed", "beddo", "ベッド", "ベッド"}},
    {"futon", {"futon", "futon", "ふとん", "布団"}},
    {"blanket", {"blanket", "moufu", "もうふ", "毛布"}}
};




#endif // WORDS_DATA_H
