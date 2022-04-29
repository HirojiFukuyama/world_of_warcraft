#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <list>
using namespace std;
int t, M, N, K, T, R;
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

class sword {
public:
    int damage;
    string name = "sword";
    sword(int a) {
        damage = a;
    }
    void blunt_sword() {
        damage = damage * 8 / 10;
    }
};
class arrow {
public:
    int times;
    int damage;
    string name = "arrow";
    arrow(int R) {
        times = 3;
        damage = R;
    }
};
class bomb {
public:
    string name = "bomb";
};

////////////////////////////




class warrior {
public:
    int loyalty;
    int side; // 0 red; N+1 blue
    int loc;
    int health;
    int atk;
    int num;
    string name;
    // vector<arm*> arms;
    sword* ps;
    arrow* pa;
    bomb* pb;
    string Sside;
    double morale;
    int steps;
    bool killEnemy = false;

public:
    warrior(int h, int a, int n, string s, int Nside) {
        loyalty = 99999999;
        health = h;
        atk = a;
        num = n;
        name = s;
        side = Nside;
        loc = Nside;
        ps = nullptr;
        pa = nullptr;
        pb = nullptr;
        if (Nside == 0) Sside = "red";
        else Sside = "blue";
    }

    void wolf_grab(warrior* w, int nTime) {
        if (w->ps && !ps) ps = w->ps;
        if (w->pa && !pa) pa = w->pa;
        if (w->pb && !pb) pb = w->pb;
    }

    virtual ~warrior() {}
};

void make_weapon(warrior* w, int idx) {
    if (idx == 0) {
        int tmp = w->atk * 2 / 10;
        if (tmp > 0) {
            w->ps = new sword(w->atk * 2 / 10);
        }
        else return;
    }
    else if (idx == 2) {
        w->pa = new arrow(R);
    }
    else {
        w->pb = new bomb;
    }
}


class dragon: public warrior {
public:
    dragon(int h, int a, int n, string s, int side, double _morale): warrior(h,a,n,s,side) {
        int tmp = n%3;
        morale = _morale;
        make_weapon(this, tmp);
        cout << "Its morale is ";
        printf("%.2f\n", morale);
    }
};

class ninja: public warrior {
public:
    ninja(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {
        int tmp1 = n%3;
        int tmp2 = (n+1)%3;
        make_weapon(this, tmp1);
        make_weapon(this, tmp2);
    }

};

class iceman: public warrior {
public:
    iceman(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {
        int tmp = n%3;
        make_weapon(this, tmp);
        steps = 0;
    }
};

class lion: public warrior {
public:
    // int loyalty;

    lion(int h, int a, int n, string s, int left_health, int side): warrior(h,a,n,s,side) {
        loyalty = left_health;
        killEnemy = false;
//        int tmp = n%3;
//        make_weapon(this, tmp);
        cout << "Its loyalty is " << loyalty << endl;
    }
};

class wolf: public warrior {
public:
    wolf(int h, int a, int n, string s, int side): warrior(h,a,n,s,side) {

    }
};


//vector<warrior*> red;
//vector<warrior*> blue;

class City {
public:
    int index;
    int health;
    warrior* rWarrior;
    warrior* bWarrior;
    string flag;
    string prev;
    bool newFlag = false;
    int numEnemy = 0;
    warrior* key = nullptr;

    City() {
        health = 0;
        rWarrior = nullptr;
        bWarrior = nullptr;
        flag = "none";
        prev = "none";
    }
};


class Red:public City {
public:
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
                rWarrior = new dragon(HD, AD, nWarriors, "dragon", 0, 1.0*health/wh[idx]);
                break;
            }
        }
    }
};


class Blue:public City {
public:
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
                bWarrior = new dragon(HD, AD, nWarriors, "dragon", N+1, 1.0*health/wh[idx]);
                break;
            }
        }
    }
};

vector<City*> cities;

typedef vector<City*>::iterator cit;
void run(int nTime);

void march(int nTime);
//
//void giveReward(int*, int*);


pair<string,int> fight(City* c, int nTime);

void report_weapon(warrior* w, int nTime);

void killShot(int nTime);

void bombShow(int nTime);

int main() {
    cin >> t;
    int nCases = t;
    // cout << make_time(t);
    while (t--) {
        cout << "Case " << nCases - t << ':' << endl;
        cin >> M >> N >> R >> K >> T;
        cin >> HD >> HN >> HI >> HL >> HW;
        cin >> AD >> AN >> AI >> AL >> AW;

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
                if (r.bWarrior && !r.key && r.numEnemy != 1) {
                    r.numEnemy++;
                    cout << make_time(nTime) << " blue " << r.bWarrior->name << " " << r.bWarrior->num << " reached red headquarter with " << r.bWarrior->health << " elements and force " << r.bWarrior->atk << endl;
                }
                else if (r.bWarrior && r.key) {
                    r.numEnemy++;
                    cout << make_time(nTime) << " blue " << r.key->name << " " << r.key->num << " reached red headquarter with " << r.key->health << " elements and force " << r.key->atk << endl;
                    if (r.numEnemy >= 2) {
                        cout << make_time(nTime) << " red headquarter was taken" << endl;
                        flag = true;
                    }
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
                if (b.rWarrior && !b.key && b.numEnemy != 1) {
                    b.numEnemy++;
                    cout << make_time(nTime) << " red " << b.rWarrior->name << " " << b.rWarrior->num << " reached blue headquarter with " << b.rWarrior->health << " elements and force " << b.rWarrior->atk << endl;
                }
                else if (b.rWarrior && b.key) {
                    b.numEnemy++;
                    cout << make_time(nTime) << " red " << b.key->name << " " << b.key->num << " reached blue headquarter with " << b.key->health << " elements and force " << b.key->atk << endl;
                    if (b.numEnemy >= 2) {
                        cout << make_time(nTime) << " blue headquarter was taken" << endl;
                        flag = true;
                    }
                }
                if (flag) break;
            }
            //

            if (min == 20) {
                for (auto i = cities.begin()+1; i != cities.end()-1; ++i) {
                    (*i)->health += 10;
                }
            }
            if (min == 30) {
                for (auto i = cities.begin()+1; i != cities.end()-1; ++i) {
                    if ((*i)->rWarrior && !(*i)->bWarrior) {
                        r.health += (*i)->health;
                        cout << make_time(nTime) << " red " << (*i)->rWarrior->name << ' ' << (*i)->rWarrior->num << " earned " << (*i)->health << " elements for his headquarter\n";
                        (*i)->health = 0;
                    }
                    else if ((*i)->bWarrior && !(*i)->rWarrior) {
                        b.health += (*i)->health;
                        cout << make_time(nTime) << " blue " << (*i)->bWarrior->name << ' ' << (*i)->bWarrior->num << " earned " << (*i)->health << " elements for his headquarter\n";
                        (*i)->health = 0;
                    }
                }
            }
            if (min == 35) {
                killShot(nTime);
            }
            if (min == 38) {
                bombShow(nTime);
            }
            if (min == 40) {
                int redSum = 0;
                int blueSum = 0;
                pair<string,int> p;
                //按城市输出
                for (cit i = cities.begin(); i != cities.end(); ++i) {
                    p = fight(*i, nTime);
                    if (p.first == "red") {
                        redSum += p.second;
                        cout << make_time(nTime) << " red " << (*i)->rWarrior->name << ' ' << (*i)->rWarrior->num << " earned " << p.second << " elements for his headquarter" << endl;
                    }
                    else if (p.first == "blue") {
                        blueSum += p.second;
                        cout << make_time(nTime) << " blue " << (*i)->bWarrior->name << ' ' << (*i)->bWarrior->num << " earned " << p.second << " elements for his headquarter" << endl;
                    }

                    if ((*i)->newFlag) {
                        cout << make_time(nTime) << ' ' << (*i)->flag << " flag raised in city " << (*i)->index << endl;
                    }
                }
                //奖励
                for (auto i = cities.begin(); i != cities.end(); ++i) {
                    if ((*i)->rWarrior && (*i)->rWarrior->killEnemy) {
                        if (r.health >= 8) {
                            r.health -= 8;
                            (*i)->rWarrior->health += 8;
                        }
                    }
                }
                for (auto i = cities.rbegin(); i != cities.rend(); ++i) {
                    if ((*i)->bWarrior && (*i)->bWarrior->killEnemy) {
                        if (b.health >= 8) {
                            b.health -= 8;
                            (*i)->bWarrior->health += 8;
                        }
                    }
                }
                r.health += redSum;
                b.health += blueSum;
            }
            if (min == 50) {
                cout << make_time(nTime) << ' ' << r.health << " elements in red headquarter" << endl;
                cout << make_time(nTime) << ' ' << b.health << " elements in blue headquarter" << endl;
            }
            if (min == 55) {
                for (auto i = cities.begin(); i != cities.end(); ++i) {
                    report_weapon((*i)->rWarrior, nTime);
                }
                for (auto i = cities.begin(); i != cities.end(); ++i) {
                    report_weapon((*i)->bWarrior, nTime);
                }

//                auto i = cities.begin();
//                report_weapon((*i)->rWarrior, nTime);
//                report_weapon((*i)->bWarrior, nTime);
//                report_weapon((*i)->key, nTime);
//                for (cit i = cities.begin()+1; i != cities.end()-1; ++i) {
//                    warrior* wr = (*i)->rWarrior;
//                    warrior* wb = (*i)->bWarrior;
//                    if (wr) report_weapon(wr, nTime);
//                    if (wb) report_weapon(wb, nTime);
//                }
//                auto j = cities.end()-1;
//                report_weapon((*j)->rWarrior, nTime);
//                report_weapon((*j)->bWarrior, nTime);
//                report_weapon((*j)->key, nTime);
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

pair<string, int> fight(City* c, int nTime) {
    c->newFlag = false;
    pair<string,int> p;
    int sum = 0;
    warrior*& r = c->rWarrior;
    warrior*& b = c->bWarrior;
    string tmpFlag = c->flag;

    //TODO
    if (r && b && r->health <= 0 && b->health <= 0) {
        r = b = nullptr;
        return make_pair("none", 0);
    }
    if (r && r->health <= 0 && !b) {
        r = nullptr;
        return make_pair("none", 0);
    }
    if (b && b->health <= 0 && !r) {
        b = nullptr;
        return make_pair("none", 0);
    }

    if (r) r->killEnemy = false;
    if (b) b->killEnemy = false;

    if (!r || !b) {
        p.first = "none";
        p.second = 0;
        return p;
    }

    bool reallyFight = true;
    if (r->health <= 0 || b->health <= 0) reallyFight = false;

    if (reallyFight) {
        if (c->flag == "red" || (c->flag=="none" && c->index%2==1))  { // red first
            int lionRedTemp = 0;
            int lionBlueTemp = 0;
            if (b->name == "lion") {
                lionBlueTemp = max(0,b->health);
            }
            if (r->name == "lion") {
                lionRedTemp = max(0,r->health);
            }

            b->health -= r->atk;
            if (r->ps) {
                b->health -= r->ps->damage;
                r->ps->blunt_sword();
                if (r->ps->damage <= 0) r->ps = nullptr;
            }

            cout << make_time(nTime) << " red " << r->name << ' ' << r->num << " attacked blue " << b->name << ' ' << b->num << " in city " << c->index << " with " << r->health << " elements and force " << r->atk << endl;

            if (b->health <= 0) {
                if (b->name == "lion") {
                    r->health += lionBlueTemp;
                }
                r->killEnemy = true;
                cout << make_time(nTime) << " blue " << b->name << ' ' << b->num << " was killed in city " << c->index << endl;
                if (r->name == "wolf") {
                    r->wolf_grab(b, nTime);
                }
                b = nullptr;
                p.first = "red", p.second = c->health;
                c->health = 0;
                if (c->prev == "red") {
                    if (c->flag != "red") c->newFlag = true;
                    c->flag = "red";
                }
                c->prev = "red";

                if (r->name == "dragon") {
                    r->morale += 0.2;
                }
            }
            else if (b->health > 0 && b->name != "ninja") {
                if (r->name == "lion") r->loyalty -= K;
                r->killEnemy = false;
                r->health -= b->atk / 2;
                if (b->ps) {
                    r->health -= b->ps->damage;
                    b->ps->blunt_sword();
                    if (b->ps->damage <= 0) b->ps = nullptr;
                }

                cout << make_time(nTime) << " blue " << b->name << ' ' << b->num << " fought back against red " << r->name << ' ' << r->num << " in city " << c->index << endl;

                if (r->health <= 0) {
                    if (r->name == "lion") {
                        b->health += lionRedTemp;
                    }
                    b->killEnemy = true;
                    cout << make_time(nTime) << " red " << r->name << ' ' << r->num << " was killed in city " << c->index << endl;
                    if (b->name == "wolf") {
                        b->wolf_grab(r, nTime);
                    }
                    r = nullptr;
                    p.first = "blue", p.second = c->health;
                    c->health = 0;
                    if (c->prev == "blue") {
                        if (c->flag != "blue") c->newFlag = true;
                        c->flag = "blue";
                    }
                    c->prev = "blue";

                    if (b->name == "dragon") {
                        b->morale += 0.2;
                    }
                }
                else {
                    if (b->name == "lion") b->loyalty -= K;
                    b->killEnemy = false;
                    c->prev = "none";
                }
            }
            else {
                if (r->name == "lion") r->loyalty -= K;
                r->killEnemy = false;
                b->killEnemy = false;
                c->prev = "none";
            }
        }

        else if (c->flag == "blue" || (c->flag=="none" && c->index%2==0))  { // blue first
            int lionRedTemp = 0;
            int lionBlueTemp = 0;
            if (b->name == "lion") {
                lionBlueTemp = b->health;
            }
            if (r->name == "lion") {
                lionRedTemp = r->health;
            }

            r->health -= b->atk;
            if (b->ps) {
                r->health -= b->ps->damage;
                b->ps->blunt_sword();
                if (b->ps->damage <= 0) b->ps = nullptr;
            }

            cout << make_time(nTime) << " blue " << b->name << ' ' << b->num << " attacked red " << r->name << ' ' << r->num << " in city " << c->index << " with " << b->health << " elements and force " << b->atk << endl;

            if (r->health <= 0) {
                if (r->name == "lion") {
                    b->health += lionRedTemp;
                }
                b->killEnemy = true;
                cout << make_time(nTime) << " red " << r->name << ' ' << r->num << " was killed in city " << c->index << endl;
                if (b->name == "wolf") {
                    b->wolf_grab(r, nTime);
                }
                r = nullptr;
                p.first = "blue", p.second = c->health;
                c->health = 0;
                if (c->prev == "blue") {
                    if (c->flag != "blue") c->newFlag = true;
                    c->flag = "blue";
                }
                c->prev = "blue";

                if (b->name == "dragon") {
                    b->morale += 0.2;
                }
            }
            else if (r->health > 0 && r->name != "ninja") {
                if (b->name == "lion") b->loyalty -= K;
                b->killEnemy = false;
                b->health -= r->atk / 2;
                if (r->ps) {
                    b->health -= r->ps->damage;
                    r->ps->blunt_sword();
                    if (r->ps->damage <= 0) r->ps = nullptr;
                }

                cout << make_time(nTime) << " red " << r->name << ' ' << r->num << " fought back against blue " << b->name << ' ' << b->num << " in city " << c->index << endl;
                if (b->health <= 0) {
                    if (b->name == "lion") {
                        r->health += lionBlueTemp;
                    }
                    r->killEnemy = true;
                    cout << make_time(nTime) << " blue " << b->name << ' ' << b->num << " was killed in city " << c->index << endl;
                    if (r->name == "wolf") {
                        r->wolf_grab(b, nTime);
                    }
                    b = nullptr;
                    p.first = "red", p.second = c->health;
                    c->health = 0;
                    if (c->prev == "red") {
                        if (c->flag != "red") c->newFlag = true;
                        c->flag = "red";
                    }
                    c->prev = "red";

                    if (r->name == "dragon") {
                        r->morale += 0.2;
                    }
                }
                else {
                    if (r->name == "lion") r->loyalty -= K;
                    r->killEnemy = false;
                    c->prev = "none";
                }
            }
            else {
                if (b->name == "lion") b->loyalty -= K;
                r->killEnemy = false;
                b->killEnemy = false;
                c->prev = "none";
            }
        }

        if (r && r->name == "dragon" && !r->killEnemy) r->morale -= 0.2;
        if (b && b->name == "dragon" && !b->killEnemy) b->morale -= 0.2;

        if (r && r->name == "dragon" && r->morale > 0.8 && (tmpFlag == "red" || (tmpFlag=="none" && c->index%2==1))) {
            cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
        }
        if (b && b->name == "dragon" && b->morale > 0.8 && (tmpFlag == "blue" || (tmpFlag=="none" && c->index%2==0))) {
            cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
        }
    }
    //没有真打起来
    else {
        if (r->health <= 0) {
            //TODO
            b->killEnemy = true;
            if (b->name == "wolf") {
                b->wolf_grab(r, nTime);
            }
            r = nullptr;
            p.first = "blue", p.second = c->health;
            c->health = 0;
            if (c->prev == "blue") {
                if (c->flag != "blue") c->newFlag = true;
                c->flag = "blue";
            }
            c->prev = "blue";
            if (b->name == "dragon") {
                b->morale += 0.2;
                if (c->flag == "blue" || (c->flag=="none" && c->index%2==0)) {
                    if (b->morale > 0.8 && (tmpFlag == "blue" || (tmpFlag=="none" && c->index%2==0))) {
                        cout << make_time(nTime) << " blue dragon " << b->num << " yelled in city " << c->index << endl;
                    }
                }
            }
        }

        if (b->health <= 0) {
            //TODO
            r->killEnemy = true;
            if (r->name == "wolf") {
                r->wolf_grab(b, nTime);
            }
            b = nullptr;
            p.first = "red", p.second = c->health;
            c->health = 0;
            if (c->prev == "red") {
                if (c->flag != "red") c->newFlag = true;
                c->flag = "red";
            }
            c->prev = "red";
            if (r->name == "dragon") {
                r->morale += 0.2;
                if (c->flag == "red" || (c->flag=="none" && c->index%2==1)) {
                    if (r->morale > 0.8 && (tmpFlag == "red" || (tmpFlag=="none" && c->index%2==1))) {
                        cout << make_time(nTime) << " red dragon " << r->num << " yelled in city " << c->index << endl;
                    }
                }
            }
        }
    }

    return p;
}

void march(int nTime) {
    for (int i = 0; i <= N+1; ++i) {
        warrior*& r = cities[i]->rWarrior;
        warrior*& b = cities[i]->bWarrior;

//        if (r && r->name=="lion" && !r->killEnemy && i != 0 && i != N+1) {
//            r->loyalty -= K;
//        }
//        if (b && b->name=="lion" && !b->killEnemy && i != 0 && i != N+1) {
//            b->loyalty -= K;
//        }

        if (r && r->name=="iceman") {
            if (r->steps % 2 == 1) {
                r->steps++;
                r->atk += 20;
                if (r->health > 9) r->health -= 9;
                else r->health = 1;
            }
            else {
                r->steps++;
            }
        }
        if (b && b->name=="iceman") {
            if (b->steps % 2 == 1) {
                b->steps++;
                b->atk += 20;
                if (b->health > 9) b->health -= 9;
                else b->health = 1;
            }
            else {
                b->steps++;
            }
        }
    }

    if (cities[N+1]->rWarrior) {
        cities[N+1]->key = cities[N]->rWarrior;
    }
    else {
        cities[N+1]->rWarrior = cities[N]->rWarrior;
    }
    for (int i = N; i > 0; --i) {
        cities[i]->rWarrior = cities[i-1]->rWarrior;
    }
    cities[0]->rWarrior = nullptr;

    if (cities[0]->bWarrior) {
        cities[0]->key = cities[1]->bWarrior;
    }
    else {
        cities[0]->bWarrior = cities[1]->bWarrior;
    }
    for (int i = 1; i <= N; ++i) {
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

void report_weapon(warrior* w, int nTime) {
    if (!w) return;
    cout << make_time(nTime) << ' ' << w->Sside << ' ' << w->name << ' ' << w->num << " has ";
    if (w->pa) cout << "arrow(" << w->pa->times << ")";
    if (w->pb) {
        if (w->pa) cout << ',';
        cout << "bomb";
    }
    if (w->ps) {
        if (w->pa || w->pb) cout << ',';
        cout << "sword(" << w->ps->damage << ')';
    }
    if (!w->pa && !w->pb && !w->ps) {
        cout << "no weapon";
    }
    cout << endl;
}

void killShot(int nTime) {
    for (int i = 0; i <= N+1; ++i) {
        //red shot blue
        if (i < N && cities[i]->rWarrior && cities[i+1]->bWarrior && cities[i]->rWarrior->pa) {
            cities[i]->rWarrior->pa->times--;
            if (cities[i]->rWarrior->pa->times <= 0) cities[i]->rWarrior->pa = nullptr;
            cities[i+1]->bWarrior->health -= R;
            cout << make_time(nTime) << " red " << cities[i]->rWarrior->name << ' ' << cities[i]->rWarrior->num << " shot";
            if (cities[i+1]->bWarrior->health <= 0) {
                cout << " and killed " << "blue " << cities[i+1]->bWarrior->name << ' ' << cities[i+1]->bWarrior->num;
            }
            cout << endl;
        }
        //blue shot red
        if (i > 1 && cities[i]->bWarrior && cities[i-1]->rWarrior && cities[i]->bWarrior->pa) { // may cause segmentation fault
            cities[i]->bWarrior->pa->times--;
            if (cities[i]->bWarrior->pa->times <= 0) cities[i]->bWarrior->pa = nullptr;
            cities[i-1]->rWarrior->health -= R;
            cout << make_time(nTime) << " blue " << cities[i]->bWarrior->name << ' ' << cities[i]->bWarrior->num << " shot";
            if (cities[i-1]->rWarrior->health <= 0) {
                cout << " and killed " << "red " << cities[i-1]->rWarrior->name << ' ' << cities[i-1]->rWarrior->num;
            }
            cout << endl;
        }
    }
}

void bombShow(int nTime) {
    for (int i = 1; i <= N; ++i) {
        warrior*& wr = cities[i]->rWarrior;
        warrior*& wb = cities[i]->bWarrior;

        if (!wr || !wb) continue;

        if (wr->health <= 0 || wb->health <= 0) continue;

        if (cities[i]->flag == "red" || (cities[i]->flag == "none" && cities[i]->index%2==1)) {
            int redDamage = wr->atk;
            if (wr->ps) redDamage += wr->ps->damage;
            int blueDamage = wb->atk / 2;
            if (wb->ps) blueDamage += wb->ps->damage;

            if (wb->health <= redDamage && wb->pb) {
                cout << make_time(nTime) << " blue " << wb->name << ' ' << wb->num << " used a bomb and killed red " << wr->name << ' ' << wr->num << endl;
                wr = nullptr;
                wb = nullptr;
                continue;
            }
            if (wr->health <= blueDamage && wr->pb && wb->health > redDamage) {
                if (wb->name == "ninja") continue;
                cout << make_time(nTime) << " red " << wr->name << ' ' << wr->num << " used a bomb and killed blue " << wb->name << ' ' << wb->num << endl;
                wr = nullptr;
                wb = nullptr;
                continue;
            }
        }

        else if (cities[i]->flag == "blue" || (cities[i]->flag == "none" && cities[i]->index%2==0)) {
            int redDamage = wr->atk / 2;
            if (wr->ps) redDamage += wr->ps->damage;
            int blueDamage = wb->atk;
            if (wb->ps) blueDamage += wb->ps->damage;

            if (wr->health <= blueDamage && wr->pb) {
                cout << make_time(nTime) << " red " << wr->name << ' ' << wr->num << " used a bomb and killed blue " << wb->name << ' ' << wb->num << endl;
                wr = nullptr;
                wb = nullptr;
                continue;
            }
            if (wb->health <= redDamage && wb->pb && wr->health > blueDamage) {
                if (wr->name == "ninja") continue;
                cout << make_time(nTime) << " blue " << wb->name << ' ' << wb->num << " used a bomb and killed red " << wr->name << ' ' << wr->num << endl;
                wr = nullptr;
                wb = nullptr;
                continue;
            }
        }
    }
}