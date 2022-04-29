#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
int t, M, N, K, T;
int HD, HN, HI, HL, HW;
int AD, AN, AI, AL, AW;
string arm_name[3] = {"sword", "bomb", "arrow"};

inline string make_time(int min) {
    string a, b;
    int front = min / 60;
    int behind = min % 60;
    if (behind < 10) {
        b = "0" + to_string(behind);
    }
    else b = to_string(behind);
    if (front < 10) {
        a = "00" + to_string(front);
    }
    else if (front < 100) {
        a = "0" + to_string(front);
    }
    else a = to_string(front);
    return a + ":" + b;
}

//////////////////////////////

class warrior {
public:
    int loyalty;
    int side; // 0 red; N+1 blue
    int loc;
    int health;
    int atk;
    int num;
    string name;
    bool run_away;
    // vector<arm*> arms;
    int arms[3];
    int nArm;
    int unused_arrow;
    string Sside;

public:
    warrior(int h, int a, int n, string s, int Nside) {
        loyalty = 99999999;
        run_away = false;
        health = h;
        atk = a;
        num = n;
        name = s;
        side = Nside;
        loc = Nside;
        unused_arrow = 0;
        nArm = 0;
        arms[0]=arms[1]=arms[2]=0;
        if (Nside == 0) Sside = "red";
        else Sside = "blue";
    }

    void grab(warrior* w, int nTime, int city_idx) {
        int new_0 = min(10-nArm, w->arms[0]);
        arms[0] += new_0;
        nArm += new_0;
        int new_1 = min(10-nArm, w->arms[1]);
        arms[1] += new_1;
        nArm += new_1;
        int unused_new_2 = min(10-nArm, w->unused_arrow);
        arms[2] += unused_new_2;
        nArm += unused_new_2;
        int used_arrow = w->arms[2] - (w->unused_arrow);
        int used_new_2 = min(10-nArm, used_arrow);
        arms[2] += used_new_2;
        nArm += used_new_2;
    }
    void wolf_grab(warrior* w, int nTime, int city_idx) {
        int minite = nTime % 60;
        if (w->name=="wolf" || nArm >= 10) return;
        for (int i = 0; i < 3; ++i) {
            if (w->arms[i] == 0) continue;
            else {
                if (i == 2) {
                    int new_unused_arrow = min(w->unused_arrow, 10-nArm);
                    arms[2] += new_unused_arrow;
                    nArm += new_unused_arrow;
                    unused_arrow += new_unused_arrow;
                    w->unused_arrow -= new_unused_arrow;
                    w->nArm -= new_unused_arrow;
                    w->arms[2] -= new_unused_arrow;

                    int new_used_arrow = min(w->arms[2]-w->unused_arrow, 10-nArm);
                    arms[2] += new_used_arrow;
                    nArm += new_used_arrow;
                    w->nArm -= new_used_arrow;
                    w->arms[2] -= new_used_arrow;

                    if (minite != 40) cout << make_time(nTime) << ' ' << Sside << " wolf " << num << " took " << (new_unused_arrow+new_used_arrow) << " arrow from " << w->Sside << ' ' << w->name << ' ' << w->num << " in city " << city_idx << endl;
                }
                else {
                    int new_arm = min(10-nArm, w->arms[i]);
                    nArm += new_arm;
                    arms[i] += new_arm;
                    w->nArm -= new_arm;
                    w->arms[i] -= new_arm;
                    if (minite != 40) cout << make_time(nTime) << ' ' << Sside << " wolf " << num << " took " << (new_arm) << ' ' << arm_name[i] << " from " << w->Sside << ' ' << w->name << ' ' << w->num << " in city " << city_idx << endl;
                }
                break;
            }
        }
    }

    virtual ~warrior() {}
};

class dragon: public warrior {
public:
    dragon(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {
        int tmp = n%3;
        arms[tmp]++;
        nArm++;
        if (tmp == 2) unused_arrow++;
    }
};

class ninja: public warrior {
public:
    ninja(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {
        int tmp1 = n%3;
        int tmp2 = (n+1)%3;
        arms[tmp1]++;
        arms[tmp2]++;
        nArm += 2;
        if (tmp1 == 2 || tmp2 == 2) unused_arrow++;
    }

};

class iceman: public warrior {
public:
    iceman(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {
        int tmp = n%3;
        arms[tmp]++;
        nArm++;
        if (tmp == 2) unused_arrow++;
    }
};

class lion: public warrior {
public:
    // int loyalty;

    lion(int h, int a, int n, string s, int left_health, int side): warrior(h,a,n,s,side) {
        loyalty = left_health;
        int tmp = n%3;
        arms[tmp]++;
        nArm++;
        if (tmp == 2) unused_arrow++;
        cout << "Its loyalty is " << loyalty << endl;
    }
    // void march(int k) {
    //     loyalty -= k;
    //     if (loyalty <= 0) run_away = true;
    // }
};

class wolf: public warrior {
public:
    wolf(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {

    }
//    void wolf_grab(warrior* w, int nTime, int city_idx) {
//        int minite = nTime % 60;
//        if (w->name=="wolf" || nArm >= 10) return;
//        for (int i = 0; i < 3; ++i) {
//            if (w->arms[i] == 0) continue;
//            else {
//                if (i == 2) {
//                    int new_unused_arrow = min(w->unused_arrow, 10-nArm);
//                    arms[2] += new_unused_arrow;
//                    nArm += new_unused_arrow;
//                    unused_arrow += new_unused_arrow;
//                    w->unused_arrow -= new_unused_arrow;
//                    w->nArm -= new_unused_arrow;
//                    w->arms[2] -= new_unused_arrow;
//
//                    int new_used_arrow = min(w->arms[2]-w->unused_arrow, 10-nArm);
//                    arms[2] += new_used_arrow;
//                    nArm += new_used_arrow;
//                    w->nArm -= new_used_arrow;
//                    w->arms[2] -= new_used_arrow;
//
//                    if (minite != 40) cout << make_time(nTime) << ' ' << Sside << " wolf " << num << " took " << (new_unused_arrow+new_used_arrow) << " arrow from " << w->Sside << ' ' << w->name << ' ' << w->num << " in city " << city_idx << endl;
//                }
//                else {
//                    int new_arm = min(10-nArm, w->arms[i]);
//                    nArm += new_arm;
//                    arms[i] += new_arm;
//                    w->nArm -= new_arm;
//                    w->arms[i] -= new_arm;
//                    if (minite != 40) cout << make_time(nTime) << ' ' << Sside << " wolf " << num << " took " << (new_arm) << ' ' << arm_name[i] << " from " << w->Sside << ' ' << w->name << ' ' << w->num << " in city " << city_idx << endl;
//                }
//                break;
//            }
//        }
//    }
};


//vector<warrior*> red;
//vector<warrior*> blue;

class City {
public:
    int index;
    warrior* rWarrior;
    warrior* bWarrior;

    City() {
        rWarrior = nullptr;
        bWarrior = nullptr;
    }
};


class Red:public City {
public:
    int health;
    int nWarriors;
    string name[5];
    int wh[5]; // short for warrior health

    Red(int n) { // constructor
        health = n;
        nWarriors = 0;
        index = 0;

        wh[0]=HI; wh[1]=HL; wh[2]=HW; wh[3]=HN; wh[4]=HD;
        name[0] = "iceman"; name[1] = "lion"; name[2] = "wolf"; name[3] = "ninja"; name[4] = "dragon";
    }

    void make_warriors(int time) {
        string stime = make_time(time);
        int idx = nWarriors % 5;
        if (health < wh[idx]) return;
        else {
            nWarriors++;
            health -= wh[idx];
        }
        cout << stime << " red " << name[idx] << ' ' << nWarriors << ' ' << "born" << endl;
        switch(idx) {
            case 0: {
                rWarrior = new iceman(HI, AI, nWarriors, "iceman", 0);
                break;
            }
            case 1: {
                rWarrior = new lion(HL, AL, nWarriors, "lion", health, 0);
                break;
            }
            case 2: {
                rWarrior = new wolf(HW, AW, nWarriors, "wolf", 0);
                break;
            }
            case 3: {
                rWarrior = new ninja(HN, AN, nWarriors, "ninja", 0);
                break;
            }
            case 4: {
                rWarrior = new dragon(HD, AD, nWarriors, "dragon", 0);
                break;
            }
        }
    }
};


class Blue:public City {
public:
    int health;
    int nWarriors;
    string name[5];
    int wh[5]; // short for warrior health

    Blue(int n) { // constructor
        health = n;
        nWarriors = 0;
        index = N+1;

        wh[0]=HL; wh[1]=HD; wh[2]=HN; wh[3]=HI; wh[4]=HW;
        name[0] = "lion"; name[1] = "dragon"; name[2] = "ninja"; name[3] = "iceman"; name[4] = "wolf";
    }

    void make_warriors(int time) {
        string stime = make_time(time);
        int idx = nWarriors % 5;
        if (health < wh[idx]) return;
        else {
            nWarriors++;
            health -= wh[idx];
        }

        cout << stime << " blue " << name[idx] << ' ' << nWarriors << ' ' << "born" << endl;
        switch(idx) {
            case 3: {
                bWarrior = new iceman(HI, AI, nWarriors, "iceman", N+1);
                break;
            }
            case 0: {
                bWarrior = new lion(HL, AL, nWarriors, "lion", health, N+1);
                break;
            }
            case 4: {
                bWarrior = new wolf(HW, AW, nWarriors, "wolf", N+1);
                break;
            }
            case 2: {
                bWarrior = new ninja(HN, AN, nWarriors, "ninja", N+1);
                break;
            }
            case 1: {
                bWarrior = new dragon(HD, AD, nWarriors, "dragon", N+1);
                break;
            }
        }
    }
};

vector<City*> cities;

typedef vector<City*>::iterator cit;
void run(int nTime);

void march(int nTime);


void fight(City* c, int nTime);


int main() {
    cin >> t;
    int nCases = t;
    // cout << make_time(t);
    while (t--) {
        cout << "Case " << nCases - t << ':' << endl;
        cin >> M >> N >> K >> T;
        cin >> HD >> HN >> HI >> HL >> HW;
        cin >> AD >> AN >> AI >> AL >> AW;


        int nTime = 0;
        Red r(M);
        Blue b(M);

        cities.push_back(&r);
        for (int i = 1; i <= N; ++i) {
            City* tmp = new City;
            tmp->index = i;
            cities.push_back(tmp);
        }
        cities.push_back(&b);

        for (int nTime = 0; nTime <= T; ++nTime) {
            int min = nTime % 60;
            //
            if (min == 0) {
                r.make_warriors(nTime);
                b.make_warriors(nTime);
            }
            //
            if (min == 5) {
                run(nTime);
            }
            //
            if (min == 10) {
                march(nTime);

                bool flag = false;
                if (r.bWarrior) {
                    cout << make_time(nTime) << " blue " << r.bWarrior->name << " " << r.bWarrior->num << " reached red headquarter with " << r.bWarrior->health << " elements and force " << r.bWarrior->atk << endl;
                    cout << make_time(nTime) << " red headquarter was taken" << endl;
                    flag = true;
                }
                for (int i = 1; i <= N; ++i) {
                    if (cities[i]->rWarrior) {
                        warrior* tmp = cities[i]->rWarrior;
                        cout << make_time(nTime) << " red " << tmp->name << " " << tmp->num << " marched to city " << i << " with " << tmp->health << " elements and force " << tmp->atk << endl;
                    }
                    if (cities[i]->bWarrior) {
                        warrior* tmp = cities[i]->bWarrior;
                        cout << make_time(nTime) << " blue " << tmp->name << " " << tmp->num << " marched to city " << i << " with " << tmp->health << " elements and force " << tmp->atk << endl;
                    }
                }
                if (b.rWarrior) {
                    cout << make_time(nTime) << " red " << b.rWarrior->name << " " << b.rWarrior->num << " reached blue headquarter with " << b.rWarrior->health << " elements and force " << b.rWarrior->atk << endl;
                    cout << make_time(nTime) << " blue headquarter was taken" << endl;
                    flag = true;
                }
                if (flag) break;
            }
            //
            if (min == 35) {
                for (cit i = cities.begin(); i != cities.end(); ++i) {
                    if ((*i)->rWarrior == nullptr || (*i)->bWarrior == nullptr) continue;
                    if ((*i)->rWarrior->name=="wolf") {
                        (*i)->rWarrior->wolf_grab((*i)->bWarrior, nTime, (*i)->index);
                    }
                    if ((*i)->bWarrior->name=="wolf") {
                        (*i)->bWarrior->wolf_grab((*i)->rWarrior, nTime, (*i)->index);
                    }
                }
            }
            if (min == 40) {
                for (cit i = cities.begin(); i != cities.end(); ++i) {
                    fight(*i, nTime);
                }
            }
            if (min == 50) {
                cout << make_time(nTime) << ' ' << r.health << " elements in red headquarter" << endl;
                cout << make_time(nTime) << ' ' << b.health << " elements in blue headquarter" << endl;
            }
            if (min == 55) {
                for (cit i = cities.begin(); i != cities.end(); ++i) {
                    warrior* wr = (*i)->rWarrior;
                    warrior* wb = (*i)->bWarrior;
                    if (wr) cout << make_time(nTime) << " red " << wr->name << ' ' << wr->num << " has " << wr->arms[0] << " sword " << wr->arms[1] << " bomb " << wr->arms[2] << " arrow and " << wr->health << " elements" << endl;
                    if (wb) cout << make_time(nTime) << " blue " << wb->name << ' ' << wb->num << " has " << wb->arms[0] << " sword " << wb->arms[1] << " bomb " << wb->arms[2] << " arrow and " << wb->health << " elements" << endl;
                }
            }
        }
        // delete掉所有指针



        // end
        cities.clear();
    }
}


void run(int nTime) {
    for (cit i = cities.begin(); i != cities.end(); ++i) {
        warrior*& r = (*i)->rWarrior;
        warrior*& b = (*i)->bWarrior;
        if (r && r->name=="lion" && r->loyalty <= 0) {
            cout << make_time(nTime) << " red lion " << r->num << " ran away" << endl;
            r = nullptr;
        }
        if (b && b->name=="lion" && b->loyalty <= 0) {
            cout << make_time(nTime) << " blue lion " << b->num << " ran away" << endl;
            b = nullptr;
        }
    }
}

bool attack(int num, warrior* act, warrior* pas, int atk) {
    if (num == -1) {
        return false;
    }
    int damage;
    if (num == 0) damage = atk * 2 / 10;
    else if (num == 1) damage = atk * 4 / 10;
    else if (num == 2) damage = atk * 3 / 10;

    pas->health -= damage;
    if (num == 1 && act->name != "ninja") {
        int self_damage = damage / 2;
        act->health -= self_damage;
    }
    return true;
}

int getNum(warrior* a, int& i) {
    int* ar = a->arms;
    if (a->nArm == 0) {
        return -1;
    }
    if (i <= ar[0]) {
        return 0;
    }
    else if (i <= ar[0]+ar[1]) {
        ar[1]--;
        a->nArm--;
        i--;
        return 1;
    }
    else if (i <= ar[0]+ar[1]+ar[2]) {
        if (a->unused_arrow > 0) a->unused_arrow--;
        else {
            ar[2]--;
            a->nArm--;
            i--;
        }
        return 2;
    }
    else {
        i = 1;
        return getNum(a, i);
    }
}


void fight(City* c, int nTime) {
    warrior*& r = c->rWarrior;
    warrior*& b = c->bWarrior;

    if (!r || !b) return;

    if (c->index % 2 == 1) {
        int rCount = 1, bCount = 1;
        while (true) {
            bool flag1 = attack(getNum(r, rCount), r, b, r->atk);
            rCount++;
            if (b->health <= 0 && r->health > 0) {
                cout << make_time(nTime) << " " << r->Sside << " " << r->name << ' ' << r->num << " killed " << b->Sside << ' ' << b->name << ' ' << b->num << " in city " << c->index << " remaining " << r->health << " elements" << endl;
                r->grab(b, nTime, c->index);
                if (r->name=="dragon") {
                    cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                }
                b = nullptr;
                break;
            }
            if (r->health <= 0 && b->health <= 0) {
                cout << make_time(nTime) << " both red " << r->name << ' ' << r->num << " and blue " << b->name << ' ' << b->num << " died in city " << c->index << endl;
                b = r = nullptr;
                break;
            }
            bool flag2 = attack(getNum(b, bCount), b, r, b->atk);
            bCount++;
            if (r->health <= 0 && b->health > 0) {
                cout << make_time(nTime) << " " << b->Sside << " " << b->name << ' ' << b->num << " killed " << r->Sside << ' ' << r->name << ' ' << r->num << " in city " << c->index << " remaining " << b->health << " elements" << endl;
                b->grab(r, nTime, c->index);
                if (b->name=="dragon") {
                    cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                }
                r = nullptr;
                break;
            }
            if (r->health <= 0 && b->health <= 0) {
                cout << make_time(nTime) << " both red " << r->name << ' ' << r->num << " and blue " << b->name << ' ' << b->num << " died in city " << c->index << endl;
                b = r = nullptr;
                break;
            }

            if (flag1 == false && flag2 == false) {
                cout << make_time(nTime) << " both red " << r->name << " " << r->num << " and blue " << b->name << " " << b->num << " were alive in city " << c->index << endl;
                if (r->name=="dragon") {
                    cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                }
                if (b->name=="dragon") {
                    cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                }

                break;
            }

            if (r->arms[1]==0 && r->arms[2]==0 && b->arms[1]==0 && b->arms[2]==0 && r->atk * 2 / 10 == 0 && b->atk * 2 / 10 == 0) {
                cout << make_time(nTime) << " both red " << r->name << " " << r->num << " and blue " << b->name << " " << b->num << " were alive in city " << c->index << endl;
                if (r->name=="dragon") {
                    cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                }
                if (b->name=="dragon") {
                    cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                }
                break;
            }
        }
    }
    if (c->index % 2 == 0) {
        int rCount = 1, bCount = 1;
        while (true) {
            bool flag2 = attack(getNum(b, bCount), b, r, b->atk);
            bCount++;
            if (r->health <= 0 && b->health > 0) {
                cout << make_time(nTime) << " " << b->Sside << " " << b->name << ' ' << b->num << " killed " << r->Sside << ' ' << r->name << ' ' << r->num << " in city " << c->index << " remaining " << b->health << " elements" << endl;
                b->grab(r, nTime, c->index);
                if (b->name=="dragon") {
                    cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                }
                r = nullptr;
                break;
            }
            if (r->health <= 0 && b->health <= 0) {
                cout << make_time(nTime) << " both red " << r->name << ' ' << r->num << " and blue " << b->name << ' ' << b->num << " died in city " << c->index << endl;
                b = r = nullptr;
                break;
            }

            bool flag1 = attack(getNum(r, rCount), r, b, r->atk);
            rCount++;
            if (b->health <= 0 && r->health > 0) {
                cout << make_time(nTime) << " " << r->Sside << " " << r->name << ' ' << r->num << " killed " << b->Sside << ' ' << b->name << ' ' << b->num << " in city " << c->index << " remaining " << r->health << " elements" << endl;
                r->grab(b, nTime, c->index);
                if (r->name=="dragon") {
                    cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                }
                b = nullptr;
                break;
            }
            if (r->health <= 0 && b->health <= 0) {
                cout << make_time(nTime) << " both red " << r->name << ' ' << r->num << " and blue " << b->name << ' ' << b->num << " died in city " << c->index << endl;
                b = r = nullptr;
                break;
            }

            if (flag1 == false && flag2 == false) {
                cout << make_time(nTime) << " both red " << r->name << " " << r->num << " and blue " << b->name << " " << b->num << " were alive in city " << c->index << endl;
                if (r->name=="dragon") {
                    cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                }
                if (b->name=="dragon") {
                    cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                }
                break;
            }

            if (r->arms[1]==0 && r->arms[2]==0 && b->arms[1]==0 && b->arms[2]==0 && r->atk * 2 / 10 == 0 && b->atk * 2 / 10 == 0) {
                cout << make_time(nTime) << " both red " << r->name << " " << r->num << " and blue " << b->name << " " << b->num << " were alive in city " << c->index << endl;
                if (r->name=="dragon") {
                    cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                }
                if (b->name=="dragon") {
                    cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                }
                break;
            }
        }
    }
}

void march(int nTime) {
    for (int i = 0; i <= N+1; ++i) {
        warrior*& r = cities[i]->rWarrior;
        warrior*& b = cities[i]->bWarrior;
        if (r && r->name=="lion") {
            r->loyalty -= K;
        }
        if (r && r->name=="iceman") {
            r->health = r->health - r->health / 10;
            if (r->health <= 0) {
                r = nullptr;
            }
        }

        if (b && b->name=="lion") {
            b->loyalty -= K;
        }
        if (b && b->name=="iceman") {
            b->health = b->health - b->health / 10;
            if (b->health <= 0) {
                b = nullptr;
            }
        }
    }





    for (int i = N+1; i > 0; --i) {
        cities[i]->rWarrior = cities[i-1]->rWarrior;
    }
    cities[0]->rWarrior = nullptr;
    for (int i = 0; i <= N; ++i) {
        cities[i]->bWarrior = cities[i+1]->bWarrior;
    }
    cities[N+1]->bWarrior = nullptr;
}


// 尚未完成：
// 1、冰人减血 完成
// 2、占领大本营 完成
// 3、狮子忠诚度下降 完成
// 4、所有攻击模块
// 5、grab函数问题（wolf的特殊性）