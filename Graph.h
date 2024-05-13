#pragma once
#include <string>
#include <vector>
#include <fstream>
#include <sstream>

using namespace std;

class Graph
{
private:
	vector<string> UsersList;
	vector<string>* UserFollowing;
	int count;
public:
	Graph();

	vector<string> getUserList();
	vector<string> getFollowingList(string usr);

	int GetUsersCount();
	int FindUser(string usr);

	int GetFollowerCountFor(string user);

	void LoadData();
	void SaveData();

	void NewUserRegister(string usr);

	bool CheckFollowing(string usr, string follow_user);

	void FollowUser(string usr, string follow_user_name);
	void UnFollowUser(string usr, string following_user_name);

	~Graph();
};

