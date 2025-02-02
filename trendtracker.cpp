#include "trendtracker.h"
// For the mandatory running times below:
// n is the number of hashtags in the Trendtracker.
// Creates a Trendtracker containing hashtags
// found in the provided file.
// The file is promised to have the following format:
//
// string1
// string2
// ...
// stringN
//
// where string1 < string2 < ... < stringN
//
// Must run in O(n) time.
Trendtracker::Trendtracker(string filename){
    ifstream fin;
    fin.open(filename);
    if(!fin.is_open()){
        return;
    }

    string word;
    Entry obj;
    obj.pop = 0;
    int maxS = 0;
    while(fin >> word){
        obj.hashtag = word;
        E.push_back(obj);
        if(S.size() < 3){
            S.push_back(maxS);
            maxS++;
        }
    }
    
    fin.close();
}

// Return the number of hashtags in the Trendtracker.
//
// Must run in O(1) time.
int Trendtracker::size(){
    return E.size();
}

// Adds 1 to the total number times a hashtag has been tweeted.
// If the hashtag does not exist in TrendTracker, does nothing.
//
// Must run in O(log(n)) time.
void Trendtracker::tweeted(string ht){
    //cout << ht<< endl << "------------------"<<endl;
    int indx = search(ht); 
    if(indx == -1){
        return;
    }
    E[indx].pop++;

    int Sindex = -1;
    for(int i=0;i<S.size();i++){
        if(E[indx].hashtag == E[S[i]].hashtag){
            Sindex = i;
        }
    }
    if(Sindex != -1){
    
        switch(Sindex){
            case 2:
                if(E[S[Sindex]].pop > E[S[1]].pop){
                    swap(S[Sindex], S[1]);
                    if(E[S[1]].pop > E[S[0]].pop){
                        swap(S[1], S[0]);
                    }
                }
            case 1: 
                if(E[S[Sindex]].pop > E[S[0]].pop){
                    swap(S[Sindex], S[0]);

                }
            case 0:
                return;
                
        }
    }

    else{
        int end = S.size()-1;
        if(E[indx].pop > E[S[end]].pop){
            S[end] = indx;
            if(E[S[end]].pop > E[S[end-1]].pop){
                        swap(S[end], S[end-1]);
                        if(E[S[end-1]].pop > E[S[0]].pop){
                            swap(S[1], S[0]);
                        }
                    }
        }
    }
    
}
    
// Returns the number of times a hashtag has been tweeted.
// If the hashtag does not exist in Trendtracker, returns -1.
//
// Must run in O(log(n)) time.
int Trendtracker::popularity(string name){
    int indx = search(name);
    if(indx == -1){
        return indx;
    }
    return E[indx].pop;
}

// Returns a most-tweeted hashtag.
// If the Trendtracker has no hashtags, returns "".
//
// Must run in O(1) time.
string Trendtracker::top_trend(){
    if(!E.size()){
        return "";
    }
    return E[S[0]].hashtag;
}

// Fills the provided vector with the 3 most-tweeted hashtags,
// in order from most-tweeted to least-tweeted.
//
// If there are fewer than 3 hashtags, then the vector is filled
// with all hashtags (in most-tweeted to least-tweeted order).
//
// Must run in O(1) time.
void Trendtracker::top_three_trends(vector<string> &T){
    T.clear();
    if(!E.size()){
        return;
    }
    for(int i=0;i<S.size();i++){
        T.push_back(E[S[i]].hashtag);
    }
}
// Optional helper method.
// Returns the index of E containing an Entry with hashtag ht.
// If no such hashtag is found, returns -1.
//
// Should run in O(log(n)).
int Trendtracker::search(string ht){
    if(!E.size()){
        return -1;
    }
    int start = 0;
    int end = E.size()-1;
    int middle;
    while(start <= end){
        middle = start + (end - start) / 2;
        if(E[middle].hashtag == ht){
            return middle;
        }
        else if(E[middle].hashtag < ht){
            start = middle +1;
        }
        else{
            end = middle -1;
        }
    }
    
    return -1;
}
