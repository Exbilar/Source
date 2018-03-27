#include <bits/stdc++.h>

#define DEBUG(...) fprintf(stderr, __VA_ARGS__)

using std :: max;
using std :: min;

const int maxm = 1e6 + 10;
const int mod = 1e9 + 7;

template <class T> bool chkmax(T &x, const T y) {
	return x < y ? x = y, true : false;
}

template <class T> bool chkmin(T &x, const T y) {
	return x > y ? x = y, true : false;
}

int prm[maxm], npr[maxm];
int N, M;

int add(int x, int y) {
	return x + y >= mod ? x + y - mod : x + y;
}

int dec(int x, int y) {
	return x - y < 0 ? x - y + mod : x - y;
}

void getPrime(int N) {
	for(int i = 2; i <= N; i++) {
		if(!npr[i]) prm[++prm[0]] = i;
		for(int j = 1; j <= prm[0] && i * prm[j] <= N; j++) {
			npr[i * prm[j]] = 1;
			if(i % prm[j] == 0) break;
		}
	}
}

void FWT(int *A, int n) {
	for(int i = 1; i < n; i <<= 1) {
		for(int j = 0; j < n; j += i << 1) {
			for(int k = 0; k < i; k++) {
				int x = A[j + k], y = A[i + j + k];
				A[j + k] = add(x, y);
				A[i + j + k] = dec(x, y);
			}
		}
	}
}

void UFWT(int *A, int n) {
	const int Inv2 = (mod + 1) >> 1;
	for(int i = 1; i < n; i <<= 1) {
		for(int j = 0; j < n; j += i << 1) {
			for(int k = 0; k < i; k++) {
				int x = A[j + k], y = A[i + j + k];
				A[j + k] = 1LL * add(x, y) * Inv2 % mod;
				A[i + j + k] = 1LL * dec(x, y) * Inv2 % mod;
			}
		}
	}
}

int fpm(int x, int k) {
	int res = 1;
	while(k) {
		if(k & 1) res = 1LL * res * x % mod;
		x = 1LL * x * x % mod;
		k >>= 1;
	}
	return res;
}

int A[maxm];
int n;

int main() {

#ifndef ONLINE_JUDGE
	freopen("bzoj4589.in", "r", stdin);
#endif
	
	getPrime(maxm - 10);
	
	while(scanf("%d%d", &N, &M) != EOF) {
		for(n = 1; n <= M; n <<= 1) {}
		for(int i = 0; i < n; i++) A[i] = 0;
		for(int i = 1; i <= prm[0] && prm[i] <= M; i++) A[prm[i]] = 1;
		FWT(A, n);
		for(int i = 0; i < n; i++) A[i] = fpm(A[i], N);
		UFWT(A, n);
		printf("%d\n", A[0]);
	}

	return 0;
}
