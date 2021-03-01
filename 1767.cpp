#include<iostream>
#include<vector>
#include<tuple>
#include<stack>
#include<algorithm>
#define MAX 10001L
using namespace std;
typedef long long ll;

bool is_core_located_in_border(pair<int, int>& pos, int size) {
	if (pos.first == 0 || pos.first == size - 1)
		return true;
	if (pos.second == 0 || pos.second == size - 1)
		return true;
	return false;
}

struct State {
	int core_idx;     // 0~n-1
	int core_state;   // 1: east, 2: west, 3: south, 4: north
	State(int _core_idx, int _core_state) :core_idx(_core_idx), core_state(_core_state) {}
};

struct Result {
	int num_connected_core;
	int sum_line;
	Result(int _num_connected_core, int _sum_line) :num_connected_core(_num_connected_core), sum_line(_sum_line) {}
};

Result solve(stack<State>& stk, vector<vector<int>>& arr, vector<pair<int,int>>& core_positions, int size, int cur_core) {
	if (cur_core == core_positions.size())
		return Result(0, 0);
	if (is_core_located_in_border(core_positions[cur_core], size))
		return solve(stk, arr, core_positions, size, cur_core + 1);

	// Do not connect
	Result ans(0, 0);

	stk.push(State(cur_core, 0));
	Result result = solve(stk, arr, core_positions, size, cur_core + 1);
	if (result.num_connected_core > ans.num_connected_core)
		ans = result;
	else if (result.num_connected_core == ans.num_connected_core && result.sum_line < ans.sum_line)
		ans = result;
	stk.pop();
	
	bool possible;
	// Connected to east
	possible = true;
	for (int i = core_positions[cur_core].second + 1; i < size; i++)
		if (arr[core_positions[cur_core].first][i] != 0)
			possible = false;
	if (possible) {
		//cout << "east" << cur_core << endl;
		int cost = 0;
		for (int i = core_positions[cur_core].second + 1; i < size; i++) {
			arr[core_positions[cur_core].first][i] = 2;
			cost++;
		}
		stk.push(State(cur_core, 1));
		result = solve(stk, arr, core_positions, size, cur_core + 1);
		result.num_connected_core += 1;
		result.sum_line += cost;
		if (result.num_connected_core > ans.num_connected_core)
			ans = result;
		else if (result.num_connected_core == ans.num_connected_core && result.sum_line < ans.sum_line)
			ans = result;
		stk.pop();
		for (int i = core_positions[cur_core].second + 1; i < size; i++)
			arr[core_positions[cur_core].first][i] = 0;
	}
	// West
	possible = true;
	for (int i = 0; i < core_positions[cur_core].second; i++)
		if (arr[core_positions[cur_core].first][i] != 0)
			possible = false;
	if (possible) {
		//cout << "west" << cur_core << endl;
		int cost = 0;
		for (int i = 0; i < core_positions[cur_core].second; i++) {
			arr[core_positions[cur_core].first][i] = 2;
			cost++;
		}
		stk.push(State(cur_core, 2));
		result = solve(stk, arr, core_positions, size, cur_core + 1);
		result.num_connected_core += 1;
		result.sum_line += cost;
		if (result.num_connected_core > ans.num_connected_core)
			ans = result;
		else if (result.num_connected_core == ans.num_connected_core && result.sum_line < ans.sum_line)
			ans = result;
		stk.pop();
		for (int i = 0; i < core_positions[cur_core].second; i++)
			arr[core_positions[cur_core].first][i] = 0;
	}
	// South
	possible = true;
	for (int i = core_positions[cur_core].first + 1; i < size; i++)
		if (arr[i][core_positions[cur_core].second] != 0)
			possible = false;
	if (possible) {
		//cout << "south" << cur_core << endl;
		int cost = 0;
		for (int i = core_positions[cur_core].first + 1; i < size; i++) {
			arr[i][core_positions[cur_core].second] = 2;
			cost++;
		}
		stk.push(State(cur_core, 3));
		result = solve(stk, arr, core_positions, size, cur_core + 1);
		result.num_connected_core += 1;
		result.sum_line += cost;
		if (result.num_connected_core > ans.num_connected_core)
			ans = result;
		else if (result.num_connected_core == ans.num_connected_core && result.sum_line < ans.sum_line)
			ans = result;
		stk.pop();
		for (int i = core_positions[cur_core].first + 1; i < size; i++)
			arr[i][core_positions[cur_core].second] = 0;
	}
	// North
	possible = true;
	for (int i = 0; i < core_positions[cur_core].first; i++)
		if (arr[i][core_positions[cur_core].second] != 0)
			possible = false;
	if (possible) {
		//cout << "north" << cur_core << endl;
		int cost = 0;
		for (int i = 0; i < core_positions[cur_core].first; i++) {
			arr[i][core_positions[cur_core].second] = 2;
			cost++;
		}
		stk.push(State(cur_core, 4));
		result = solve(stk, arr, core_positions, size, cur_core + 1);
		result.num_connected_core += 1;
		result.sum_line += cost;
		if (result.num_connected_core > ans.num_connected_core)
			ans = result;
		else if (result.num_connected_core == ans.num_connected_core && result.sum_line < ans.sum_line)
			ans = result;
		stk.pop();
		for (int i = 0; i < core_positions[cur_core].first; i++)
			arr[i][core_positions[cur_core].second] = 0;
	}
	return ans;
}


int main() {
	cin.tie(NULL);
	ios::sync_with_stdio(false);
	int t, n, e, m;
	cin >> t;
	for (int test_case = 1; test_case <= t; test_case++) {
		cin >> n;
		vector<vector<int>> arr(n, vector<int>(n));
		vector<pair<int, int>> core_positions(n);
		int core_idx = 0;
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				cin >> arr[i][j];
				if (arr[i][j] == 1) {
					core_positions[core_idx++] = make_pair(i, j);
				}
			}
		}
		// Brute force with stack
		stack<State> stk;
		Result ans = solve(stk, arr, core_positions, n, 0);
		cout << "#" << test_case << " " << ans.sum_line << endl;
	}
	return 0;
}
