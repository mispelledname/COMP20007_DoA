def arrayManipulation(n, queries):
    array = [0]*(n+1)
    for i in range(1, n+1):
        for (start, end, value) in queries:
            if (start <= i) and (i <= end):
                array[start] += value
    
    return array

nm = input().split()
n = int(nm[0])
m = int(nm[1])

queries = []
for _ in range(m):
        queries.append(list(map(int, input().rstrip().split())))

result = arrayManipulation(n, queries)

print(result)