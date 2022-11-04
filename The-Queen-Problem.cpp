#include <iostream>
#include <vector>
#include <string>

void Output(std::vector<std::vector<bool>>& board, std::vector<std::string>& lines, bool last);

// Рекурсивная функция для решения бэк-трэкингом.
// board - доска, board[i][j] == true если стоит ферзь в [i][j], иначе false.
// lines - вспомогательный массив для сбора выводимых в консоль строк.
// N - количество ферзей, cnt - сколько ферзей уже удалось расставить
// (start_i, start_j) - с какой позиции пытаться расставлять следующего ферзя
void Solve(std::vector<std::vector<bool>>& board, std::vector<std::string>& lines,
    int N, int& num_sol, int cnt = 0, int start_i = 0, int start_j = 0, int depth = 0) {
    if (cnt >= N) {
        Output(board, lines, false);
        // Увеличиваем счётчик числа решений.
        ++num_sol;
        return;
    }

    // Обходим всю доску, начиная с позиции последнего ферзя.
    for (int i = start_i; i < board.size(); ++i)
        for (int j = i == start_i ? start_j : 0; j < board[i].size(); ++j) {
            bool attacked = false;
            // Цикл по k проверяет атакована ли позиция [i][j]
            for (int k = 0; k < (board.size() > board[i].size() ?
                board.size() : board[i].size()); ++k)
                if (
                    // Есть ли атака по горизонтали
                    k < board[i].size() && k != j && board[i][k] ||
                    // Атака по вертикали
                    k < board.size() && k != i && board[k][j] ||
                    // Атака по главной диагонали
                    k < board.size() && k != i && 0 <= j - i + k &&
                    j - i + k < board[i].size() && board[k][j - i + k] ||
                    // Атака по второстепенной диагонали
                    k < board.size() && k != i && 0 <= j + i - k &&
                    j + i - k < board[i].size() && board[k][j + i - k]
                    ) {
                    attacked = true;
                    break;
                }
            if (attacked)
                continue;
            // Позиция [i][j] не под атакой, потому ставим ферзя
            board[i][j] = true;
            // Рекурисвный спуск для расстановки следующего ферзя
            Solve(board, lines, N, num_sol, cnt + 1, i, j + 1, depth + 1);
            // Бэктрэкинг, удаляем прошлого установленного ферзя
            board[i][j] = false;
        }
    if (depth == 0)
        Output(board, lines, true);
}

// Функция для вывода решений.
void Output(std::vector<std::vector<bool>>& board, std::vector<std::string>& lines, bool last) {
    // Вывод решения в консоль. Поставить тут if (0) если не нужно выводить доски в консоль.
    if (1) {
        if (!last) {
            // Добавление одной доски к текущим строкам.
            for (int i = 0; i < board.size(); ++i) {
                for (int j = 0; j < board[i].size(); ++j)
                    lines[i].push_back(board[i][j] ? 'Q' : '.');
                // Символ | в качестве разделителя между досок.
                lines[i] += "|";
            }
        }
        // Если длина строк превысила ширину консоли (70), то выводим строки и разделитель.
        if (lines.at(0).size() >= 70 || last && !lines.at(0).empty()) {
            for (int i = 0; i < lines.size(); ++i)
                std::cout << lines[i] << std::endl;
            for (int j = 0; j < lines.at(0).size(); ++j)
                std::cout << (lines.at(0)[j] == '|' ? '+' : '-');
            std::cout << std::endl;
            // Очищаем строки для следующих выводов досок.
            lines.clear();
            lines.resize(board.size());
        }
    }
}

int main() {
    // Входные параметры, rows - число рядов доски, cols - число столбцов
    // N - число ферзей которые нужно расставить
    int const rows = 8, cols = 8, N = 8;
    // Заполняем пустыми значениями доску размером [rows][cols]
    std::vector<std::vector<bool>> board(rows, std::vector<bool>(cols));
    std::vector<std::string> lines(rows);
    // Ответ, число решений
    int num_sol = 0;
    // Запускаем бэк-трэкинг поиск решений.
    Solve(board, lines, N, num_sol);
    // Вывод ответа.
    std::cout << "Number of solutions: " << num_sol << std::endl;
}