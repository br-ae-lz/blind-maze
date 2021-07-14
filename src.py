# sets length/width of square maze (min of 2, max of...whatever i can handle ? ?? ??)
size = 2

# builds grid's rows (row1 being individual cells, row2 being dividing lines)
row1 = []
row2 = []

for i in range (size*2 - 1):
    if i % 2:
        row1.append('|')
    else:
        row1.append(' ')
    row2.append('-')

# builds grid from rows
grid = []
for i in range(size*2 - 1):
    if i % 2:
        grid.append(row2)
    else:
        grid.append(row1)

# outputs grid
for i in range(size*2 - 1):
    print(grid[i])