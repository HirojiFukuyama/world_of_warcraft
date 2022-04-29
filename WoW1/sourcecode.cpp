#include <iostream>
#include <string>
using namespace std;
int HD, HN, HI, HL, HW;
bool cr = true, cb = true; // short for canred, canblue

string make_time(int time) {
    string stime;
    if (time < 10) {
        stime = "00" + to_string(time);
    }
    else if (time >= 10) {
        stime = "0" + to_string(time);
    } 
    return stime;
}

class Red {
    public:
    int redtime;
    int health;
    int nWarriors;
    string name[5];
    int wh[5]; // short for warrior health
    int count[5];

    Red(int n) { // constructor
        redtime = 0;
        health = n;
        nWarriors = 0;
        for (int i = 0; i < 5; ++i) {
            count[i] = 0;
        }
        wh[0]=HI; wh[1]=HL; wh[2]=HW; wh[3]=HN; wh[4]=HD;
        name[0] = "iceman"; name[1] = "lion"; name[2] = "wolf"; name[3] = "ninja"; name[4] = "dragon";
    }

    void makeWarriors(int time) {
        string stime = make_time(time);
        int cant = 0;
        for (int i = redtime; ; i++) {
            if (health >= wh[i%5]) {
                health -= wh[i%5];
                count[i%5]++;
                nWarriors++;
                redtime++;
                cout << stime << ' ' << "red" << ' ' << name[i%5] << ' ' << nWarriors << " born with strength " << wh[i%5] <<  "," << count[i%5] << " " << name[i%5] << ' ' << "in red headquarter\n";
                break;
            }
            else {
                cant++;
                redtime++;
            }
            if (cant == 5) {
                cout << stime << ' ' << "red headquarter stops making warriors\n";
                cr = false;
                break;
            }
        }
    }
};

class Blue {
    public:
    int bluetime;
    int health;
    int nWarriors;
    string name[5];
    int wh[5];
    int count[5];

    Blue(int n) {
        bluetime = 0;
        health = n;
        nWarriors = 0;
        for (int i = 0; i < 5; ++i) {
            count[i] = 0;
        }
        wh[0]=HL; wh[1]=HD; wh[2]=HN; wh[3]=HI; wh[4]=HW;
        name[0] = "lion"; name[1] = "dragon"; name[2] = "ninja"; name[3] = "iceman"; name[4] = "wolf";
    }

    void makeWarriors(int time) {
        string stime = make_time(time);
        int cant = 0;
        for (int i = bluetime; ; i++) {
            if (health >= wh[i%5]) {
                health -= wh[i%5];
                count[i%5]++;
                nWarriors++;
                bluetime++;
                cout << stime << ' ' << "blue" << ' ' << name[i%5] << ' ' << nWarriors << " born with strength " << wh[i%5] <<  "," << count[i%5] << " " << name[i%5] << ' ' << "in blue headquarter\n";
                break;
            }
            else {
                cant++;
                bluetime++;
            }
            if (cant == 5) {
                cout << stime << ' ' << "blue headquarter stops making warriors\n";
                cb = false;
                break;
            }
        }
    }
};

class dragon {
    public:
    int health;
};

class ninja {
    public:
    int health;
};

class iceman {
    public:
    int health;
};

class lion {
    public:
    int health;
};

class wolf {
    public:
    int health;
};


int main()
{
    int nCases;
    cin >> nCases;
    int tmp = nCases;
    while (tmp--) {
        cout << "Case:" << nCases - tmp << endl;
        cr = true, cb = true;
        int totalHealth;
        cin >> totalHealth;
        cin >> HD >> HN >> HI >> HL >> HW;
        Red r(totalHealth); Blue b(totalHealth);
        for (int time = 0; ; time++) {
            if (cr) r.makeWarriors(time);
            if (cb) b.makeWarriors(time);
            if (!cr && !cb) break;
        }
    }
	
	return 0;
}