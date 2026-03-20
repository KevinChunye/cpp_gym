#include <cmath>
#include <cstdio>
#include <vector>
#include <iostream>
#include <algorithm>
using namespace std;

class Student{
    private:
        static const int NUM_SUBJECT = 5;
        vector<int> scores;
    public:
        // constructor
        Student(): scores(NUM_SUBJECT){}
        
        // input function
        void input(){
            for(int i = 0; i < NUM_SUBJECT; i++){
                cin >> scores[i];
            }
        }
        // calculate total score
        int calculateTotalScore(){
            int sum = 0;
            for(int score: scores){
                sum += score;
            }
            return sum;
        }
    
};

int main() {
    /* Enter your code here. Read input from STDIN. Print output to STDOUT */   
    int n;
    cin >> n;
    
    vector<Student> students(n);
    
    for (int i = 0; i < n; i++){
        students[i].input();
    }
    
    int kristen_score = students[0].calculateTotalScore();
    
    // count higher scores
    int count = 0;
    for (int i = 1; i < n; i++){
        if (students[i].calculateTotalScore() > kristen_score){
            count++;
        }
    }
    cout << count;
    return 0;
}
