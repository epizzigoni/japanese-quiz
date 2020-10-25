import pandas as pd


df = pd.read_csv('words_data.csv')
df = df.fillna(method='ffill')
# print(df)

lines = ['#ifndef WORDS_DATA_H',
         '#define WORDS_DATA_H',
         'QMap<QString, QStringList> groupMap {']

for g, gr in df.groupby('Group'):

    new_line = '{"' + g + '", {'
    for eng in gr.English:
        new_line += '"' + eng + '", '
    new_line = new_line[:-2]
    new_line += '}},'
    lines.append(new_line)

lines[-1] = lines[-1][:-1]
lines.append('};')
lines.append('QMap<QString, QStringList> ansMap {')

for _, row in df.iterrows():
    new_line = '{"' + row['English'] + '", {'
    for word in row.iloc[1:]:
        new_line += '"' + word + '", '
    new_line = new_line[:-2]
    new_line += '}},'
    lines.append(new_line)

lines[-1] = lines[-1][:-1]
lines.append('};')
lines.append('#endif // WORDS_DATA_H')


for i in range(len(lines)):
    lines[i] = '\n' + lines[i]

with open('words_data.h', 'w') as f:
    f.writelines(lines)

with open('words_data.h', 'r') as f:
    print(f.read())


