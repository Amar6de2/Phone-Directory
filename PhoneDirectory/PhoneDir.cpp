/*
This a code to implement a phone directory from Coding Ninjas.The question states that:
You are given a list/array of strings which denotes the contact that exist in your phone directory.
The search query on a string 'str' which is a query string displays all the contacts which are present
in the given directory with the prefix as 'str'.One special property of the search function is that
when a user searches for a contact from the contact list then suggestion(contacts with prefix as the 
string entered so far) are shown after the user enters each character.
A data structure called 'Trie' has been used in order to solve the question.*/
#include<bits/stdc++.h>
 class TrieNode{public:
     char data;
     TrieNode* children[26];
     bool isterminal;
     TrieNode(char ch)
     {this->data=ch;
      this->isterminal=false;
      for(int i=0;i<26;i++)
      {this->children[i]=NULL;}
         }};
class Trie{public:
    TrieNode* root;
    Trie(){root=new TrieNode('\0');}
    void insertword(TrieNode* root,string word)
    {
      if(word.length()==0){root->isterminal=true;return;}
      int index=word[0]-'a';
      TrieNode* child;
      if(root->children[index]!=NULL)
     {
       child=root->children[index];
          }
      else{
            child=new TrieNode(word[0]);
            root->children[index]=child;
        }
        insertword(child,word.substr(1)); }
    void insert(string word)
    {insertword(root,word);}
};
void findsuggestion(TrieNode* curr,string prefix,vector<string> &temp)
{   //no return statement as there can be more than one string with the same prefix
    //hence there isterminal will not match.
    if(curr->isterminal==true){temp.push_back(prefix);}
    for(char b='a';b<='z';b++)
    {
        int index=b-'a';
        if(curr->children[index]!=NULL)
        {
        prefix.push_back(b);
        findsuggestion(curr->children[index],prefix,temp);
        prefix.pop_back();//backtracking step
        }}
}
vector<vector<string>> suggestion(TrieNode* root,string str)
{
    vector<vector<string>> ans;
    TrieNode* prev=root;TrieNode* curr;
    vector<string> temp;string prefix="";
    for(int j=0;j<str.size();j++)
    {  
        char ch=str[j];
        int index=ch-'a';
        curr=prev->children[index];
        if (curr != NULL) {
            prefix.push_back(ch);
            findsuggestion(curr, prefix, temp);
            ans.push_back(temp);
            temp.clear();
            prev = curr;
        } else {
            break;
        }
    }
    return ans;
    }
vector<vector<string>> phoneDirectory(vector<string>&contactList, string &queryStr)
{
    //    Write your code here.
    Trie* contact=new Trie();
    for(int i=0;i<contactList.size();i++)
    {contact->insert(contactList[i]);}
    return suggestion(contact->root,queryStr);
}