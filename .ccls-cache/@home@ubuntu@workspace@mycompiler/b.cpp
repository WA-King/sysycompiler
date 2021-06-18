int fun(int a,int b) {
	printint(a);
	printint(b);
}
int main() {
	int ans=add(add(1,2),add(2,3));
	printint(ans);
	return 0;
}