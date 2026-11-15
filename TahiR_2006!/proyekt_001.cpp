#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Option {
    string text;
    bool isCorrect;
};

struct Question {
    string text;
    vector<Option> options;
};

struct Quiz {
    string name;
    vector<Question> questions;
};

struct Leader {
    string name;
    int score;
    int correct;
    int incorrect;
    int pass;
};

vector<Quiz> allQuizzes;
vector<Leader> leaders;

void initQuizzes() {
    Quiz q1;
    q1.name = "Quiz1";

    Question q1_1;
    q1_1.text = "Azerbaycanin paytaxti haradir?";
    q1_1.options.push_back({ "Baki", true });
    q1_1.options.push_back({ "Xizi", false });
    q1_1.options.push_back({ "Gence", false });
    q1_1.options.push_back({ "Sumqayit", false });
    q1.questions.push_back(q1_1);

    Question q1_2;
    q1_2.text = "C++ dilinde dinamik yaddas hansi operatorla ayrilir?";
    q1_2.options.push_back({ "new", true });
    q1_2.options.push_back({ "malloc", false });
    q1_2.options.push_back({ "alloc", false });
    q1.questions.push_back(q1_2);

    Question q1_3;
    q1_3.text = "OOP-nin esas prinsiplerine hansi aid DEYIL?";
    q1_3.options.push_back({ "Compilation", true });
    q1_3.options.push_back({ "Encapsulation", false });
    q1_3.options.push_back({ "Inheritance", false });
    q1.questions.push_back(q1_3);

    allQuizzes.push_back(q1);

    Quiz q2;
    q2.name = "Quiz2";

    Question q2_1;
    q2_1.text = "Sual 1";
    q2_1.options.push_back({ "a1", true });
    q2_1.options.push_back({ "a2", false });
    q2_1.options.push_back({ "a3", false });
    q2.questions.push_back(q2_1);

    Question q2_2;
    q2_2.text = "Sual 2";
    q2_2.options.push_back({ "a1", false });
    q2_2.options.push_back({ "a2", true });
    q2_2.options.push_back({ "a3", false });
    q2.questions.push_back(q2_2);

    allQuizzes.push_back(q2);

    Quiz q3;
    q3.name = "Quiz3";

    Question q3_1;
    q3_1.text = "Dovr operatoruna hansi aiddir?";
    q3_1.options.push_back({ "for", true });
    q3_1.options.push_back({ "if", false });
    q3_1.options.push_back({ "switch", false });
    q3.questions.push_back(q3_1);

    allQuizzes.push_back(q3);
}

void shuffleQuiz(Quiz& quiz) {
    int qCount = (int)quiz.questions.size();
    for (int i = 0; i < qCount; i++) {
        int r = rand() % qCount;
        Question tempQ = quiz.questions[i];
        quiz.questions[i] = quiz.questions[r];
        quiz.questions[r] = tempQ;
    }

    for (int i = 0; i < qCount; i++) {
        int optCount = (int)quiz.questions[i].options.size();
        for (int j = 0; j < optCount; j++) {
            int r = rand() % optCount;
            Option tempOpt = quiz.questions[i].options[j];
            quiz.questions[i].options[j] = quiz.questions[i].options[r];
            quiz.questions[i].options[r] = tempOpt;
        }
    }
}

void createQuiz() {
    system("cls");
    cout << "1) Create Quiz\n\n";

    cout << "Enter Quiz name: ";
    string qName;
    getline(cin, qName);
    if (qName.empty()) qName = "Quiz1";

    Quiz newQuiz;
    newQuiz.name = qName;

    int qNum = 1;
    while (true) {
        system("cls");
        cout << "Quiz: " << qName << "\n\n";
        cout << "Question " << qNum << " : ";
        string qText;
        getline(cin, qText);
        if (qText.empty()) break;

        Question q;
        q.text = qText;

        int optNum = 1;
        while (true) {
            cout << "Answer " << optNum << " : ";
            string optText;
            getline(cin, optText);
            if (optText.empty()) {
                if (optNum <= 2) {
                    cout << "Minimum 2 variant yazin!\n";
                    continue;
                }
                break;
            }
            q.options.push_back({ optText, false });
            optNum++;
        }

        cout << "\nDuzgun cavab nomresi (1-" << (optNum - 1) << "): ";
        int correctNum = 1;
        cin >> correctNum;
        cin.ignore();

        if (correctNum < 1 || correctNum >= optNum) correctNum = 1;
        q.options[correctNum - 1].isCorrect = true;

        newQuiz.questions.push_back(q);
        qNum++;

        cout << "\n1 : new\n";
        cout << "2 : back\n";
        cout << "3 : save\n";
        cout << "Secim: ";
        int cmd = 3;
        cin >> cmd;
        cin.ignore();

        if (cmd == 1) {
            continue;
        }
        else if (cmd == 2) {
            return;
        }
        else {
            allQuizzes.push_back(newQuiz);
            break;
        }
    }
}

void startQuiz(string playerName) {
    if (allQuizzes.empty()) {
        system("cls");
        cout << "Quiz tapilmadi!\n\n";
        system("pause");
        return;
    }

    system("cls");
    cout << "2) Start Quiz\n\n";
    cout << "Telebe: " << playerName << "\n\n";
    cout << "Select quiz:\n\n";

    for (int i = 0; i < (int)allQuizzes.size(); i++) {
        cout << "  " << (i + 1) << ". " << allQuizzes[i].name << "\n";
    }
    cout << "\nSecim (1-" << allQuizzes.size() << "): ";

    int choice = 0;
    cin >> choice;
    cin.ignore();

    if (choice <= 0 || choice > (int)allQuizzes.size()) return;

    Quiz activeQuiz = allQuizzes[choice - 1];
    shuffleQuiz(activeQuiz);

    int total = (int)activeQuiz.questions.size();
    vector<int> userAns(total, -1);

    int cur = 0;
    while (true) {
        system("cls");
        Question& q = activeQuiz.questions[cur];

        cout << "Sual " << (cur + 1) << " / " << total << ": " << q.text << "\n\n";

        for (int i = 0; i < (int)q.options.size(); i++) {
            cout << "  " << (i + 1) << ") " << q.options[i].text;
            if (userAns[cur] == i) {
                cout << "  <-- [SECILIB]";
            }
            cout << "\n";
        }

        cout << "\n----------------------------------------\n";
        cout << "[1-" << q.options.size() << "] Cavabi sec\n";
        cout << "[P]   Previus\n";
        cout << "[N]   Next\n";
        cout << "[S]   Submit\n";
        cout << "----------------------------------------\n";
        cout << "Secim: ";

        string input;
        getline(cin, input);
        if (input.empty()) continue;

        if (input[0] >= '1' && input[0] <= '9') {
            int opt = input[0] - '1';
            if (opt >= 0 && opt < (int)q.options.size()) {
                userAns[cur] = opt;
                if (cur + 1 < total) cur++;
            }
            continue;
        }

        if (input == "P" || input == "p") {
            if (cur > 0) cur--;
        }
        else if (input == "N" || input == "n") {
            if (cur + 1 < total) cur++;
        }
        else if (input == "S" || input == "s") {
            break;
        }
    }

    int correct = 0;
    int incorrect = 0;
    int pass = 0;

    for (int i = 0; i < total; i++) {
        if (userAns[i] == -1) {
            pass++;
        }
        else if (activeQuiz.questions[i].options[userAns[i]].isCorrect) {
            correct++;
        }
        else {
            incorrect++;
        }
    }

    system("cls");
    cout << "Result\n\n";
    cout << "Telebe:    " << playerName << "\n";
    cout << "Correct:   " << correct << "\n";
    cout << "InCorrect: " << incorrect << "\n";
    cout << "Pass:      " << pass << "\n";
    cout << "Bal:       " << (correct * 10) << " xal\n\n";

    leaders.push_back({ playerName, correct * 10, correct, incorrect, pass });

    system("pause");
}

void showLeaderboard() {
    system("cls");
    cout << "3) Leader Board(Top 10)\n\n";
    cout << "No   Ad             Bal   Duz   Sehv   Pass\n";
    cout << "-------------------------------------------\n";

    if (leaders.empty()) {
        cout << "     (Hele hec bir netice yoxdur)\n";
    }
    else {
        int n = (int)leaders.size();
        for (int i = 0; i < n - 1; i++) {
            for (int j = 0; j < n - i - 1; j++) {
                if (leaders[j].score < leaders[j + 1].score) {
                    Leader tempL = leaders[j];
                    leaders[j] = leaders[j + 1];
                    leaders[j + 1] = tempL;
                }
            }
        }

        int limit = (n > 10) ? 10 : n;
        for (int i = 0; i < limit; i++) {
            cout << (i + 1) << ".   "
                << leaders[i].name << "\t    "
                << leaders[i].score << "     "
                << leaders[i].correct << "     "
                << leaders[i].incorrect << "      "
                << leaders[i].pass << "\n";
        }
    }

    cout << "-------------------------------------------\n";
    cout << "0) Exit\n";
    cout << "Secim: ";
    string ex;
    getline(cin, ex);
}

int main() {
    srand(time(0));
    initQuizzes();

    while (true) {
        system("cls");
        cout << "1. Admin\n";
        cout << "2. Guest\n";
        cout << "0. Exit\n\n";
        cout << "Secim: ";

        int role = 0;
        cin >> role;
        cin.ignore();

        if (role == 0) break;

        bool isAdmin = false;
        string userName = "Guest";

        if (role == 1) {
            cout << "Parol: ";
            string pass;
            getline(cin, pass);
            if (pass == "admin123") {
                isAdmin = true;
                userName = "Admin";
            }
            else {
                cout << "\nSehv parol!\n";
                system("pause");
                continue;
            }
        }
        else if (role == 2) {
            cout << "Enter your name: ";
            getline(cin, userName);
            if (userName.empty()) userName = "Guest";
        }
        else {
            continue;
        }

        while (true) {
            system("cls");
            cout << "Istifadeci: " << userName << " (" << (isAdmin ? "Admin" : "Guest") << ")\n\n";

            if (isAdmin) {
                cout << "1) Create Quiz\n";
                cout << "2) Start Quiz\n";
                cout << "3) Leader Board(Top 10)\n";
                cout << "0) Exit\n";
            }
            else {
                cout << "1) Start Quiz\n";
                cout << "2) Leader Board(Top 10)\n";
                cout << "0) Exit\n";
            }
            cout << "\nSecim: ";

            int secim;
            cin >> secim;
            cin.ignore();

            if (isAdmin) {
                if (secim == 1) createQuiz();
                else if (secim == 2) startQuiz(userName);
                else if (secim == 3) showLeaderboard();
                else if (secim == 0) break;
            }
            else {
                if (secim == 1) startQuiz(userName);
                else if (secim == 2) showLeaderboard();
                else if (secim == 0) break;
            }
        }
    }

    system("cls");
    cout << "Ugurlar!\n";
    return 0;
}