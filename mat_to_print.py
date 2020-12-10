from scipy.io import loadmat

x = loadmat('intrlvMap_PC.mat')

for i in range(164):
    print(x['ans'][i][0], end=", ")