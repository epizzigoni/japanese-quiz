
#ifndef WORDS_DATA_H
#define WORDS_DATA_H
QMap<QString, QStringList> groupMap {
{"01 - The Body", {"mouth", "eye", "ear", "nose", "face", "hand", "foot", "finger", "head", "tooth"}},
{"02 - Bed and Bath", {"pillow", "bed", "futon", "blanket", "towel", "bath", "soap", "toothbrush", "mirror", "window"}}
};
QMap<QString, QStringList> ansMap {
{"mouth", {"mouth", "kuchi", "くち", "口"}},
{"eye", {"eye", "me", "め", "目"}},
{"ear", {"ear", "mimi", "みみ", "耳"}},
{"nose", {"nose", "hana", "はな", "鼻"}},
{"face", {"face", "kao", "かお", "顔"}},
{"hand", {"hand", "te", "て", "手"}},
{"foot", {"foot", "ashi", "あし", "足"}},
{"finger", {"finger", "yubi", "ゆび", "指"}},
{"head", {"head", "atama", "あたま", "頭"}},
{"tooth", {"tooth", "ha", "は", "歯"}},
{"pillow", {"pillow", "makura", "まくら", "枕"}},
{"bed", {"bed", "beddo", "ベッド", "ベッド"}},
{"futon", {"futon", "futon", "ふとん", "布団"}},
{"blanket", {"blanket", "moufu", "もうふ", "毛布"}},
{"towel", {"towel", "taoru", "タオル", "タオル"}},
{"bath", {"bath", "ofuro", "おふろ", "お風呂"}},
{"soap", {"soap", "sekken", "せっけん", "石けん"}},
{"toothbrush", {"toothbrush", "haburashi", "ハブラシ", "歯ブラシ"}},
{"mirror", {"mirror", "kagami", "かがみ", "鏡"}},
{"window", {"window", "mado", "まど", "窓"}}
};
#endif // WORDS_DATA_H