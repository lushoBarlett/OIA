#include <iostream>
#include <vector>
#include <algorithm>
#include <assert.h>

using namespace std;

int close_power(unsigned int n){
  n--;
  n |= n >> 1;
  n |= n >> 2;
  n |= n >> 4;
  n |= n >> 8;
  n |= n >> 16;
  n++;
  return n;
}


struct mis_match{
  int closed;
  int opened;
  
  // non commutative
  mis_match operator+ (const mis_match &right_sibling) const {
    int diff = opened - right_sibling.closed;
    if (diff > 0) return {closed , diff + right_sibling.opened};
    return {closed - diff, right_sibling.opened};
  }
};

struct seg_node{
  int beg;
  int end;
  mis_match data;
  
  seg_node operator+ (const seg_node &right_sibling) const {
    return {beg, right_sibling.end, data + right_sibling.data};
  }
};

int left (int i) { return i*2; }

int right (int i) { return i*2 + 1; }

seg_node bracket(char b,int i){
  if (b == '(') return {i,i+1,{0,1}};
  if (b == ')') return {i,i+1,{1,0}};
  return {i,i+1,{0,0}};
}

void fill_leaves(vector<seg_node> &s, vector<char> &b){
  int index = s.size() / 2;
  
  for (char c : b) s[index++] = bracket(c,index-s.size()/2);
  
  while( index < s.size() ) s[index++] = bracket('-',index-s.size()/2);
}

seg_node fill_tree(vector<seg_node> &segment, int index){
  assert(index <= segment.size());
  
  if (index >= segment.size() / 2) return segment[index];
  
  return segment[index] = fill_tree(segment,left(index)) + fill_tree(segment,right(index));
}

vector<seg_node> make_tree(vector<char> &b){
  int newsize = close_power(b.size());
  
  vector<seg_node> segment;
  segment.resize(newsize * 2);
  segment[0] = {-1,-1,{-1,-1}};
  mis_match filling = {-1,-1};
  
  // put actual nodes where they belong
  fill_leaves(segment,b);
  
  // fill the rest
  fill_tree(segment, 1);
  
  return segment;
}

void print_tree(vector<seg_node> s){
  for(int i = 0; i < s.size(); i++){
    if ( i >= s.size() / 2){
      
      char bracket;
      if (s[i].data.closed == 1){
        bracket = ')';
      } else if (s[i].data.opened == 1) {
        bracket = '(';
      } else { bracket = '-'; }
      
      cout << s[i].beg << ":'" << bracket << "' ";    
    
    } else {
      cerr << "[" << s[i].beg << ":" << s[i].end << "]{" << s[i].data.closed << "," << s[i].data.opened << "} ";
    }
  }
  cerr << endl << endl;
}

void update_tree(vector<seg_node> &s, int sindex, int i, char b){
  
  // out of bounds
  if (i < s[sindex].beg || i >= s[sindex].end) return;
  
  // update here
  if (s[sindex].end - s[sindex].beg == 1){
    cerr << "updating index: " << i << " saved at seg_index: " << sindex << " to char: " << b << "\n";
    s[sindex] = bracket(b,i);
    //cerr << "[" << s[sindex].beg << ":" << s[sindex].end << "]{" << s[sindex].data.closed << "," << s[sindex].data.opened << "} " << endl;
    return;
  }
  
  // ripple effect of update
  update_tree(s,left(sindex),i,b);
  update_tree(s,right(sindex),i,b);
  
  // recalculate
  s[sindex] = s[left(sindex)] + s[right(sindex)];
}

int main(){

  vector<char> input = {'(',')','(','(','(',')'};
  
  auto s = make_tree(input);
  
  print_tree(s);
  update_tree(s,1,3,')');
  print_tree(s);
  update_tree(s,1,0,')');
  print_tree(s);
  update_tree(s,1,5,'(');
  print_tree(s);
  return 0;
}
