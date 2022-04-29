#include <iostream>
#include <string>
using namespace std;
int HD, HN, HI, HL, HW; // dragon, ninja, iceman, lion, wolf
bool cr = true, cb = true; // short for canred, canblue
const char* arm[3] = {"sword", "bomb", "arrow"};

class warrior {
    protected:
    int health;
    string name;
    
    warrior(int wh, string s) {
        health = wh;
        name = s;
    }
};

class dragon: public warrior {
    public:
    int nArm;
    
    double morale;
    dragon(int n, int left, int wh): warrior(wh, "dragon") {
        nArm = n % 3;

        morale = 1.0*left / wh;
        printf("It has a %s,and it's morale is %.2f\n",arm[nArm], morale);
    }
};

class ninja: public warrior {
    public:
    int arm1, arm2;
    ninja(int n, int wh): warrior(wh, "ninja") {
        arm1 = n%3;
        arm2 = (n+1)%3;
        printf("It has a %s and a %s\n", arm[arm1], arm[arm2]);
    }
};

class iceman: public warrior {
    public:
    int nArm;

    iceman(int n, int wh): warrior(wh, "iceman") {
        nArm = n%3;
        printf("It has a %s\n", arm[nArm]);
    }
};

class wolf: public warrior {
    public:
    wolf(int n, int wh): warrior(wh, "wolf") {
        
    }
};

class lion: public warrior {
    public:
    int loyalty;
    lion(int n, int left, int wh): warrior(wh, "lion") {
        loyalty = left;
        printf("It's loyalty is %d\n", loyalty);
    }
};

dragon* d[100]; ninja* n[100]; iceman* ic[100]; lion* l[100]; wolf* w[100]; // start from 1

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
                int idx = i%5;

                health -= wh[i%5];
                count[i%5]++;
                nWarriors++;
                redtime++;
                
                cout << stime << ' ' << "red" << ' ' << name[i%5] << ' ' << nWarriors << " born with strength " << wh[i%5] <<  "," << count[i%5] << " " << name[i%5] << ' ' << "in red headquarter\n";
                switch(idx) {
                    case 0: {
                        iceman tmp = iceman(nWarriors, wh[idx]);
                        break;
                    }
                    case 1: {
                        lion tmp = lion(nWarriors, health, wh[idx]);
                        break;
                    }
                    case 2: {
                        wolf tmp = wolf(nWarriors, wh[idx]);
                        break;
                    }
                    case 3: {
                        ninja tmp = ninja(nWarriors, wh[idx]);
                        break;
                    }
                    case 4: {
                        dragon tmp = dragon(nWarriors, health, wh[idx]);
                        break;
                    }
                }
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
                int idx = i%5;

                health -= wh[i%5];
                count[i%5]++;
                nWarriors++;
                bluetime++;
                
                cout << stime << ' ' << "blue" << ' ' << name[i%5] << ' ' << nWarriors << " born with strength " << wh[i%5] <<  "," << count[i%5] << " " << name[i%5] << ' ' << "in blue headquarter\n";
                switch(idx) {
                    case 3: {
                        iceman tmp = iceman(nWarriors, wh[idx]);
                        break;
                    }
                    case 0: {
                        lion tmp = lion(nWarriors, health, wh[idx]);
                        break;
                    }
                    case 4: {
                        wolf tmp = wolf(nWarriors, wh[idx]);
                        break;
                    }
                    case 2: {
                        ninja tmp = ninja(nWarriors, wh[idx]);
                        break;
                    }
                    case 1: {
                        dragon tmp = dragon(nWarriors, health, wh[idx]);
                        break;
                    }
                }
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