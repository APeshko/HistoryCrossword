#include "crossword.h"
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QDebug>

Crossword::Crossword() {}

bool Crossword::loadFromJson(const QString &filePath) {
    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly)) {
        qWarning() << "Could not open file:" << filePath;
        return false;
    }

    QByteArray data = file.readAll();
    QJsonDocument doc(QJsonDocument::fromJson(data));
    QJsonObject json = doc.object();

    m_title = json["title"].toString();
    int rows = json["rows"].toInt();
    int cols = json["cols"].toInt();

    grid.resize(rows);
    for (auto &row : grid) {
        row.resize(cols);
        row.fill(' ');
    }

    QJsonArray questionsArray = json["questions"].toArray();
    for (const QJsonValue &value : questionsArray) {
        QJsonObject obj = value.toObject();
        Question q;
        q.text = obj["question"].toString();
        q.answer = obj["answer"].toString().toUpper();
        q.position = QPoint(obj["row"].toInt(), obj["col"].toInt());
        q.isHorizontal = obj["horizontal"].toBool();
        questions.push_back(q);
    }

    buildGrid();
    return true;
}

void Crossword::buildGrid() {
    for (const Question &q : questions) {
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
}

const std::vector<Question> &Crossword::getQuestions() const {
    return questions;
}

const QChar &Crossword::cellAt(int row, int col) const {
    return grid[row][col];
}

int Crossword::rows() const {
    return grid.size();
}

int Crossword::cols() const {
    return grid.isEmpty() ? 0 : grid[0].size();
}

QString Crossword::title() const {
    return m_title;
}
