#include<bits/stdc++.h>
using namespace std;

class Solution {
public:
    typedef long long ll;
    typedef pair<ll, string>P;
    ll BIG_VALUE = 1e10;

    unordered_map<string, vector<pair<string, ll>>>adjList;  // Graph

    vector<ll>dpMemo;

    string sourceStr;
    string targetStr;
    set<int>validLengths;

    ll dijkstra(string& start, string& end){
        //Min-Heap
        priority_queue<P, vector<P>, greater<P>> pq;
        unordered_map<string, ll>mpp;
        mpp[start] = 0;
        pq.push({0, start});

        while(!pq.empty()){
            ll currCost = pq.top().first;
            string node = pq.top().second;
            pq.pop();

            if(node == end) break;

            for(auto &edge: adjList[node]){
                string adjNode = edge.first;
                ll edgeCost = edge.second;

                if(!mpp.count(adjNode) || currCost + edgeCost < mpp[adjNode]){
                    mpp[adjNode] = currCost + edgeCost;
                    pq.push({mpp[adjNode], adjNode});
                }
            }
        }
        ll finalCost = mpp.count(end) ? mpp[end] : BIG_VALUE;

        return finalCost;

    }

    ll solve(int idx){
        if(idx > sourceStr.size()) return 0;
        ll minCost = BIG_VALUE;

        if(dpMemo[idx] != -1){
            return dpMemo[idx];
        }
        if(sourceStr[idx] == targetStr[idx]){
            minCost = min(minCost, solve(idx+1));
        }

        for(auto &len: validLengths){
            if(idx + len > sourceStr.length()){
                break;
            }

            string srcSubStr = sourceStr.substr(idx, len);
            string tarSubStr = targetStr.substr(idx, len);

            if(!adjList.count(srcSubStr)){
                continue;
            }

            ll minPathCost = dijkstra(srcSubStr, tarSubStr);
            if(minPathCost == BIG_VALUE){
                continue;
            }

            minCost = min(minCost, minPathCost + solve(idx + len));
        }
        return dpMemo[idx] = minCost;
    }

    long long minimumCost(string source, string target, vector<string>& original, vector<string>& changed, vector<int>& cost) {
        sourceStr = source;
        targetStr = target;

        for(int i = 0; i < original.size(); i++){
            adjList[original[i]].push_back({changed[i], cost[i]});
        }

        for(auto &it: original){
            validLengths.insert(it.size());
        }

        dpMemo.assign(10001, -1);

        ll result = solve(0); //Recursion generting all possible substrings

        return result == BIG_VALUE ? -1: result;
    }
};