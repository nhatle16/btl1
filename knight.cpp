#include "knight.h"

// check stats event 1 -> 5
void check_HP_Level_1To5(int & HP, int & phoenixdown, int & level, int level0, float & damage, int maxHP, int & rescue){
   
    if (level > level0 ){ // level + 1 if win but not greater than 10
       level += 1; 
       if (level > 10)      level = 10;
       rescue = -1;
    }
    else if (level == level0){ // due 
        rescue = -1; // continue
    }
    else if (level < level0){ 
        HP = HP - damage;
        if (HP > 0){ // HP still > 0 then continue adventure
            rescue = -1;
        }
        else if (HP <= 0 && phoenixdown >= 1){       // HP < 0 + has phoenixdown then return to maxHP and continue
            phoenixdown--;
            HP = maxHP;
            rescue = -1;
        }
        else if (HP <= 0 && phoenixdown == 0){       // HP < 0 + no phoenixdown then cannot rescue
            rescue = 0;
        }
    }
}

// check stats event 6: meet Shaman
void check_HP_Level_6(int & HP, int & remedy, int & level, int level0, int & rescue, int & tinystate){
    if (level > level0){      // level + 2 if win but not greater than 10
        level += 2;
        if (level > 10)    level = 10;
        rescue = -1;
    }
    else if(level == level0){   // due
        rescue = -1;
    }
    else if (level < level0 && remedy == 0){    // if lost and has no remedy
        tinystate = 1;
        if (HP < 5){    // if HP < 5, not divide 5 but set to 1
            HP = 1;
        }
        else
        HP = HP / 5;     // divide 5
    }
    else if (level < level0 && remedy >= 1){    // if lost but has remedy => HP not change
        HP = HP;
        remedy--;
    }
}

// check stats event 7: meet Siren Vajsh
void check_HP_Level_7(int & HP, int & maidenkiss, int & level, int level0, int & rescue, int & frogstate){
    if (level > level0){
        level += 2;
        if (level > 10)     level = 10;
        rescue = -1;
    }
    else if (level == level0){
        rescue = -1;
    }
    else if (level < level0 && maidenkiss == 0){ // if lost and has no maidenkiss => set level = 1
        frogstate = 1;
        level = 1;
    }
    else if (level < level0 && maidenkiss >= 1){ // if lost and has maidenkiss => level not change;
        level = level;
        maidenkiss--;
    }
}

// check stats event 12: when meet mushFibo, return HP to the nearest Fibo number
int mushFibo(int n){
    int num1 = 0, num2 = 1;
    int num = 0;
    while(num < n)
    {
        num  = num1 + num2;
        num1 = num2;
        num2 = num;
    }
    return num1;
}

// check prime number
bool isPrime(int n){
    if (n < 2){
        return false;
    }
    for (int i = 2; i < n; i++){
        if (n % i == 0){
            return false;
        }        
    }
    return true;
}

// check stats 11: increase HP to nearest prime
int nearestPrime(int n){
    if (n <= 1){
        return 2;
    }
    int num = n + 1;

    if (isPrime(num) == true){ 
        return num;
    }
    while (!isPrime(num)){
        num++;
    }
    return num;
}

void display(int HP, int level, int remedy, int maidenkiss, int phoenixdown, int rescue) {
    cout << "HP=" << HP
        << ", level=" << level
        << ", remedy=" << remedy
        << ", maidenkiss=" << maidenkiss
        << ", phoenixdown=" << phoenixdown
        << ", rescue=" << rescue << endl;
}

void adventureToKoopa(string file_input, int & HP, int & level, int & remedy, int & maidenkiss, int & phoenixdown, int & rescue) {
    
    ifstream infile;
    infile.open(file_input);
    int event[1000];
    int count = 1;
    string line1, line2, line3;
    getline (infile, line1);
    stringstream stats(line1);

    stats >> HP; 
    stats >> level;

    stats >> remedy;
    stats >> maidenkiss;
    stats >> phoenixdown;
    rescue = -1;
    
    int maxHP = HP;
    int isArthur, isLancelot;
    int initialPhoenixdown = 0;
    int tinystate = 0, frogstate = 0;
    int initialLevel = 0;

    int flag6 = 0, flag7 = 0;

    // variable use in case 11
    int n1, s1, termiNum, i_e11;

    // variable use in mush_ghost    
    int mtx, mti, maxi, mini, maxi2, mini2;
    int max_4, max_4index, max2_3x, max2_3i;
    int max_1, min_1, max_2, max_3, min_3;
    int v;
    int u = 0;
    int i1 = 0, i2 = 0, i3 = 0, i4 = 0; // index used in loop of case 1 2 3 4 respectively

    
    // variable use in asclepius - case 19
    int k = 0;
    int num[100][100] = {0};   

    // variable use in merlin - case 18
    int a = 0;

    if (maxHP == 999)    isArthur = 1;
    else if (isPrime(maxHP) == true)   isLancelot = 1;
    
    // string & stringstream used for event 18 19 
    string merlin_pack, asclepius_pack, line;
    string merlin_1, asclepius_1, asclepius_2;
    string character;
    
    stringstream ss_merlin, ss_ascle1, ss_ascle2, ss_line;
    
    ifstream asclepius; 
    ifstream merlin;
    ifstream inputfile18, inputfile19;

    int metAsclepius, metMerlin;    // state when meet Asclepius and Merlin

    getline(infile, line2);
    stringstream ssline2(line2);
    
    string event_string;
    while (getline(ssline2, event_string,' ')){
        event[count] = stoi(event_string);
        count++;
        event_string = "";
    }  

    getline(infile, line3,',');   // read line3 until meet comma

    ifstream mush_ghost;
    mush_ghost.open(line3);     // mush_ghost takes information from line3 - which is <file_mush_ghost>
    string mush_line1, mush_line2;
    getline(mush_ghost, mush_line1);
    getline(mush_ghost, mush_line2);
    stringstream ss_mush1(mush_line1); // read value from line1 and store it in n2
    int n2, n9;
    ss_mush1 >> n2;

    stringstream ss_mush2(mush_line2); // ss to read mush_line2 and store them in arrays

    int old_i = 0;
    int i = 0;
    char comma, comma1;
    int value3[1000], old_value[1000], value4[1000];
    
    while (ss_mush2 >> old_value[old_i]){  // ss
        old_i++;
        ss_mush2 >> comma1;
    }
    
    // for (int i = 0; i < old_i; i++){
    //     cout << old_value[i] << " ";
    // }

    if (event[1] == 0){
        rescue = 1;
        display(HP, level, remedy, maidenkiss, phoenixdown, rescue); 
        return;
    }
    for (i = 1; i < count; i++)
    {   
        int b = i % 10;
        int level0 = i > 6?(b > 5?b : 5) : b; //    if i <= 6 then level0 = b; else (if b <= 5, then b = 5 else b = b)
        float damage;
        float dame_MadBear = 1, dame_Bandit = 1.5, dame_Lupin = 4.5, dame_Elf = 7.5, dame_Troll = 9.5;        
                                   

        switch(event[i]){

            case  0:    rescue = 1;
                        if (isArthur == 1 || isLancelot == 1){
                            rescue = 1;                          
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);     
                        break;

            case  1:   damage = dame_MadBear * level0 * 10;
                        
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 1;
                            rescue = -1;
                            if (level > 10)     level = 10;
                            
                        }
                        else{ 
                            check_HP_Level_1To5(HP, phoenixdown, level, level0, damage, maxHP, rescue);
                            if (event[i + 1] == 7){
                                initialLevel = level; //   set a variable as the level before this stage
                                
                            }
                                                        
                            if (i >= 4  && event[i - 3] == 6 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    HP = HP * 5;
                                    if (HP > maxHP)    HP = maxHP;   
                                }
                                else {
                                    initialPhoenixdown--;
                                }                                                    
                            }
                            else if (i >= 4 && event[i - 3] == 7 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    level = initialLevel;    
                                }
                                else{
                                    initialPhoenixdown--;
                                }
                            }
                            
                        }  
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);                      
                        break;
                        
            case  2:  damage = dame_Bandit * level0 * 10;
                        
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 1;
                            rescue = -1;
                            if (level > 10)     level = 10;    
                        }
                        else {
                            check_HP_Level_1To5(HP, phoenixdown, level, level0, damage, maxHP, rescue);
                            if (event[i + 1] == 7){
                                initialLevel = level; //   set a variable as the level before this stage
                            } 
                                // cout << level << " " << initialLevel << endl;
                                                
                            if (i >= 4 && event[i - 3] == 6 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    HP = HP * 5;
                                    if (HP > maxHP)    HP = maxHP; 
                                }
                                else {
                                    initialPhoenixdown--;
                                }                                                    
                            }
                            else if (i >= 4 && event[i - 3] == 7 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    level = initialLevel;
                                }
                                else{
                                    initialPhoenixdown--;
                                }
                            }
                        } 
                        if (i == count - 1 && HP > 0)  rescue = 1;
                        if (i == count - 1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);                                              
                        break;
                    
            case  3:    damage = dame_Lupin * level0 * 10;
                        
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 1;
                            rescue = -1;
                            if (level > 10)     level = 10;
                        }
                        else 
                        {  
                            check_HP_Level_1To5(HP, phoenixdown, level, level0, damage, maxHP, rescue);
                            if (event[i + 1] == 7){
                                initialLevel = level; //   set a variable as the level before this stage
                            } 
                                                    
                            if (i >= 4  && event[i - 3] == 6 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    HP = HP * 5;
                                    if (HP > maxHP)    HP = maxHP;
                                }
                                else {
                                    initialPhoenixdown--;
                                }                                                    
                            }
                            else if (i >= 4 && event[i - 3] == 7 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    level = initialLevel;
                                }
                                else{
                                    initialPhoenixdown--;
                                }
                            }
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);                        
                        break;
                        
            case  4:    damage = dame_Elf * level0 * 10;
                        
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 1;
                            rescue = -1;
                            if (level > 10)     level = 10;
                        }
                        else{
                            check_HP_Level_1To5(HP, phoenixdown, level, level0, damage, maxHP, rescue); 
                            if (event[i + 1] == 7){
                                initialLevel = level; //   set a variable as the level before this stage
                            }                        
                            
                            if (i >= 4  && event[i - 3] == 6 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    HP = HP * 5;
                                    if (HP > maxHP)    HP = maxHP;
                                }
                                else {
                                    initialPhoenixdown--;
                                }                                                    
                            }
                            else if (i >= 4 && event[i - 3] == 7 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    level = initialLevel;
                                }
                                else{
                                    initialPhoenixdown--;
                                }
                            }                       
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0; 
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);                       
                        break;
                        
            case  5:    damage = dame_Troll * level0 * 10;
                        
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 1;
                            rescue = -1;
                            if (level > 10)     level = 10;
                        }
                        else{
                            
                            check_HP_Level_1To5(HP, phoenixdown, level, level0, damage, maxHP, rescue);  
                            if (event[i + 1] == 7){
                                initialLevel = level; //   set a variable as the level before this stage
                            }
                            
                            if (i >= 4 && event[i - 3] == 6 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    HP = HP * 5;
                                    if (HP > maxHP)    HP = maxHP;
                                }
                                else {
                                initialPhoenixdown--;
                                }                                                    
                            }
                            else if (i >= 4 && event[i - 3] == 7 && HP > 0 && level < level0){
                                if (phoenixdown == initialPhoenixdown){
                                    level = initialLevel;
                                }
                                else{
                                    initialPhoenixdown--;
                                }
                            }
                        } 
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;  
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);                     
                        break;
                        
            case  6:    initialPhoenixdown = phoenixdown;
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 2;
                            rescue = -1;
                            if (level > 10)     level = 10;
                        }
                        else{
                            if (event[i-1] == 7 || event[i-2] == 7 || event[i-3] == 7 || event[i-1] == 6 || event[i-2] == 6 || event[i-3] == 6){
                                flag6 = 1;                                    
                                if (level > level0){
                                    check_HP_Level_6(HP, remedy, level, level0, rescue, tinystate);
                                }
                                if (event[i-3] == 6 && (level < level0)){
                                    //check_HP_Level_6(HP, remedy, level, level0, rescue, tinystate);
                                    HP = HP * 5;
                                    if (HP > maxHP)     HP = maxHP;
                                }
                                // cout << remedy << endl;
                                // if (remedy == 0)
                                // {
                                //     display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                                //     break;  
                                // }
                            }
                            if (flag6 == 0)   check_HP_Level_6(HP, remedy, level, level0, rescue, tinystate);
                        }
                        //if (flag6 == 0)   check_HP_Level_6(HP, remedy, level, level0, rescue, tinystate);
                            //cout << remedy << endl;

                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;
           
            case  7:    initialPhoenixdown = phoenixdown;
                        initialLevel = level;
                        if (isArthur == 1 || isLancelot == 1){
                            level = level + 2;
                            rescue = -1;
                            if (level > 10)     level = 10;
                        }
                        else{
                            if (event[i-1] == 7 || event[i-2] == 7 || event[i-3] == 7 || event[i-1] == 6 || event[i-2] == 6 || event[i-3] == 6){
                                flag7 = 1;
                                if (level > level0){
                                    level += 2;
                                    if (level > 10)   level = 10;   
                                }                          

                            } 
                            if (flag7 == 0)     check_HP_Level_7(HP, maidenkiss, level, level0, rescue, frogstate); 
                        }  
                        if (level < level0 && maidenkiss >= 1){ // if lost and has maidenkiss => level not change;
                            level = level;
                            maidenkiss--;
                        } 
                        //cout << level << "\t" << maidenkiss << endl;

                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;

            case 11:    n1 = ((level + phoenixdown) % 5 + 1) * 3;
                        s1 = 0;
                        i_e11 = 0;
                        termiNum = 99;
                        
                        while (i_e11 < n1){
                            s1 = s1 + termiNum;
                            termiNum = termiNum - 2;
                            i_e11++;
                            if (termiNum < 11)      break;
                        }

                        HP = HP + (s1 % 100);
                        //cout << HP << endl;
                        HP = nearestPrime(HP);
                        //cout << HP << endl;
                        if (HP > maxHP){
                            HP = maxHP;
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;         

            case  12:   if (HP > 1){
                            int temp1 = mushFibo(HP);
                            HP = temp1;
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;                        

            case  15:   if (remedy >= 0 && remedy < 99){
                            remedy = remedy + 1;
                            if (tinystate == 1){
                                tinystate = 0;
                                remedy = remedy - 1;
                                HP = HP * 5;
                            }
                        }                        
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;

            case 16:    if (maidenkiss >= 0 && maidenkiss < 99){
                            maidenkiss = maidenkiss + 1;
                            if (frogstate == 1){
                                frogstate = 0;
                                maidenkiss = maidenkiss - 1;
                                level = initialLevel;
                            }
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;

            case 17:    if (phoenixdown >= 0 && phoenixdown < 99){
                            phoenixdown = phoenixdown + 1;
                        }
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;

            case 18:    if (metMerlin == 1){
                            if (i == count-1 && HP > 0)  rescue = 1;
                            if (i == count-1 && HP < 0)  rescue = 0;
                            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                            break;
                        }   
                        infile.clear();
                        
                        inputfile18.open(file_input);
                        getline (inputfile18, line1);
                        getline (inputfile18, line2);
                        getline (inputfile18, line3, ',');
                        getline (inputfile18, line3, ',');
                        getline (inputfile18, merlin_pack);  
                        //cout << merlin_pack << endl;                      

                        merlin.open(merlin_pack);
                        getline (merlin, merlin_1); 
                        ss_merlin.str(merlin_1);

                        ss_merlin >> n9;                        
                        for (int a = 0; a < n9; a++){
                            getline (merlin, character);
                            int total[6] = {0};
                            for (int j18 = 0; j18 < character.length(); j18++){
                                
                                if (character.substr(j18, 6) == "Merlin" || character.substr(j18, 6) == "merlin"){
                                    HP = HP + 3;
                                    if (HP > maxHP)  HP = maxHP;
                                    break;
                                }
                                if (character[j18] == 'm' || character[j18] == 'M'){
                                    total[0] = 1;
                                }
                                else if (character[j18] == 'e' || character[j18] == 'E'){
                                    total[1] = 1;
                                }
                                else if (character[j18] == 'r' || character[j18] == 'R'){
                                    total[2] = 1;
                                }
                                else if (character[j18] == 'l' || character[j18] == 'L'){
                                    total[3] = 1;
                                }
                                else if (character[j18] == 'i' || character[j18] == 'I'){
                                    total[4] = 1;
                                }
                                else if (character[j18] == 'n' || character[j18] == 'N'){
                                    total[5] = 1;
                                }                                
                            }

                            int sum_of_count = 0;
                            for (int k18 = 0; k18 < 6; k18++){
                                sum_of_count += total[k18];
                            }
                        
                            if (sum_of_count == 6){
                                HP = HP + 2;
                                if (HP > maxHP)     HP = maxHP;
                            }
                        }
                        metMerlin = 1;
                        if (HP > maxHP)    HP = maxHP;
                        if (i == count-1 && HP > 0)  rescue = 1;
                        if (i == count-1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;                    
     
            case 19:    
                        if (metAsclepius == 1){
                            if (i == count-1 && HP > 0)  rescue = 1;
                            if (i == count-1 && HP < 0)  rescue = 0;
                            display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                            break;
                        }   
                        infile.clear();
                        
                        inputfile19.open(file_input);
                        getline (inputfile19, line1);
                        getline (inputfile19, line2);
                        getline (inputfile19, line3, ',');
                        getline (inputfile19, asclepius_pack, ','); //   save the 2nd file in line as asclepius_pack
                        asclepius.open(asclepius_pack);  // asclepius takes information from line3
                       
                        getline(asclepius, asclepius_1);    // in4 in the 1st line is stored in asclepius_1
                        getline(asclepius, asclepius_2);    // in4 in the 2nd line is stored in asclepius_2
                        //cout << asclepius_pack;
                        int r1;
                        ss_ascle1.str(asclepius_1);    
                        ss_ascle1 >> r1;    //  turn element in asclepius_1 into int type and stored in r1;

                        ss_ascle2.str(asclepius_2);
                        int c1; 
                        ss_ascle2 >> c1;    // turn element in asclepius_2 into int type and stored in c1; 
                        //cout << r1 << " " << c1 << endl;                   
                        for (int k1 = 0; k1 < r1; k1++){
                            for (int j = 0; j < c1; j++){    
                                asclepius >> num[k1][j]; 
                                //cout << num[k1][j] << " "; 
                            }   
                             
                        }

                        for (int k1 = 0; k1 < r1; k1++){
                            int turn = 0;
                            for (int j = 0; j < c1; j++){
                                if (num[k1][j] == 16){
                                    remedy++;
                                    
                                    turn++;
                                    if(remedy > 99)     remedy = 99; 
                                }
                                else if (num[k1][j] == 17){
                                    maidenkiss++;
                                    turn++;
                                    if (maidenkiss > 99)    maidenkiss = 99;
                                }    
                                else if (num[k1][j] == 18){
                                    phoenixdown++;
                                    turn++;
                                    if (phoenixdown > 99)   phoenixdown = 99;
                                }
                                if (turn == 3)    break;
                            }
                            // cout << remedy << endl;
                        }
                        metAsclepius = 1;
                        if (i == count - 1 && HP > 0)  rescue = 1;
                        if (i == count - 1 && HP < 0)  rescue = 0;
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);

                        break;

            case 99:    if (isArthur == 1 || (isLancelot == 1 && level >= 8) || ((HP > 0) && (level = 10))){
                            level = 10;
                            rescue = 1;
                        }
                        else    rescue = 0;
                        
                        display(HP, level, remedy, maidenkiss, phoenixdown, rescue);
                        break;
            default:    break;
        }

           
        
        string event_str = to_string(event[i]);  // declare event_str as string type of event[i]
        if (event_str.substr(0,2) == "13"){     // determine whether first 2 character is "13"
            string event_13 = event_str.substr(2);     // declare sub_event as a substring of event_str starting from 2nd position
            int mush_arr[1000];
            //cout << event_13.size() << endl;
            while(u < event_13.size()){  // determine whether the character at ith position is not null
                string mush_type = event_13.substr(u, 1);  // declare mush_type as the ith character
                mush_arr[u] = stoi(mush_type);   // declare mush_arr as int type of mush_type 
                u++; // u is index
            }
                           
            
            for (v = 0; v < u; v++){
                //cout << old_value[0] << endl;  
            switch(mush_arr[v]){
                case   1:   max_1 = old_value[0], maxi = 0;
                            for (i1 = 1; i1 < n2; i1++){
                                if (old_value[i1] >= max_1){
                                   max_1 = old_value[i1];
                                   maxi = i1;
                                }
                            }
                            min_1 = max_1, mini = 0;
                            for (int j = 0; j < n2; j++){
                                if (old_value[j] <= min_1){
                                    min_1 = old_value[j];
                                    mini = j;
                                }   
                            }
                            HP = HP - (maxi + mini);
                            if (HP < 0 && phoenixdown >= 1){
                                HP = maxHP;
                                phoenixdown--;
                            }
                            break;

                case  2:    max_2 = old_value[0], mtx = old_value[0], mti = 0;
                            for (i2 = 1; i2 < n2; i2++){
                                if (old_value[i2] > max_2){
                                    max_2 = old_value[i2];
                                    mtx = max_2;
                                    mti = i2;
                                }
                            }
                            for (int j = 0; j < mti; j++){
                                if (old_value[j] >= old_value[j + 1]){
                                    mtx = -2;
                                    mti = -3;
                                }                                
                            }                 
                            for (int j = mti + 1; j < n2; j++){
                                if (old_value[j] <= old_value[j + 1]){
                                    mtx = -2;
                                    mti = -3;
                                }
                            }
                           // cout << mtx << "\t" << mti << endl;

                            HP = HP - (mtx + mti);
                            
                            if (HP < 0 && phoenixdown >= 1){
                                HP = maxHP;
                                phoenixdown--;
                            }                            

                            break;

                case  3:    maxi2 = 0;
                            for (i3 = 0; i3 < n2; i3++){
                                value3[i3] = old_value[i3];
                                if (value3[i3] < 0){
                                    value3[i3] = -value3[i3];
                                }
                                value3[i3] = (17 * value3[i3] + 9) % 257;
                            }

                            max_3 = value3[0], maxi2 = 0;
                            for (i3 = 0; i3 < n2; i3++){
                                if (value3[i3] > max_3){
                                    max_3 = value3[i3];
                                    maxi2 = i3;
                                }
                            }
                            min_3 = max_3, mini2 = 0;
                            for (int j = 0; j < n2; j++){
                                if (value3[j] <= min_3){
                                    min_3 = value3[j];
                                    mini2 = j;
                                }   
                            }
                            HP = HP - (maxi2 + mini2);
                            if (HP < 0 && phoenixdown >= 1){
                                HP = maxHP;
                                phoenixdown--;
                            }
                            break;
                
                case  4:    for (i4 = 0; i4 < n2; i4++){
                            value4[i4] = old_value[i4];
                                if (value4[i4] < 0){
                                    value4[i4] = -value4[i4];
                                }
                                value4[i4] = (17 * value4[i4] + 9) % 257;

                            }
                            
                            max_4 = value4[0];
                            max2_3x = value4[1];
                            max_4index = 0;
                            max2_3i = 1;
                            // find the 2nd biggest value 
                            if (value4[1] > max_4) {
                                max2_3x = max_4;
                                max2_3i = 0;
                                max_4 = value4[1];
                                max_4index = 1;
                            }
                            else if (value4[1] > max2_3x) {
                                max2_3x = value4[1];
                                max2_3i = 1;
                            }

                            if (value4[2] > max_4) {
                                max2_3x = max_4;
                                max2_3i = max_4index;
                                max_4 = value4[2];
                                max_4index = 2;
                            }
                            else if (value4[2] > max2_3x) {
                                max2_3x = value4[2];
                                max2_3i = 2;
                            }

                            // if there is no 2nd biggest value, declare max2_3x = -5 and max2_3i = -7
                            if (max_4 == max2_3x){
                                max2_3x = -5;
                                max2_3i = -7;
                            }

                            HP = HP - (max2_3x + max2_3i);
                            if (HP < 0 && phoenixdown >= 1){
                                HP = maxHP;
                                phoenixdown--;
                            }
                            
                            break;
                }

            }
                if (HP > maxHP)    HP = maxHP;
                if (i == count-1 && HP > 0)  rescue = 1;
                if (i == count-1 && HP < 0)  rescue = 0;
                display(HP, level, remedy, maidenkiss, phoenixdown, rescue);        

        }
        u = 0; // re-assign the index
        event_str = "";
        if (HP < 0)     break;            
    }
    infile.close();
}   

