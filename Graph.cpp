#include "Graph.h"

Graph::Graph()
{
	count = 0;
	UsersList.clear();
	UserFollowing = nullptr;
}

int Graph::GetUsersCount()
{
	return count;
}

int Graph::FindUser(string usr) 
{
	for (int i = 0; i < count; i++)
	{
		if (UsersList[i] == usr) 
		{
			return i;
		}
	}
	return -1;
}

void Graph::LoadData() 
{
	fstream file;
	file.open("graph_file.csv", ios::in);
	count = 0;
	if (!file.is_open()) { return; }

	string line;
	while (getline(file, line)) {
		count++;
	}
	file.close();

	file.open("graph_file.csv", ios::in);
	if (!file.is_open()) { return; }

	UsersList.clear();
	delete[] UserFollowing;
	UserFollowing = new vector<string>[count];

	int user_i = 0;

	while (user_i < count) {
		string user, followers_line, follower;
		int i;
		try
		{
			getline(file, user, ':');
			getline(file, followers_line);
			if (user == "")
				break;
		}
		catch (const std::exception&)
		{
			return;
		}

		UsersList.push_back(user);

		for (int i = 0; i <= followers_line.length(); i++) {
			if (followers_line[i] == ',' || followers_line[i] == '\0') {
				if (follower != "")
					UserFollowing[user_i].push_back(follower);
				follower = "";
				continue;
			}
			follower += followers_line[i];
		}
		user_i++;
	}
	file.close();
}

vector<string> Graph::getFollowingList(string usr)
{
	int index = FindUser(usr);
	if (index == -1) 
	{ vector<string> temp;  
	return temp; }

	return UserFollowing[index];
}

int Graph::GetFollowerCountFor(string user)
{
	int followers_count = 0;
	for (int i = 0; i < count; i++)
	{
		for (int j = 0; j < UserFollowing[i].size(); i++) 
		{
			if (UserFollowing[i][j] == user)
				followers_count++;
		}
	}
	return followers_count;
}

void Graph::SaveData() {
	fstream file;
	file.open("graph_file.csv", ios::out);

	if (!file.is_open()) { return; }

	for (int i = 0; i < count; i++) {
		file << UsersList[i] << ":";
		if(UserFollowing != nullptr)
		for (int j = 0; j < UserFollowing[i].size(); j++) {
			file << UserFollowing[i][j];
			if (j + 1 != UserFollowing[i].size()) {
				file << ",";
			}
		}
		file << endl;
	}
	file.close();
}

void Graph::NewUserRegister(string usr) {
	if (FindUser(usr) != -1) { return; }

	UsersList.push_back(usr);
	count++;

	vector<string>* uf = new vector<string>[count];
	for (int i = 0; i < count - 1; i++) {
		uf[i] = UserFollowing[i];
	}

	delete[] UserFollowing;
	UserFollowing = uf;

	SaveData();
	LoadData();
}

bool Graph::CheckFollowing(string usr, string follow_user) {
	int index = FindUser(usr);
	if (index == -1) { return false; }

	for (int i = 0; i < UserFollowing[index].size(); i++) {
		if (UserFollowing[index][i] == follow_user) {
			return true;
		}
	}
	return false;
}

void Graph::FollowUser(string usr, string follow_user_name) {
	int index = FindUser(usr);
	if (index == -1) { return; }
	if (FindUser(follow_user_name) < 0) { return; }
	if (usr == follow_user_name) { return; }

	if (CheckFollowing(usr, follow_user_name)) { return; }

	UserFollowing[index].push_back(follow_user_name);
}

void Graph::UnFollowUser(string usr, string following_user_name) {
	int index = FindUser(usr);
	if (index == -1) { return; }
	if (!CheckFollowing(usr, following_user_name)) { return; }

	vector<string> newFollowingList;
	for (int i = 0; i < UserFollowing[index].size(); i++) {
		if (following_user_name != UserFollowing[index][i]) {
			newFollowingList.push_back(UserFollowing[index][i]);
		}
	}

	UserFollowing[index] = newFollowingList;
}

vector<string> Graph::getUserList() {
	return UsersList;
}

Graph::~Graph() {
	delete[] UserFollowing;
}
