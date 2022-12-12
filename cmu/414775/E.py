t = int(input())
 
for _ in range(t):
    X, Y = list(map(int, input().split()))
    def solve(ans, height):
        nums = list(map(int, input().split()))
        assert nums[0] >= 2
        mx = max(nums[1:])
        mn = min(nums[1:])
        ans = max(ans, (mx-mn)*height)
        return ans
 
    ans = 0
    ans = solve(ans, Y)
    ans = solve(ans, Y)
    ans = solve(ans, X)
    ans = solve(ans, X)
 
    print(ans)
