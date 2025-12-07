#include <iostream>
#include <string>
#include <ctime>
#include <cctype>
using namespace std;
// -------------------- QUESTION NODE --------------------
struct Question {
string text;
string optA, optB, optC, optD;
char correct;
int marks;
Question *next;
Question() { next = NULL; }
};
// -------------------- SUBJECT STRUCT (NOT LINKED) --------------------
struct Subject {
string name;
Question *qhead;
Subject() { qhead = NULL; }
};
Subject *subjects[10];
int subjectCount = 0;
int timeLimit = 30;
double NEG_PENALTY = 0.25;
void teacherMenu();
void studentExam();
void addSubject();
int selectSubject();
void addQuestion(Subject *s);
void viewQuestions(Subject *s);
void removeQuestion(Subject *s);
int main() {
int choice;
do {
cout << "\n===== ONLINE EXAM SYSTEM =====\n";
cout << "1. Teacher\n2. Student\n0. Exit\nEnter choice: ";
cin >> choice;
switch (choice) {
case 1: teacherMenu(); break;
case 2: studentExam(); break;
case 0: cout << "Goodbye!\n"; break;
default: cout << "Invalid choice.\n";
}
} while (choice != 0);
return 0;
}
void teacherMenu() {
int ch;
do {
cout << "\n--- TEACHER MENU ---\n";
cout << "1. Add Subject\n";
cout << "2. Set Timer (" << timeLimit << " min)\n";
cout << "3. Set Negative Marking (-" << NEG_PENALTY << ")\n";
cout << "4. Add Question\n";
cout << "5. Remove Question\n";

cout << "6. View Questions\n";
cout << "0. Back\n";
cout << "Enter choice: ";
cin >> ch;
switch (ch) {
case 1:
addSubject();
break;
case 2:
cout << "Enter new time limit: ";
cin >> timeLimit;
break;
case 3:
cout << "Enter negative marks per wrong answer: ";
cin >> NEG_PENALTY;
break;
case 4: {
int index = selectSubject();
if (index != -1) addQuestion(subjects[index]);
break;
}
case 5: {
int index = selectSubject();
if (index != -1) removeQuestion(subjects[index]);
break;
}
case 6: {
int index = selectSubject();
if (index != -1) viewQuestions(subjects[index]);
break;
}
case 0: break;
default: cout << "Invalid.\n";
}
} while (ch != 0);
}
void addSubject() {
if (subjectCount >= 10) {
cout << "Maximum subjects reached!\n";
return;
}
cin.ignore();
subjects[subjectCount] = new Subject();
cout << "Enter subject name: ";
getline(cin, subjects[subjectCount]->name);
subjectCount++;
cout << "Subject added!\n";
}
int selectSubject() {
if (subjectCount == 0) {
cout << "No subjects available.\n";
return -1;
}
cout << "\n--- SUBJECTS ---\n";
for (int i = 0; i < subjectCount; i++)
cout << i+1 << ". " << subjects[i]->name << endl;
cout << "Select subject: ";

int choice;
cin >> choice;
if (choice < 1 || choice > subjectCount)
return -1;
return choice - 1;
}
void addQuestion(Subject *s) {
cin.ignore();
Question *q = new Question();
cout << "\nEnter question text:\n> ";
getline(cin, q->text);
cout << "Option A: "; getline(cin, q->optA);
cout << "Option B: "; getline(cin, q->optB);
cout << "Option C: "; getline(cin, q->optC);
cout << "Option D: "; getline(cin, q->optD);
cout << "Correct option (A/B/C/D): ";
cin >> q->correct;
q->correct = toupper(q->correct);
cout << "Enter marks for this question: ";
cin >> q->marks;
if (s->qhead == NULL) {
s->qhead = q;
} else {
Question *temp = s->qhead;
while (temp->next != NULL)
temp = temp->next;
temp->next = q;
}
cout << "Question added!\n";
}
void viewQuestions(Subject *s) {
if (s->qhead == NULL) {
cout << "No questions.\n";
return;
}
cout << "\n--- QUESTIONS ---\n";
Question *temp = s->qhead;
int i = 1;
while (temp != NULL) {
cout << i << ") " << temp->text
<< " [Ans: " << temp->correct
<< ", Marks: " << temp->marks << "]\n";
temp = temp->next;
i++;
}
}
void removeQuestion(Subject *s) {
if (s->qhead == NULL) {
cout << "No questions to remove.\n";
return;
}
viewQuestions(s);
cout << "Enter question number to remove: ";
int n;
cin >> n;
Question *temp = s->qhead;

if (n == 1) {
s->qhead = temp->next;
delete temp;
cout << "Removed.\n";
return;
}
for (int i = 1; temp != NULL && i < n - 1; i++)
temp = temp->next;
if (temp == NULL || temp->next == NULL) {
cout << "Invalid.\n";
return;
}
Question *del = temp->next;
temp->next = del->next;
delete del;
cout << "Question removed.\n";
}
void studentExam() {
int index = selectSubject();
if (index == -1) return;
Subject *s = subjects[index];
if (s->qhead == NULL) {
cout << "No questions available.\n";
return;
}
cout << "\nExam: " << s->name << endl;
cout << "Time limit: " << timeLimit << " minutes\n";
cout << "Negative marking: -" << NEG_PENALTY << endl;
cin.ignore();
cout << "Press ENTER to start...";
cin.get();
time_t start = time(NULL);
int correct = 0, wrong = 0;
double score = 0;
Question *q = s->qhead;
int qNo = 1;
while (q != NULL) {
time_t now = time(NULL);
if (difftime(now, start) / 60.0 >= timeLimit) {
cout << "\nTime up!\n";
break;
}
cout << "\nQ" << qNo << ") " << q->text << "\n";
cout << "A) " << q->optA << "\n";
cout << "B) " << q->optB << "\n";
cout << "C) " << q->optC << "\n";
cout << "D) " << q->optD << "\n";
cout << "Enter answer (A/B/C/D) or S to Skip: ";
char ans;
cin >> ans;
ans = toupper(ans);
if (ans == 'S') {
}
else if (ans == q->correct) {
score += q->marks;
correct++;
}

else {
score -= NEG_PENALTY;
wrong++;
}
q = q->next;
qNo++;
}
cout << "\n----- RESULT -----\n";
cout << "Correct: " << correct << endl;
cout << "Wrong: " << wrong << endl;
cout << "Final Score: " << score << endl;
}
