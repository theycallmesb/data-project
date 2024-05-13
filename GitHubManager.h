#pragma once
#include <fstream>
#include <string>
#include <vector>

using namespace std;

struct ListNode {
	string data;
	ListNode* next;
	ListNode(string s) {
		data = s;
		next = nullptr;
	}
};

class LinkedList {
private:
	ListNode* head;
	int listSize;
public:
	LinkedList();
	void Insert(string str);
	void Delete(string str);
	int GetListSize();
	string GetDataFromIndex(int index);
};

struct Node {
	string Repository_Name;
	LinkedList* files;
	LinkedList* commits;
	bool isPrivate;
	int height;
	Node* left;
	Node* right;
	Node(string RepoName) {
		Repository_Name = RepoName;
		files = new LinkedList;
		commits = new LinkedList;
		isPrivate = true;
		height = 1;
		left = nullptr;
		right = nullptr;
	}
};

class GitHubManager
{
private:
	string OwnerName;
	Node* root;

	int getHeight(Node* node);
	int getBalance(Node* node);

	void RepositoryPrivateStatus(Node* node, string repo_name, bool status);
	Node* rightRotate(Node* y);
	Node* leftRotate(Node* x);

	Node* getRepoRecurr(Node* node, string name);

	Node* InsertFileInRepo(Node* node, string repoName, string fileName = "", string Commit_Msg = "");
	Node* minValueNode(Node* node);

	bool ForkRepoOf(Node* node, string repo_name, GitHubManager& repo);
	Node* deleteRepo(Node* root, string repoName);
	void deleteFileFromRepo(Node* node, string repoName, string fileName, string Commit_Msg);

	void SaveData();
	void saveData(Node*& node);
	void LoadData(string Owner);

	void inorderTraversalSave(Node* node);
	void inorderTraversalRepoGrab(Node* node, vector<string>& vect);

public:
	GitHubManager() {
		root = nullptr;
	}

	void CreateANewRepo(string repoName);
	void InsertFileInRepo(string repoName, string fileName);
	void DeleteFileFromRepo(string repoName, string fileName, string commit_msg);
	void Add_Commit_Msg(string repoName, string commitMsg);
	bool ForkARepository(string repo_name, GitHubManager& repo);
	static void LoadAllData(GitHubManager*& ghm);
	static bool RegisterUser(string user);
	static void SaveAllData(GitHubManager* ghm);
	static int GetGitHubUsersCount();
	Node* GetRepo(string name);
	vector<string> GetRepoList();
};

