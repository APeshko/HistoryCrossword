#include "jsoncrosswordloader.h"
#include "crossworddata.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>

ICrossword* JsonCrosswordLoader::load(const QString& filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        return nullptr;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject json = doc.object();

    QString title = json["title"].toString();
    int rows = json["rows"].toInt();
    int cols = json["cols"].toInt();

    QVector<QVector<QChar>> grid(rows);
    for (auto& row : grid) {
        row.resize(cols);
        row.fill(' ');
    }

    std::vector<Question> questions;
    QJsonArray questionsArray = json["questions"].toArray();
    for (const QJsonValue& value : questionsArray) {
        QJsonObject obj = value.toObject();
        Question q;
        q.text = obj["question"].toString();
        q.answer = obj["answer"].toString().toUpper();
        q.position = QPoint(obj["row"].toInt(), obj["col"].toInt());
        q.isHorizontal = obj["horizontal"].toBool();
        questions.push_back(q);

        // Fill grid
        int row = q.position.x();
        int col = q.position.y();
        for (int i = 0; i < q.answer.length(); ++i) {
            if (q.isHorizontal) {
                if (col + i < grid[row].size()) {
                    grid[row][col + i] = q.answer[i];
                }
            } else {
                if (row + i < grid.size()) {
                    grid[row + i][col] = q.answer[i];
                }
            }
        }
    }

    return new CrosswordData(title, grid, questions);
}
